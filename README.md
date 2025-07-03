# DSP / Audio Programming

Experiments and examples to learn and play with DSP concepts and audio programming.

## Building

Dependencies:
- CMake >= 3.25
- C++ 23
- libsndfile
- portaudio
- JUCE (automatically pulled with cmake's FetchContent)

``` sh
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build -j8 # the number of cores your CPU has
```

To see in detail which executable needs which library, you can look at the
[CMakeLists.txt](./CMakeLists.txt) and search for `target_link_libraries`.

## Targets


| Target          | Description                                         | Run (after building)                            |
|-----------------|-----------------------------------------------------|-------------------------------------------------|
| [sine][1]       | Writes a 4 second 440hz sine wave using libsndfile. | `./build/sine`                                  |
| [pa_sine][2]    | Plays a 440hz sine wave with PortAudio              | `./build/pa_sine`                               |
| [jucewindow][3] | Simple JUCE window                                  | `./build/jucewindow_artefacts/Debug/jucewindow` |


[1]:./sine.cpp
[2]:./pa_sine.cpp
[3]:./jucewindow.cpp
