cmake_minimum_required(VERSION 3.5)

project(opengl_cpp)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME} src/main.cpp)

add_subdirectory(external/glfw)
add_subdirectory(external/glad)

target_include_directories(${PROJECT_NAME} 
  PUBLIC external/glfw/include
  PUBLIC external/glad/include
)

target_link_directories(${PROJECT_NAME} 
  PRIVATE external/glfw/src
  PRIVATE external/glad/src
)

target_link_libraries(${PROJECT_NAME} 
  glfw 
  glad
)

if (APPLE)
  target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

# Create a symlink between the compile_commands in build folder and the src folder 
# so that clangd can recognize different compiler arguments set in CMake
file(CREATE_LINK
  "${CMAKE_BINARY_DIR}/compile_commands.json"
  "${CMAKE_SOURCE_DIR}/compile_commands.json"
  SYMBOLIC
)

