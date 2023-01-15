
cmake_minimum_required(VERSION 3.0)
project(libbf_test)

set(CMAKE_CXX_STANDARD 20)
add_definitions(-DBOOST_NO_EXCEPTIONS=1)


if("${CMAKE_SYSTEM_NAME}" STREQUAL "Emscripten")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif()


set(BOOST_INCLUDE_LIBRARIES multiprecision)
add_subdirectory(boost)

add_library(bf STATIC
            ${CMAKE_CURRENT_SOURCE_DIR}/quickjs/libbf.c
            ${CMAKE_CURRENT_SOURCE_DIR}/quickjs/cutils.c
           )

add_library(bf_float STATIC bf_float.cpp)
target_link_libraries(bf_float PUBLIC bf Boost::multiprecision)

add_executable(bftest test.cpp)
target_link_libraries(bftest PRIVATE bf_float)

#add_executable(test_arithmetic test_arithmetic.cpp)
#target_link_libraries(test_arithmetic PRIVATE bf_float)
#target_compile_options(test_arithmetic PRIVATE -DTEST_BF_FLOAT=1)

add_executable(test_pow test_pow.cpp)
target_link_libraries(test_pow PRIVATE bf_float)
target_compile_options(test_pow PRIVATE -DTEST_BF_FLOAT=1)

add_executable(test_acos test_acos.cpp)
target_link_libraries(test_acos PRIVATE bf_float)
target_compile_options(test_acos PRIVATE -DTEST_BF_FLOAT=1)


#add_library(quickjs STATIC
#            quickjs/repl.c
#            quickjs/quickjs.c
#            quickjs/libregexp.c
#            quickjs/libunicode.c
#            quickjs/cutils.c
#            quickjs/quickjs-libc.c
#            quickjs/libbf.c
#            quickjs/qjscalc.c)
#target_compile_definitions(quickjs PUBLIC
#                           -D_GNU_SOURCE
#                           -DCONFIG_VERSION=\"2021-03-27\"
#                           -DCONFIG_BIGNUM)
#target_include_directories(quickjs PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/quickjs")
#target_link_libraries(quickjs PUBLIC m pthread dl)

#add_executable(qjs quickjs/qjs.c)
#target_link_libraries(qjs PRIVATE quickjs)

