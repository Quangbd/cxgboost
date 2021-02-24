cmake_minimum_required(VERSION 3.17)
project(cxgboost)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILE main.cpp logging.h Model.cpp Model.h)

#add_executable(cxgboost ${SOURCE_FILE})
add_library(cxgboost SHARED ${SOURCE_FILE})

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDEBUG")
endif ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")

target_include_directories(cxgboost PRIVATE includes/xgboost)

if ("${BUILD_ENV}" STREQUAL "arm64-v8a")
    target_link_directories(cxgboost PUBLIC libs/arm64-v8a)
    target_link_libraries(cxgboost log android xgboost dmlc m dl)
else()
    target_link_directories(cxgboost PUBLIC libs/osx_x86_64)
    target_link_libraries(cxgboost xgboost dmlc pthread m dl)
endif ("${BUILD_ENV}" STREQUAL "arm64-v8a")