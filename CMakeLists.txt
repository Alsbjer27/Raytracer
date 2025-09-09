cmake_minimum_required(VERSION 3.25)
project(Raytracer CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# Fetch glm
FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG        0.9.9.8
)
FetchContent_MakeAvailable(glm)

# Executable target
add_executable(raytracer
    src/main.cpp
    src/Scene.cpp
    src/Scene.h
)

target_link_libraries(raytracer PRIVATE glm::glm)
