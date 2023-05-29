set(BUILD_LIB_NAME server)
cmake_minimum_required(VERSION 3.22)
set(include_dirs ../someipService ../ ../nlohmann)
include_directories(${include_dirs})

add_library(${BUILD_LIB_NAME} SHARED
    ${CMAKE_CURRENT_SOURCE_DIR}/MsgHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Server.cpp
)