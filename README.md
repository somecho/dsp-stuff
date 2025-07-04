# DSP / Audio Programming

Experiments and examples to learn and play with DSP concepts and audio programming.

## Building

Requirements:
- CMake >= 3.25
- C++ 23

Dependencies:
- libsndfile
- portaudio
- JUCE 

These are automatically pulled. You do not need to download or install them.

``` sh
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build -j8 # the number of cores your CPU has
```

### CMake Options

- CMAKE_BUILD_TYPE - `Debug` or `Release`
- JUCE_PROJECTS - fetches JUCE and includes targets that require JUCE


## Targets


| Target             | Description                                         | Run (after building)                            |
|--------------------|-----------------------------------------------------|-------------------------------------------------|
| [sine][1]          | Writes a 4 second 440hz sine wave using libsndfile. | `./build/sine`                                  |
| [pa_sine][2]       | Plays a 440hz sine wave with PortAudio              | `./build/pa_sine`                               |
| [jucewindow][3]    | Simple JUCE window                                  | `./build/jucewindow_artefacts/Debug/jucewindow` |
| [attackrelease][4] | Attack Release Envelope                             | `./build/attackrelease`                         |


[1]:./sine/sine.cpp
[2]:./pa_sine/pa_sine.cpp
[3]:./jucewindow/jucewindow.cpp
[4]:./attackrelease/attackrelease.cpp
