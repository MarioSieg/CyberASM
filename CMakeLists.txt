cmake_minimum_required (VERSION 3.8)

project("Cyber Assembler" CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -Ofast")

message("${CMAKE_CXX_FLAGS}")

add_library("libcyberasm" STATIC 
	"Include/CyAsm/X86/Syntax.h" 
	"Include/CyAsm/X86/Registers.hpp" 
	"Include/CyAsm/X86/Size.hpp" 
	"Include/CyAsm/StreamReader.hpp" 
	"Include/CyAsm/X86/Instructions.hpp" 
	"Include/CyAsm/X86/OperandType.hpp" 
	"Include/CyAsm/MachineLanguage.hpp" 
	"Include/CyAsm/MachineStream.hpp" 
	"Source/MachineStream.cpp"     
	"Include/CyAsm/Operand.hpp"  
	"Include/cyasm/X86/Encoder.hpp" 
	"Source/Encoders.cpp"  
	"Source/Operand.cpp" 
	"Include/CyAsm/Utils.hpp")

add_executable("cyberasm" "Source/Main.cpp")
target_link_libraries("cyberasm" "libcyberasm")
