cmake_minimum_required(VERSION 3.24)
project(Multithreading LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_COLOR_DIAGNOSTICS ON)

# ====================== Main ======================
add_executable(game src/main.cpp)
target_include_directories(game PRIVATE src)
target_link_libraries(game ncurses)

# ====================== Formatting ======================

file(GLOB_RECURSE FORMAT_FILES
  "src/*.cpp" "src/*.hpp"
)

add_custom_target(format
    COMMAND clang-format -i ${FORMAT_FILES}
    COMMENT "Formatting code"
)
