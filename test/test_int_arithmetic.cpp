
#include "../bf_float/bf_int.hpp"
#include "../boost/libs/multiprecision/test/test_arithmetic.hpp"
#include <boost/multiprecision/integer.hpp>

int main() {
    test<boost::multiprecision::bf_int<>>();
    test<boost::multiprecision::bf_int<32>>();
    test<boost::multiprecision::bf_int<64>>();
    test<boost::multiprecision::bf_int<128>>();
    test<boost::multiprecision::bf_int<256>>();
    return boost::report_errors();
}
