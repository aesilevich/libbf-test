
# libbf test report with boost.multiprecision library

## Passed tests

|Test Name                      |Description |
|-------------------------------|-------------------|
|test_acos                      | Tests acos floating point function. Tested with precisions: 113, 50, 100, 200, 400. |
|test_asin                      | Tests asin floating point function. Tested with precisions: 113, 50, 100, 200, 400. |
|test_atan                      | Tests atan floating point function. | **FAILED** (very low precision) |
|test_constants                 | Tests calculating ln2, e, pi floating point constants. Tested with precision 2000. |
|test_cos                       | Tests cos floating point function test. Tested with precisions: 113, 50, 100, 200, 400. |
|test_cos_near_half_pi          | Tests cos floating point function for values near pi/2. Tested with precisions: 113, 50, 100, 200, 400 |
|test_cosh                      | Tests cosh function. Tested with precisions: 113, 50, 100, 200, 400, 500, 1000. |
|test_exp                       | Tests exp floating point function. Tested with precisions: 113, 50, 100, 200. |
|test_float_arithmetic          | Basic arithmetic tests including corner cases, for floating point types (tested precisions: 113, 50, 100, 200, 500, 1000)      |
|test_gcd                       | Tests GCD calculation for big integer. Tested with infinite precision. |
|test_int_arithmetic            | Basic arithmetic tests including corner cases, for integer types (tested integer with infinite precision) |
|test_log                       | Tests log floating point function. Tested with precisions: 113, 50, 100, 200, 400, 500, 1000. |
|test_miller_rabin              | Test for equality of results of the Miller–Rabin primality test performed with integer number implementation and libgmp implementation. Tested with precisions: infinite, 64, 128, 1024 |
|test_pow                       | Tests pow floating point function. Tested with precisions: 113, 50, 100, 200, 400, 500. |
|test_sin                       | Tests sin floating point function. Tested with precisions: 113, 50, 100, 200, 400. |
|test_sinh                      | Tests sinh floating point function. Tested with precisions: 113, 50, 100, 200, 400. |
|test_tan                       | Tests tan floating point function. Tested with precisions: 113, 50, 100, 200. |
|test_tanh                      | Tests tanh floating point function. Tested with precisions: 113, 50, 100, 200, 400, 500, 1000. |
|test_sin_near_half_pi          | Tests sin floating point function for values near pi/2. Tested with precisions: 113, 50, 100, 200, 400, 500, 1000. |
|test_sf_import_c99             | Big amount of various tests for compatibility with C99 standard. **Problems with atan/atan2 functions**. |
|test_signed_zero               | Signed zero tests. Tested with precisions: 113, 50, 100, 200, 400, 500, 1000. |
|test_round                     | Tests rounding functions. Tested with precisions: 113, 50, 100, 200, 400, 500, 1000. |
|test_sqrt                      | Tests sqrt function. Tested with precisions: 113, 50, 100, 200, 400, 500, 1000. |




## Not usefull tests

|Test Name                      |Description|
|-------------------------------|-----------|
|test_assume_uniform_precision  | Tests for managing current default precision for specific implementation. Does not test computations. |
|test_convert*                  | Tests conversion between different number implementations. Does not test computations. |
|test_fixed_zero_precision_io   | Tests correct specific to boost.multiprecision formatting for stdio. Does not test computations. |
|test_float_io                  | Tests float conversion to/from string specific to boost.multiprecision. Does not test computations. |
|test_fpclassify                | Tests fpclassify function in number traits. Does not test compurations. |
|test_generic_conv              | Tests conversions between different implementations. Does not test computations. |
|test_int_io                    | Tests integer conversion to/from string specific to boost.multiprecision. Does not test computations. |
|test_hash                      | Tests std::hash support for big numbers. Does not test computations. |
|test_mixed                     | Tests performing operations with mixed precisions. Not implemented for libbf. |
|test_nothrow*                  | Tests various type traits related to nothrow specifier. Does not test computations. |
|test_move                      | Tests std::move support for big number. Does not test computations. |
|test_optional_compat           | Tests compatiblity with boost::optional type. Does not test computations. |
|test_preserve_*_precision      | Tests for changing default computation precision. Does not test computations. |
|test_rational_io               | Tests formatting with iostream. Does not test computations. |
|test_threaded_precision        | Tests setting default precision for different threads. Does not test computations. |
|test_trailing_io_delim         | Tests parsing numbers from strings with trailing characters. Does not test computations. |


## Not applicable tests


|Test Name                              |Description|
|---------------------------------------|-----------|
|constexpr_test_*                       | Tests for compile time computations with the builtin boost.multiprecision implementations of big numbers. Compile time computations are not applicable to libbf |
|standalone_test_convert_from_tom_int   | Specialized test for the tommath library |
|test_adapt_serial                      | Serialization tests for builtin boost.multiprecision implementation of big numbers |
|test_checked_*cpp_int                  | Tests for throwing correct exceptions for builtin boost.multiprecision implementation of big integers |
|test_complex*                          | Tests for complex numbers |
|test_cpp_*                             | Performs tests specific to the builtin boost.multiprecision big numbers implementation |
|test_float_conversions                 | Tests compile time numeric traits for builtin boost.multiprecision big numbers implementation. |
|test_float128_serial                   | Tests serialization of builtin float implementation |
|test_gmp_conversions                   | Tests conversions between builtin implementation and libgmp implementation. |
|test_mpc*                              | libmpc implementation specific tests. |
|test_mpfr*                             | libmpfr implementation specific tests. |
|test_rat_float_interconv               | Tests conversion between different float implementations. |
|test_roots_10k_digits                  | Tests calculating sqrt with builtin implementation for very big numbers. Supports only builtin implementation. |




## Other not tested tests
|Test Name              |Description|
|-----------------------|-----------|
|test_eigen             | Test for interoperability with the Eigen linear algebra C++ library. Requires additional dependency. |
|test_int_sqrt          | Tests calculating sqrt for builtin integer implementation. Can be used for testing libbf, but requires additional implementation of conversion from 128bit integer (__int128) |
