# DSP

Experiments to learn DSP.

## Building

Dependencies:
- libsndfile
- portaudio

``` sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

## Files

|------------------------|----------------------------------------|----------------------|
| File                   | Description                            | Run (after building) |
|------------------------|----------------------------------------|----------------------|
| [`src/sine.cpp`][1]    | Writes a 4 second 440hz sine wave      | `./build/sine`       |
| [`src/pa_sine.cpp`][2] | Plays a 440hz sine wave with PortAudio | `./build/pa_sine`    |
|------------------------|----------------------------------------|----------------------|

[1]:./src/sine.cpp
[2]:./src/pa_sine.cpp

