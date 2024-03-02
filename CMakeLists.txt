cmake_minimum_required(VERSION 3.15)
project(hcmp)
set(CMAKE_CXX_STANDARD_REQUIRED 17)
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/out)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
set(CMAKE_CXX_FLAGS_RELEASE -Ofast)

set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -O3  -Wall")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3  -Wall")

file(GLOB_RECURSE SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
add_library(hcmp_so SHARED ${SRC_LIST})
add_library(hcmp_a STATIC ${SRC_LIST})
set_target_properties(hcmp_so PROPERTIES OUTPUT_NAME "hcmp")
set_target_properties(hcmp_a PROPERTIES OUTPUT_NAME "hcmp")
