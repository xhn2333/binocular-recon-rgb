cmake_minimum_required(VERSION 3.4)
project(BinocularReconRGB)

file(GLOB_RECURSE SRC_DIR_LIST "src/*.cpp" "src/*.c")

add_library(
    BinocularReconRGB STATIC
    ${SRC_DIR_LIST}
)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
message(${OpenCV_INCLUDE_DIRS})

add_executable(test ${SRC_DIR_LIST})
target_link_libraries(test ${OpenCV_LIBS} -ljsoncpp)