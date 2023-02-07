

set(compile_options "-DTEST_BF_FLOAT=1")

set(tests
    test_acos
    test_arithmetic
    test_asin
    test_atan
    test_cos
    test_cosh
    test_exp
    test_int_arithmetic
    test_log
    test_pow
    test_round
    test_sf_import_c99)

set(gmp_dep_tests
    test_miller_rabin)

list(APPEND tests ${gmp_dep_tests})


if("${ENABLE_MPFR}")
    list(APPEND tests
         test_cos_near_half_pi
         test_sin_near_half_pi)
endif()

foreach(test ${tests})
    add_executable("${test}" "${test}.cpp")
    target_link_libraries("${test}" PRIVATE bf_float Boost::multiprecision Boost::math Boost::exception quadmath m gmp)
    target_compile_options("${test}" PRIVATE ${compile_options})
    add_test(NAME "${test}" COMMAND "${test}")
endforeach()
