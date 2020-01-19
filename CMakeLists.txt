cmake_minimum_required(VERSION 3.10)
project(TUX)

IF(WIN32)
    set(OpenCV_DIR D:/opencv4/mingw-static)
ELSE()
    set(CMAKE_C_COMPILER "/usr/bin/x86_64-w64-mingw32-gcc-posix")
    set(CMAKE_CXX_COMPILER "/usr/bin/x86_64-w64-mingw32-g++-posix")
    set(OpenCV_DIR /home/ago/opencv-build)
ENDIF()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

add_subdirectory(duktape)
include_directories(${PROJECT_SOURCE_DIR}/duktape)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
# link_directories(${OpenCV_DIR}/3rdparty)

add_executable(tux src/main.cpp)
target_link_libraries(tux duktape ${OpenCV_LIBS} -static -lcomdlg32)

# 复制core下的所有文件到bin下
add_custom_command(OUTPUT COPY_RES
    COMMAND echo "copy files..."
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/core
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/core ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/core

    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/typings
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/typings ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/typings
    
    COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/jsconfig.json ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/jsconfig.json
)
add_custom_target(CopyTask ALL DEPENDS COPY_RES)