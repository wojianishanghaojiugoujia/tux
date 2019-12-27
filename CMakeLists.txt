cmake_minimum_required(VERSION 3.10)
project(TUX)
add_subdirectory(duktape)

set(CMAKE_C_COMPILER "/usr/bin/x86_64-w64-mingw32-gcc-posix")
set(CMAKE_CXX_COMPILER "/usr/bin/x86_64-w64-mingw32-g++-posix")
set(OpenCV_DIR /home/ago/opencv-build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

include_directories(${PROJECT_SOURCE_DIR}/duktape)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

link_directories(${OpenCV_DIR}/3rdparty)

add_executable(tux src/main.cpp)
target_link_libraries(tux duktape ${OpenCV_LIBS} -static)
