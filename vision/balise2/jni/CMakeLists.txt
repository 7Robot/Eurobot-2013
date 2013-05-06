project(proto)
cmake_minimum_required(VERSION 2.8)
find_package( OpenCV REQUIRED )
aux_source_directory(. SRC_LIST)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g -ggdb")
set(CMAKE_BUILD_TYPE Debug)

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} )
