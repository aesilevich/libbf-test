
cmake_minimum_required(VERSION 3.0)
project(libbf_test)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(boost)

add_library(bf STATIC
            ${CMAKE_CURRENT_SOURCE_DIR}/quickjs/libbf.c
            ${CMAKE_CURRENT_SOURCE_DIR}/quickjs/cutils.c
           )

add_library(bf_float STATIC bf_float.cpp)
target_link_libraries(bf_float PUBLIC bf Boost::multiprecision)

add_executable(bftest test.cpp)
target_link_libraries(bftest PRIVATE bf_float)

add_executable(test_pow test_pow.cpp)
target_link_libraries(test_pow PRIVATE bf_float)
#target_compile_options(test_pow PRIVATE -DTEST_CPP_BIN_FLOAT=1)
target_compile_options(test_pow PRIVATE -DTEST_BF_FLOAT=1)
