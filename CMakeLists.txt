
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


add_library(quickjs STATIC
            quickjs/repl.c
            quickjs/quickjs.c
            quickjs/libregexp.c
            quickjs/libunicode.c
            quickjs/cutils.c
            quickjs/quickjs-libc.c
            quickjs/libbf.c
            quickjs/qjscalc.c
           )
target_compile_definitions(quickjs PUBLIC
                           -D_GNU_SOURCE
                           -DCONFIG_VERSION=\"2021-03-27\"
                           -DCONFIG_BIGNUM)
target_include_directories(quickjs PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/quickjs")
target_link_libraries(quickjs PUBLIC bf_float m pthread dl)

add_executable(qjs quickjs/qjs.c)
target_link_libraries(qjs PRIVATE quickjs)


add_executable(xtest test.cpp)
target_link_libraries(xtest PRIVATE bf_float Boost::math)
