
cmake_minimum_required(VERSION 3.0)
project(libbf_test)
enable_testing()


option(ENABLE_MPFR "Enable tests dependent on MPFR library" ON)


set(CMAKE_CXX_STANDARD 20)


if("${CMAKE_SYSTEM_NAME}" STREQUAL "Emscripten")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif()


set(BOOST_INCLUDE_LIBRARIES multiprecision exception math test)
add_subdirectory(boost)

add_library(bf STATIC
            ${CMAKE_CURRENT_SOURCE_DIR}/quickjs/libbf.c
            ${CMAKE_CURRENT_SOURCE_DIR}/quickjs/cutils.c
           )

add_subdirectory(bf_float)
add_subdirectory(test)

add_executable(xtest test.cpp)
target_link_libraries(xtest PRIVATE bf_float Boost::math)
