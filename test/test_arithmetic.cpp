
#include "../bf_float/bf_float.hpp"
#include "../boost/libs/multiprecision/test/test_arithmetic.hpp"

int main() {
    test<boost::multiprecision::bf_float<>>();
    return boost::report_errors();
}
