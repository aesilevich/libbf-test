# Testing libbf with Boost.Multiprecision Test Suite

## Background

The libbf library is an arbitrary-precision floating-point arithmetic library that is used as a part of the QuickJS virtual machine.

The objective of this project is to ensure the correctness and stability of the libbf library by performing additional testing beyond the existing libbf test suite.


## Approach

To ensure the stability and correctness of the libbf library, we decided to perform additional testing using the test suite from the boost.multiprecision library, which is a comprehensive set of tests designed for a generic implementation of integer and floating-point numbers.

To achieve this, we have implemented a boost.multiprecision backend on top of the libbf library for both integer and floating-point numbers. This allows us to run tests from the boost.multiprecision test suite to validate the correctness of the libbf library.


## Results

After running the boost.multiprecision test suite with the libbf backend, we found that the library works correctly for a wide range of inputs and scenarios. All the tests passed without any issues, and we did not encounter any errors or failures. This indicates that the libbf library is stable and reliable, and can be used in real-world applications with confidence.


## Structure of this project

The project has the following structure:
- `bf_float` - implementation of boost.multiprecision backends for floating-point and integer numbers on top of the the libbf library
- `test` - copy of all applicable boost.multiprecision tests with added support of libbf backed
- `quickjs` - quickjs git submodule containing libbf library
- `boost` - modular boost git submodule


## Building and running tests

To build and run the tests, follow these steps:
1. Pull all required submodules:
   ```
   cd <source_dir>
   git submodule update --init --recursive
   ```
2. Configure the project using CMake:
   ```
   cd <build_dir>
   cmake <source_dir> [additional cmake options]
   ```
   You can specify additional cmake options when configuring the project, for example:
   - `-DCMAKE_C_COMPILER=...` and `-DCMAKE_CXX_COMPILER=...` - to set C and C++ compilers to build.
   - `-DCMAKE_BUILD_TYPE=[Debug|Release]` - to set debug or release build type
3. Build the project:
   ```
   make
   ```
4. Run tests:
   ```
   ctest
   ```

## List of tests

### Passed tests

|Test Name                      |Description |
|-------------------------------|-------------------|
|test_acos                      | Tests acos floating point function. Tested with precisions: 113, 50, 100, 200, 400. |
|test_asin                      | Tests asin floating point function. Tested with precisions: 113, 50, 100, 200, 400. |
|test_atan                      | Tests atan floating point function. Tested with precisions: 113, 50, 100, 200, 400, 500, 1000. |
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
|test_sf_import_c99             | Big amount of various tests for compatibility with C99 standard. Tested with precision 334. |
|test_signed_zero               | Signed zero tests. Tested with precisions: 113, 50, 100, 200, 400, 500, 1000. |
|test_round                     | Tests rounding functions. Tested with precisions: 113, 50, 100, 200, 400, 500, 1000. |
|test_sqrt                      | Tests sqrt function. Tested with precisions: 113, 50, 100, 200, 400, 500, 1000. |



### Not useful tests

|Test Name                      |Description|
|-------------------------------|-----------|
|test_assume_uniform_precision  | Tests for managing current default precision for specific implementation. Does not test computations. |
|test_convert*                  | Tests conversion between different number implementations. Does not test computations. |
|test_fixed_zero_precision_io   | Tests correct specific to boost.multiprecision formatting for stdio. Does not test computations. |
|test_float_io                  | Tests float conversion to/from string specific to boost.multiprecision. Does not test computations. |
|test_fpclassify                | Tests fpclassify function in number traits. Does not test computations. |
|test_generic_conv              | Tests conversions between different implementations. Does not test computations. |
|test_int_io                    | Tests integer conversion to/from string specific to boost.multiprecision. Does not test computations. |
|test_hash                      | Tests std::hash support for big numbers. Does not test computations. |
|test_mixed                     | Tests performing operations with mixed precisions. Not implemented for libbf. |
|test_nothrow*                  | Tests various type traits related to the nothrow specifier. Does not test computations. |
|test_move                      | Tests std::move support for big numbers. Does not test computations. |
|test_optional_compat           | Tests compatiblity with boost::optional type. Does not test computations. |
|test_preserve_*_precision      | Tests for changing default computation precision. Does not test computations. |
|test_rational_io               | Tests formatting with iostream. Does not test computations. |
|test_threaded_precision        | Tests setting default precision for different threads. Does not test computations. |
|test_trailing_io_delim         | Tests parsing numbers from strings with trailing characters. Does not test computations. |


### Not applicable tests


|Test Name                              |Description|
|---------------------------------------|-----------|
|constexpr_test_*                       | Tests for compile-time computations with the built-in boost.multiprecision implementations of big numbers. Compile time computations are not applicable to libbf |
|standalone_test_convert_from_tom_int   | Specialized test for the tommath library |
|test_adapt_serial                      | Serialization tests for built-in boost.multiprecision implementation of big numbers |
|test_checked_*cpp_int                  | Tests for throwing correct exceptions for builtin boost.multiprecision implementation of big integers |
|test_complex*                          | Tests for complex numbers |
|test_cpp_*                             | Performs tests specific to the built-in boost.multiprecision big numbers implementation |
|test_float_conversions                 | Tests compile time numeric traits for builtin boost.multiprecision big numbers implementation. |
|test_float128_serial                   | Tests serialization of builtin float implementation |
|test_gmp_conversions                   | Tests conversions between built-in implementation and libgmp implementation. |
|test_mpc*                              | libmpc implementation specific tests. |
|test_mpfr*                             | libmpfr implementation specific tests. |
|test_rat_float_interconv               | Tests conversion between different float implementations. |
|test_roots_10k_digits                  | Tests calculating sqrt with built-in implementation for very big numbers. Supports only built-in implementation. |


### Other not tested tests
|Test Name              |Description|
|-----------------------|-----------|
|test_eigen             | Test for interoperability with the Eigen linear algebra C++ library. Requires additional dependency. |
|test_int_sqrt          | Tests calculating sqrt for built-in integer implementation. Can be used for testing libbf, but requires additional implementation of conversion from 128bit integer (__int128) |
