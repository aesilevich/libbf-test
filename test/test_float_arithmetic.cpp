
#include "../bf_float/bf_float.hpp"
#include "../boost/libs/multiprecision/test/test_arithmetic.hpp"

int main() {
    test<boost::multiprecision::bf_float<>>();
    test<boost::multiprecision::bf_float_50>();
    test<boost::multiprecision::bf_float_100>();
    test<boost::multiprecision::bf_float_200>();
    test<boost::multiprecision::bf_float_500>();
    test<boost::multiprecision::bf_float_1000>();
    return boost::report_errors();
}
