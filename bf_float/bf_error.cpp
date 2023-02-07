
#include "bf_error.hpp"
#include "libbf.hpp"
#include <cassert>
#include <iostream>


namespace boost::multiprecision::backends {


static std::string bf_error_string(int ret) {
    assert(ret != 0 && ret != BF_ST_INEXACT && "invalid result passed to bf_error_string");

    switch (ret) {
    case BF_ST_INVALID_OP:
        return "invalid operation";
    case BF_ST_DIVIDE_ZERO:
        return "division to zero";
    case BF_ST_OVERFLOW:
        return "overflow";
    case BF_ST_UNDERFLOW:
        return "underflow";
    case BF_ST_INEXACT:
        return "inexact";
    case BF_ST_MEM_ERROR:
        return "memory error";
    default:
        return "unknown error";
    }
}


// Checks for libbf error and reports error and throws corresponding exception
void check_bf_error(int ret, std::string_view op) {
    ret &= ~(BF_ST_INEXACT);
    ret &= ~(BF_ST_DIVIDE_ZERO);
    ret &= ~(BF_ST_UNDERFLOW);
    ret &= ~(BF_ST_OVERFLOW);

    if (ret == 0) {
        return;
    }

    std::cerr << "ERROR: " << op << " operation failed: " << bf_error_string(ret) << std::endl;
    throw std::runtime_error{std::string{op} + std::string{" operation failed: "} + bf_error_string(ret)};
}


}
