cmake_minimum_required(VERSION 3.15)

project(dsp LANGUAGES CXX)


set(CMAKE_EXPORT_COMPILE_COMMANDS true)


add_compile_options("$<$<CONFIG:Debug>:-g;-Wall;-Wpedantic;-Wconversion>")
add_compile_options("$<$<CONFIG:Release>:-O3;-DNDEBUG;-s;-Wall;-Wpedantic>")

add_executable(sine ${CMAKE_CURRENT_SOURCE_DIR}/src/sine.cpp)
add_executable(pa_sine ${CMAKE_CURRENT_SOURCE_DIR}/src/pa_sine.cpp)

target_compile_features(sine PUBLIC cxx_std_23)
target_compile_features(pa_sine PUBLIC cxx_std_23)

target_link_libraries(sine PRIVATE sndfile)
target_link_libraries(pa_sine PRIVATE portaudio)
