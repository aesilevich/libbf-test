
#include <boost/math/special_functions/acosh.hpp>
#include "bf_float/bf_float.hpp"

int main() {
    ::boost::multiprecision::acosh(::boost::multiprecision::bf_float<>{1.0});
    return 0;
}

