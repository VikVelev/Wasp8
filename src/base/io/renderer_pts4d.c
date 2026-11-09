// Path traced renderer, uses PTS4D (https://github.com/VikVelev/PTS4D).
// PTS4D renders on its own threads, we just hand it the display and show
// whatever image it has finished.
#ifdef WASP8_PTS4D

#include "./pts4d/pts4d.h"

#define PTS4D_FRAME_MS 16

static SDL_Renderer  *pt_sdl = NULL;
static SDL_Texture   *pt_tex = NULL;
static Pts4dRenderer *pt = NULL;
static Uint32        *pt_pixels = NULL;
static int            pt_w = 0, pt_h = 0;
static unsigned       pt_fg = 0, pt_bg = 0;
static Uint32         pt_last_present = 0;
static Uint32         pt_last_submit = 0;

// Latest display, sent to PTS4D at most once per frame instead of on every
// draw, otherwise it ends up rendering half drawn sprites.
static unsigned char  pt_display[GRID_W * GRID_H];
static int            pt_display_dirty = 0;

// WASP8_STATS=1 prints some numbers once a second
static int            pt_stats = 0;
static unsigned       pt_stat_frames = 0, pt_stat_submits = 0;
static Uint32         pt_stat_since = 0;
static Uint64         pt_stat_time = 0;

static void pt_shutdown(void);

static int pt_init(SDL_Renderer *sdl, int win_w, int win_h, unsigned fg_rgb, unsigned bg_rgb) {
    // Leave a couple of cores for the emulator and the timer thread
    int cpus = SDL_GetCPUCount();

    Pts4dConfig config = {0};
    config.struct_size       = sizeof(config);
    config.abi_version       = PTS4D_ABI_VERSION;
    config.out_width         = win_w;
    config.out_height        = win_h;
    config.grid_width        = GRID_W;
    config.grid_height       = GRID_H;
    config.samples_per_frame = 1;
    config.max_bounces       = 4;
    config.threads           = cpus > 3 ? cpus - 2 : 1;
    config.fg_rgb            = fg_rgb;
    config.bg_rgb            = bg_rgb;

    Pts4dStatus status = pts4d_create(&config, &pt);
    if (status != PTS4D_OK) {
        printf("PTS4D failed to start (%d): %s\n", status, pts4d_last_error(NULL));
        pt = NULL;
        return -1;
    }

    pt_sdl = sdl;
    pt_w = win_w;
    pt_h = win_h;
    pt_fg = fg_rgb;
    pt_bg = bg_rgb;
    pt_stats = getenv("WASP8_STATS") != NULL;

    pt_pixels = calloc(win_w * win_h, sizeof(Uint32));
    pt_tex = SDL_CreateTexture(sdl, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, win_w, win_h);

    if (!pt_pixels || !pt_tex) {
        printf("Failed to create PTS4D output: %s\n", SDL_GetError());
        pt_shutdown();
        return -1;
    }

    return 0;
}

static void pt_submit(const unsigned char *display, unsigned fg_rgb, unsigned bg_rgb) {
    if (!pt) {
        return;
    }

    if (fg_rgb != pt_fg || bg_rgb != pt_bg) {
        pts4d_set_palette(pt, fg_rgb, bg_rgb);
        pt_fg = fg_rgb;
        pt_bg = bg_rgb;
    }

    memcpy(pt_display, display, sizeof(pt_display));
    pt_display_dirty = 1;
}

static void pt_tick(void) {
    if (!pt) {
        return;
    }

    Uint32 now = SDL_GetTicks();
    Uint64 start = SDL_GetPerformanceCounter();

    if (pt_display_dirty && now - pt_last_submit >= PTS4D_FRAME_MS) {
        pt_last_submit = now;
        pt_display_dirty = 0;
        pt_stat_submits++;

        Pts4dStatus status = pts4d_submit_grid(pt, pt_display, sizeof(pt_display));
        if (status != PTS4D_OK) {
            printf("PTS4D submit failed (%d): %s\n", status, pts4d_last_error(pt));
        }
    }

    // Once a frame's worth of time has passed, check on every tick until a new
    // image shows up. Checking only every 16ms halves the fps when a pass takes
    // slightly longer than that. Checking with nothing new is cheap.
    if (now - pt_last_present < PTS4D_FRAME_MS) {
        return;
    }

    static uint32_t spp = 0;
    Pts4dStatus status = pts4d_acquire_image(pt, pt_pixels, pt_w * sizeof(Uint32), &spp);

    if (pt_stats && now - pt_stat_since >= 1000) {
        double ms = 1000.0 * pt_stat_time / SDL_GetPerformanceFrequency();
        printf("[pts4d] %u fps, %u submits/s, %u spp, %.1f ms/s presenting\n",
               pt_stat_frames, pt_stat_submits, spp, ms);
        pt_stat_frames = 0;
        pt_stat_submits = 0;
        pt_stat_time = 0;
        pt_stat_since = now;
    }

    if (status == PTS4D_NO_NEW_FRAME) {
        return;
    }

    if (status != PTS4D_OK) {
        printf("PTS4D failed to get a frame (%d): %s\n", status, pts4d_last_error(pt));
        return;
    }

    pt_last_present = now;
    pt_stat_frames++;

    SDL_UpdateTexture(pt_tex, NULL, pt_pixels, pt_w * sizeof(Uint32));
    SDL_RenderClear(pt_sdl);
    SDL_RenderCopy(pt_sdl, pt_tex, NULL, NULL);
    SDL_RenderPresent(pt_sdl);

    pt_stat_time += SDL_GetPerformanceCounter() - start;
}

static void pt_shutdown(void) {
    pts4d_destroy(pt);
    pt = NULL;

    if (pt_tex) {
        SDL_DestroyTexture(pt_tex);
    }
    pt_tex = NULL;

    free(pt_pixels);
    pt_pixels = NULL;
}

static const wasp8_renderer pts4d_renderer = {
    "pts4d", pt_init, pt_submit, pt_tick, pt_shutdown,
};

#endif
