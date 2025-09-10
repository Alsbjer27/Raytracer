cmake_minimum_required(VERSION 3.25)
project(Raytracer LANGUAGES CXX)

# --- Language standard ---
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- Build-type default ---
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# --- macOS (Apple Silicon) friendliness ---
if(APPLE)
  if(NOT DEFINED CMAKE_OSX_ARCHITECTURES)
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "^(arm64|aarch64)$")
      set(CMAKE_OSX_ARCHITECTURES "arm64" CACHE STRING "Build architectures for macOS" FORCE)
    endif()
  endif()

  if(NOT DEFINED CMAKE_OSX_DEPLOYMENT_TARGET)
    set(CMAKE_OSX_DEPLOYMENT_TARGET "13.0" CACHE STRING "Minimum macOS version" FORCE)
  endif()
endif()

# --- Warnings and portability tweaks ---
if(MSVC)
  add_compile_options(/W4 /permissive- /Zc:__cplusplus)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(FetchContent)

# --- Dependencies ---
# Silence glm's deprecation warnings
set(CMAKE_WARN_DEPRECATED OFF CACHE BOOL "" FORCE)

# GLM (header-only, updated version)
FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG        1.0.1
)
FetchContent_MakeAvailable(glm)

# --- Targets ---
add_executable(raytracer
  src/main.cpp
  src/Scene.cpp
  src/Scene.h
)

target_link_libraries(raytracer PRIVATE glm::glm)

if(WIN32)
  target_compile_definitions(raytracer PRIVATE PLATFORM_WINDOWS=1)
elseif(APPLE)
  target_compile_definitions(raytracer PRIVATE PLATFORM_MACOS=1)
else()
  target_compile_definitions(raytracer PRIVATE PLATFORM_UNIX=1)
endif()

target_include_directories(raytracer PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")
