cmake_minimum_required(VERSION 3.28)
project(gameEngine CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(SFML_BUILD_NETWORK OFF)

include(FetchContent)
FetchContent_Declare(sfml URL https://github.com/SFML/SFML/archive/refs/tags/3.0.2.tar.gz)
FetchContent_MakeAvailable(sfml)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS Engine/Source/*.cpp)
add_executable(gameEngine ${SOURCES})

target_include_directories(gameEngine PRIVATE Engine/Include)
target_compile_features(gameEngine PRIVATE cxx_std_20)
target_compile_options(gameEngine PRIVATE $<IF:$<CXX_COMPILER_ID:MSVC>, /W4, -Wall -Wextra>)

target_link_libraries(gameEngine PRIVATE SFML::Graphics SFML::Audio)