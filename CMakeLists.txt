cmake_minimum_required(VERSION 3.16)
project(OpenGLProject)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define configurations
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)

# Platform specific settings
if(MSVC)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

# Define target application
add_executable(${PROJECT_NAME})

# Add preprocessor definitions
target_compile_definitions(${PROJECT_NAME} PRIVATE
    _DEBUG
    _CONSOLE
    LAB
    $<$<CONFIG:Debug>:_DEBUG>
    $<$<CONFIG:Release>:NDEBUG>
)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/deps/include
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/thirdparty
    ${CMAKE_SOURCE_DIR}/Source
)

# Set up source files
file(GLOB_RECURSE SOURCES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
    ${CMAKE_SOURCE_DIR}/include/*.h
    ${CMAKE_SOURCE_DIR}/src/*.hpp
    ${CMAKE_SOURCE_DIR}/src/*.c
)

# Add the sources to the target
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})

# Debug configuration settings
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} /SUBSYSTEM:CONSOLE")

# Release configuration settings
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /SUBSYSTEM:CONSOLE")

# Libraries (Adjust as needed)
set(LIBS
    opengl32
    freetype
    winmm
    gdi32
    sfml-graphics
    sfml-window
    sfml-system
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBS})

# Add Debug/Release Specific Library Directories
target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/deps/lib)

# Additional preprocessor definitions
target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<CONFIG:Debug>:DEBUG>)
target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<CONFIG:Release>:NDEBUG>)

# Platform specific configurations for Win32/x64
if(CMAKE_SIZEOF_VOID_P EQUAL 4)
    # Win32
    set(PLATFORM_DEFINES WIN32)
elseif(CMAKE_SIZEOF_VOID_P EQUAL 8)
    # x64
    set(PLATFORM_DEFINES x64)
endif()

# Apply the platform definitions
target_compile_definitions(${PROJECT_NAME} PRIVATE ${PLATFORM_DEFINES})

# Include external CMake helpers if needed
include(${CMAKE_SOURCE_DIR}/CMake/Utils.cmake)
