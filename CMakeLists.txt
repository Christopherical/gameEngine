cmake_minimum_required(VERSION 3.28)
project(gameEngine CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(SFML_BUILD_NETWORK OFF)
set(SPDLOG_USE_STD_FORMAT ON)
set(TGUI_BACKEND SFML_GRAPHICS)

include(FetchContent)
FetchContent_Declare(sfml URL https://github.com/SFML/SFML/archive/refs/tags/3.0.2.tar.gz)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz)
FetchContent_Declare(logs URL https://github.com/gabime/spdlog/archive/refs/tags/v1.16.0.tar.gz)
FetchContent_Declare(tgui URL https://github.com/texus/TGUI/archive/refs/tags/v1.11.0.tar.gz)
FetchContent_MakeAvailable(sfml json logs tgui)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS Engine/Source/*.cpp)
add_executable(gameEngine ${SOURCES})

target_include_directories(gameEngine PRIVATE Engine/Include)
target_compile_features(gameEngine PRIVATE cxx_std_20)
target_compile_options(gameEngine PRIVATE $<IF:$<CXX_COMPILER_ID:MSVC>, /W4, -Wall -Wextra>)

target_link_libraries(gameEngine PRIVATE SFML::Graphics SFML::Audio nlohmann_json::nlohmann_json spdlog::spdlog TGUI::TGUI)