cmake_minimum_required(VERSION 3.17.3)
project(rnk)

set(CMAKE_CXX_STANDARD 17)

add_executable(rnk test.cpp RNK.cpp RNK.h Vector.cpp Vector.h DNK.cpp DNK.h)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)
target_link_libraries(rnk gtest gtest_main)