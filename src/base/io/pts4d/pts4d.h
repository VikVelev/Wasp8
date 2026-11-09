/*
 * PTS4D render ABI, version 1.
 *
 * Implemented in src/ffi.rs of PTS4D, Wasp8 keeps a copy of this file.
 * Keep them in sync and bump PTS4D_ABI_VERSION if anything breaks.
 *
 * Rules:
 *  - All memory crossing the boundary is owned by the caller, except the
 *    opaque Pts4dRenderer handle (create/destroy).
 *  - A handle must only be used from one thread at a time.
 *  - No function unwinds or aborts; failures return a Pts4dStatus and
 *    pts4d_last_error() describes the most recent one.
 */
#ifndef PTS4D_H
#define PTS4D_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PTS4D_ABI_VERSION 1u

typedef struct Pts4dRenderer Pts4dRenderer; /* opaque */

typedef enum {
    PTS4D_OK           =  0,
    PTS4D_NO_NEW_FRAME =  1, /* acquire_image: nothing newer than last call */
    PTS4D_ERR_NULL     = -1, /* a required pointer was NULL */
    PTS4D_ERR_ARG      = -2, /* bad size/length/stride */
    PTS4D_ERR_VERSION  = -3, /* abi_version or struct_size mismatch */
    PTS4D_ERR_PANIC    = -4, /* Rust panicked; handle may be unusable */
} Pts4dStatus;

typedef struct {
    uint32_t struct_size;       /* sizeof(Pts4dConfig) */
    uint32_t abi_version;       /* PTS4D_ABI_VERSION */
    uint32_t out_width;         /* output image size in pixels */
    uint32_t out_height;
    uint32_t grid_width;        /* emulator framebuffer, 64x32 for CHIP-8 */
    uint32_t grid_height;
    uint32_t samples_per_frame; /* samples added per render pass */
    uint32_t max_bounces;
    uint32_t threads;           /* 0 = auto */
    uint32_t fg_rgb;            /* 0xRRGGBB, lit cells */
    uint32_t bg_rgb;            /* 0xRRGGBB, unlit cells / environment */
} Pts4dConfig;

/* Creates a renderer and starts its render thread. *out is set on success. */
Pts4dStatus pts4d_create(const Pts4dConfig *cfg, Pts4dRenderer **out);

/* Stops the render thread and frees the handle. NULL is a no-op. */
void pts4d_destroy(Pts4dRenderer *r);

/*
 * Submits a new grid (grid_width * grid_height bytes, 0 = off, non-zero = on).
 * The data is copied; the call never blocks on rendering. If the grid differs
 * from the previous one, accumulation restarts, keeping a few samples of
 * history so motion leaves a short afterglow instead of pure noise. Submit at
 * display rate (~60 Hz), not on every draw opcode.
 */
Pts4dStatus pts4d_submit_grid(Pts4dRenderer *r, const uint8_t *cells, size_t len);

/*
 * Copies the newest finished image into argb8888 (out_width x out_height,
 * 0xAARRGGBB, rows stride_bytes apart). Returns PTS4D_NO_NEW_FRAME and leaves
 * the buffer untouched if nothing new finished since the last call.
 * out_spp (optional) receives the accumulated samples per pixel.
 */
Pts4dStatus pts4d_acquire_image(Pts4dRenderer *r, uint32_t *argb8888,
                                size_t stride_bytes, uint32_t *out_spp);

/* Changes colors; restarts accumulation if they differ. */
Pts4dStatus pts4d_set_palette(Pts4dRenderer *r, uint32_t fg_rgb, uint32_t bg_rgb);

/*
 * Message for the last error on this handle (or on create if r is NULL).
 * Valid until the next call on the same handle. Never NULL.
 */
const char *pts4d_last_error(const Pts4dRenderer *r);

#ifdef __cplusplus
}
#endif

#endif /* PTS4D_H */
