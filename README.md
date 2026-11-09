# Wasp8
A Chip8 C Emulator using Dynamic Recompilation and Raytracing for the rendering engine. Currently WIP

## Goals
Have fun and learn about stuff.
Create the most overengineered Chip8 emulator ever.

## Raytracing
The screen can be path traced with [PTS4D](https://github.com/VikVelev/PTS4D), every pixel becomes a glowing cube.
Clone it next to this repo and build with:

```
make interpreter RENDERER=pts4d
```

`WASP8_RENDERER=flat` switches back to the normal look, `WASP8_STATS=1` prints fps and samples per pixel.


### TODOs

| Task | Status |
|------|--------|
| Find a way to differentiate and detect Interrupts | In progress |
| Create a smart interrupt handling structure | In progress |
| Translate baseline opcodes to assembly | In progress |
|+ MOV | In progress |
|+ ADD | In progress |
|+ JMP | In progress |
|+ Other | In progress |
| Use the translated base x86 opcodes to form the actual chip8 opcodes | Stalled |
| Go into conditional and other types of jumping | Stalled |
| Adapt timing | Stalled |
