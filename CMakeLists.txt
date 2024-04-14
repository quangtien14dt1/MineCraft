cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)

set(CMAKE_SYSTEM_VERSION 10.0 CACHE STRING "" FORCE)

project(OpenGL C CXX)

set(CMAKE_CONFIGURATION_TYPES
    "Debug"
    "Release"
    CACHE STRING "" FORCE
)

add_executable( OpenGL
    "Source/Application.cpp"
    "Source/Context.cpp"
    "Source/Engine.cpp"
    "Source/Entity/Camera.cpp"
    "Source/EventManager.cpp"
    "Source/KeyBoard.cpp"
    "Source/Mesh.cpp"
    "Source/MineCraft.cpp"
    "Source/Shader/BasicShader.cpp"
    "Source/Shader/ShaderLoader.cpp"
    "Source/Texture/Texture.cpp"
    "Source/Thirdparty/fastnoise.cpp"
    "Source/Thirdparty/glad.c"
)

target_link_directories(
    OpenGL
    PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/lib;"
)

target_include_directories(OpenGL PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Thirdparty"
)

set(ADDITIONAL_LIBRARY_DEPENDENCIES
    "$<$<CONFIG:Debug>:"
        "sfml-graphics-d;"
        "sfml-window-d;"
        "sfml-system-d"
    ">"
    "$<$<CONFIG:Release>:"
        "sfml-graphics;"
        "sfml-window;"
        "sfml-system"
    ">"
    "opengl32;"
    "freetype;"
    "winmm;"
    "gdi32"
)

target_link_libraries(
        ${PROJECT_NAME} 
        PRIVATE 
        "${ADDITIONAL_LIBRARY_DEPENDENCIES}"
)
