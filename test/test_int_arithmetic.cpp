
#include "../bf_float/bf_int.hpp"
#include "../boost/libs/multiprecision/test/test_arithmetic.hpp"
#include <boost/multiprecision/integer.hpp>

int main() {
    test<boost::multiprecision::bf_int<BF_PREC_INF>>();
    return boost::report_errors();
}
