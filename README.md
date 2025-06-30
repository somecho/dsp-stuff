# DSP

Experiments to learn DSP.

## Building

Dependencies:
- libsndfile

``` sh
cmake -S . -B build
cmake --build build
```

## Files

|----------------------------------|-----------------------------------|----------------------|
| File                             | Description                       | Run (after building) |
|----------------------------------|-----------------------------------|----------------------|
| [`src/sine.cpp`](./src/sine.cpp) | Writes a 4 second 440hz sine wave | `./build/sine`       |
|----------------------------------|-----------------------------------|----------------------|

