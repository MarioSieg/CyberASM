cmake_minimum_required (VERSION 3.8)

project("Cyber Assembler" CXX)

if(MSVC)

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -permissive")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS}")

endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

message("${CMAKE_CXX_FLAGS}")

add_executable("CyberAsm" "Source/Main.cpp")
add_executable("CyberAsmTests" "Source/Tests.cpp")
