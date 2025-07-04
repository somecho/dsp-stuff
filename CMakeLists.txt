cmake_minimum_required(VERSION 3.25)

project(dsp LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

option(JUCE_PROJECTS "Enable JUCE projects" ON)
# Fetch Dependencies

include(FetchContent)

set(DSP_PROJECT_DEPENDENCIES PORTAUDIO LIBSNDFILE)

if(${JUCE_PROJECTS})
  FetchContent_Declare(
    JUCE
    GIT_REPOSITORY https://github.com/juce-framework/JUCE
    GIT_TAG 8.0.8
    GIT_SHALLOW TRUE
  )
  list(APPEND DSP_PROJECT_DEPENDENCIES JUCE)
endif()

FetchContent_Declare(
  PORTAUDIO
  GIT_REPOSITORY https://github.com/PortAudio/portaudio
  GIT_TAG v19.7.0
  GIT_SHALLOW TRUE
)
FetchContent_Declare(
  LIBSNDFILE
  GIT_REPOSITORY https://github.com/libsndfile/libsndfile
  GIT_TAG 1.2.2
  GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(${DSP_PROJECT_DEPENDENCIES})


add_compile_options("$<$<CONFIG:Debug>:-g;-Wall;-Wpedantic;-Wconversion>")
add_compile_options("$<$<CONFIG:Release>:-O3;-DNDEBUG;-s;-Wall;-Wpedantic>")

add_executable(sine sine.cpp)
target_link_libraries(sine PRIVATE sndfile)

add_executable(pa_sine pa_sine.cpp)
target_link_libraries(pa_sine PRIVATE portaudio)

if(${JUCE_PROJECTS})
  juce_add_gui_app(jucewindow
    VERSION 0.0.0
    NEEDS_CURL TRUE
  )
  target_sources(jucewindow PRIVATE jucewindow.cpp)
  target_link_libraries(jucewindow PRIVATE juce_core juce_gui_basics)
endif()
