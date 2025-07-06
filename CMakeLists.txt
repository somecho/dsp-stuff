cmake_minimum_required(VERSION 3.25)

project(dsp LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

option(JUCE_PROJECTS "Enable JUCE projects" ON)

# Fetch Dependencies

include(FetchContent)

if(${JUCE_PROJECTS})
  set(JUCE_WEB_BROWSER OFF CACHE INTERNAL "")
  FetchContent_Declare(
    JUCE
    GIT_REPOSITORY https://github.com/juce-framework/JUCE
    GIT_TAG 8.0.8
    GIT_SHALLOW TRUE
  )
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

set(DSP_PROJECT_DEPENDENCIES PORTAUDIO LIBSNDFILE)

if(${JUCE_PROJECTS})
  list(APPEND DSP_PROJECT_DEPENDENCIES JUCE)
endif()

FetchContent_MakeAvailable(${DSP_PROJECT_DEPENDENCIES})


add_compile_options("$<$<CONFIG:Debug>:-g;-Wall;-Wpedantic;-Wconversion;>")
add_compile_options("$<$<CONFIG:Release>:-O3;-DNDEBUG;-s;-Wall;-Wpedantic>")

add_library(common)
target_sources(common
  PRIVATE
    common/SineOscillator.cpp
)
target_include_directories(common
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/common>
)

add_executable(sine sine/sine.cpp)
target_link_libraries(sine PRIVATE sndfile)

add_executable(pa_sine pa_sine/pa_sine.cpp)
target_link_libraries(pa_sine PRIVATE portaudio)

if(${JUCE_PROJECTS})
  juce_add_gui_app(jucewindow VERSION 0.0.0)
  target_sources(jucewindow PRIVATE jucewindow/jucewindow.cpp)
  target_link_libraries(jucewindow PRIVATE juce_core juce_gui_basics)
  target_compile_definitions(jucewindow PUBLIC JUCE_WEB_BROWSER=0 JUCE_USE_CURL=0)

  juce_add_gui_app(jucegraphics VERSION 0.0.0)
  target_sources(jucegraphics
    PRIVATE
      jucegraphics/jucegraphics.cpp
      jucegraphics/MainWindow.cpp
      jucegraphics/MainComponent.cpp
  )
  target_link_libraries(jucegraphics PRIVATE juce_core juce_gui_basics juce::juce_recommended_warning_flags)
  target_compile_definitions(jucegraphics PUBLIC JUCE_WEB_BROWSER=0 JUCE_USE_CURL=0)

  juce_add_gui_app(adsr VERSION 0.0.0)
  target_sources(adsr
    PRIVATE
      adsr/adsr.cpp
      adsr/Window.cpp
      adsr/MainContentComponent.cpp
  )
  target_link_libraries(adsr
    PRIVATE
      juce_core
      juce_gui_basics
      juce_audio_basics
      juce_audio_utils
      common
  )
  target_compile_definitions(adsr PUBLIC JUCE_WEB_BROWSER=0 JUCE_USE_CURL=0)
endif()
