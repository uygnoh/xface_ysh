cmake_minimum_required(VERSION 2.6)

if(WIN32)
	message(FATAL_ERROR "windows is stupid.")
else(UNIX)
	message(STATUS "This is Linux.")
endif(WIN32)


project(demoB)

include_directories(./include)
aux_source_directory(./src CPP_FILES)

message(STATUS "CPP_FILES: " ${CPP_FILES})
message(STATUS "Binary dir:" ${PROJECT_BINARY_DIR})
message(STATUS "Source dir:" ${PROJECT_SOURCE_DIR})

add_executable(sqrtDemoB ${CPP_FILES})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
