let emu = new Emulator();

function start() {
    if (!emu.running) {
        emu.init();
    }
}