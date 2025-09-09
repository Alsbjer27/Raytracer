cmake_minimum_required(VERSION 3.25)
project(Raytracer CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG        1.0.1   # or newer 1.0.x
)
FetchContent_MakeAvailable(glm)

add_executable(raytracer
  src/main.cpp
  src/Scene.cpp
  src/Scene.h
)

target_link_libraries(raytracer PRIVATE glm::glm)
