cmake_minimum_required(VERSION 3.5)

project(opengl_cpp)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME} src/main.cpp)

find_package(Git QUIET)

# DOWNLOAD ALL SUBMODULES
if (GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
  option(GIT_SUBMODULE "Check submodules during build" ON)
  if (GIT_SUBMODULE)
    message(STATUS "Submodule update")
    execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --remote --recursive
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                    RESULT_VARIABLE GIT_SUBMOD_RESULT)
    if (NOT GIT_SUBMOD_RESULT EQUAL "0")
      message(FATAL_ERROR "git submodule update --init --remote --recursive failed with ${GIT_SUBMOD_RESULT}, please check the logs")
    endif()
  endif()
endif()

# CHECK ALL THE SUBMODULES
if (NOT EXISTS "${PROJECT_SOURCE_DIR}/external/sdl2/CMakeLists.txt")
  message(FATAL_ERROR "The glfw submodules was not downloaded! GIT_SUBMODULE was turned of or failed. Please check CMakeLists.")
endif()

if (NOT EXISTS "${PROJECT_SOURCE_DIR}/external/glad/CMakeLists.txt")
  message(FATAL_ERROR "The glad CMakeLists.txt is missing, you need to generate one yourself.")
endif()

add_subdirectory(external/glad)
add_subdirectory(external/sdl2)

target_include_directories(${PROJECT_NAME} 
  PUBLIC external/glad/include
  PUBLIC external/sdl2/include
)

target_link_directories(${PROJECT_NAME} 
  PRIVATE external/glad/src
  PRIVATE external/sdl2/src 
)

target_link_libraries(${PROJECT_NAME} 
  glad
  SDL2main
  SDL2-static
)

# Create a symlink between the compile_commands in build folder and the src folder 
# so that clangd can recognize different compiler arguments set in CMake
file(CREATE_LINK
  "${CMAKE_BINARY_DIR}/compile_commands.json"
  "${CMAKE_SOURCE_DIR}/compile_commands.json"
  SYMBOLIC
)

