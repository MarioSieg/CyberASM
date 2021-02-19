cmake_minimum_required (VERSION 3.8)

project("Cyber Assembler" CXX)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -flto -Ofast -march=native -Wall -Wextra -Werror -Wno-c++20-compat -Wno-c++98-compat -Wno-missing-prototypes -Wno-switch-enum  -Wno-c++98-compat-pedantic -Wno-unknown-attributes")
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS}")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

message("${CMAKE_CXX_FLAGS}")

add_executable("CyberAsm" "Source/Main.cpp")
add_executable("CyberAsmTests" "Source/TestMain.cpp" "Source/TestsX86.cpp")
