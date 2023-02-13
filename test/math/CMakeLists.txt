set(compile_options "-DTEST_BF_FLOAT=1")

set(tests
    test_gamma)


foreach(test ${tests})
    add_executable("${test}" "${test}.cpp")
    target_link_libraries("${test}" PRIVATE bf_float Boost::multiprecision Boost::math Boost::exception quadmath m gmp)
    target_compile_options("${test}" PRIVATE ${compile_options})
    target_include_directories("${test}" PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../boost/libs/math/include_private")
    add_test(NAME "${test}" COMMAND "${test}")
endforeach()
