cmake_minimum_required(VERSION 3.20)
project(Connect-4)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- Create Executable ---
add_executable(${PROJECT_NAME})

# --- Included files ---
target_include_directories(${PROJECT_NAME} PUBLIC Program/include)

# --- Project source files ---
target_sources(${PROJECT_NAME} PRIVATE
        Program/main.cpp
)

# --- Compile Options ---
target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:
        -Wall -Wextra -Wpedantic
        >
        $<$<CXX_COMPILER_ID:MSVC>:
        /W4 /permissive-
        >
)