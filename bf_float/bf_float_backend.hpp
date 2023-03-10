
#pragma once

#include "bf_backend.hpp"
#include "bf_context.hpp"
#include "bf_error.hpp"
#include "libbf.hpp"
#include <boost/multiprecision/number.hpp>


namespace boost::multiprecision::backends {


template <::limb_t Precision>
class bf_float_backend: public bf_backend {
public:
    static constexpr auto exponent_bits = BF_EXP_BITS_MAX;
    static const ::bf_flags_t bf_flags;

    bf_float_backend(): bf_backend{bf_flags} {}
    bf_float_backend(const bf_float_backend & o) = default;
//   bf_float_backend(bf_float_backend && o) = default;
    ~bf_float_backend() = default;


    bf_float_backend & operator=(const bf_float_backend & o) { assign(o); return *this; }
    bf_float_backend & operator=(long long i) { assign(i); return *this; }
    bf_float_backend & operator=(unsigned long long i) { assign(i); return *this; }
    // bf_float_backend& operator=(bf_float_backend&& o);

    bf_float_backend & operator=(signed char i) { assign(i); return *this; }
    bf_float_backend & operator=(short i) { assign(i); return *this; }
    bf_float_backend & operator=(int i) { assign(i); return *this; }
    bf_float_backend & operator=(long i) { assign(i); return *this; }

    bf_float_backend & operator=(unsigned char i) { assign(i); return *this; }
    bf_float_backend & operator=(unsigned short i) { assign(i); return *this; }
    bf_float_backend & operator=(unsigned int i) { assign(i); return *this; }
    bf_float_backend & operator=(unsigned long i) { assign(i); return *this; }

    bf_float_backend & operator=(double i) { assign(i); return *this; }
    bf_float_backend & operator=(long double i) { assign(i); return *this; }
    bf_float_backend & operator=(__float128 i) { assign(i); return *this; }

    bf_float_backend & operator=(const char * s) { from_string(s, Precision); return *this; }

    std::string str(std::streamsize digits, std::ios_base::fmtflags f) const {
        auto res = ::bf_ftoa(nullptr, bf_val(), 10, Precision, bf_flags | BF_FTOA_FORMAT_FREE_MIN);
        if (!res) {
            throw std::runtime_error{"bf_ftoa returned null"};
        }

        return res;
    }

    // //
    // // Comparison with arithmetic types, default just constructs a temporary:
    // //
    // template <class A>
    // typename std::enable_if<boost::multiprecision::detail::is_arithmetic<A>::value, int>::type compare(A i) const
    // {
    //    bf_float_backend t;
    //    t = i;  //  Note: construct directly from i if supported.
    //    return compare(t);
    // }

    static bf_float_backend<Precision> infinity() {
        bf_float_backend<Precision> res;
        ::bf_set_inf(res.bf_val(), false);
        return res;
    }

    static bf_float_backend<Precision> quiet_NaN() {
        bf_float_backend<Precision> res;
        ::bf_set_nan(res.bf_val());
        return res;
    }
};


template <::limb_t Precision>
const ::bf_flags_t bf_float_backend<Precision>::bf_flags = ::bf_set_exp_bits(exponent_bits) | BF_RNDN | BF_FLAG_SUBNORMAL;


//
// Required non-members:
//


template <limb_t Precision>
void eval_add(bf_float_backend<Precision> & a, const bf_float_backend<Precision> & b) {
    bf_float_backend<Precision> res;
    auto ret = ::bf_add(res.bf_val(), a.bf_val(), b.bf_val(), Precision, bf_float_backend<Precision>::bf_flags);
    check_bf_error(ret, "bf_add");
    a = res;
}


template <limb_t Precision>
void eval_subtract(bf_float_backend<Precision> & a, const bf_float_backend<Precision> & b) {
    bf_float_backend<Precision> res;
    auto ret = ::bf_sub(res.bf_val(), a.bf_val(), b.bf_val(), Precision, bf_float_backend<Precision>::bf_flags);
    check_bf_error(ret, "bf_add");
    a = res;
}


template <limb_t Precision>
void eval_multiply(bf_float_backend<Precision> & a, const bf_float_backend<Precision> & b) {
    bf_float_backend<Precision> res;
    auto ret = ::bf_mul(res.bf_val(), a.bf_val(), b.bf_val(), Precision, bf_float_backend<Precision>::bf_flags);
    check_bf_error(ret, "bf_mul");
    a = res;
}


template <limb_t Precision>
void eval_divide(bf_float_backend<Precision>& a, const bf_float_backend<Precision>& b) {
    bf_float_backend<Precision> res;
    auto ret = ::bf_div(res.bf_val(), a.bf_val(), b.bf_val(), Precision, bf_float_backend<Precision>::bf_flags);
    check_bf_error(ret, "bf_div");
    a = res;
}



//
// Conversions: must include at least unsigned long long, long long and long double.
// Everything else is entirely optional:
//


template <limb_t Precision>
void eval_convert_to(unsigned long long * result, const bf_float_backend<Precision> & backend) {
    uint64_t val = 0;
    auto res = ::bf_get_uint64(&val, backend.bf_val());
    check_bf_error(res, "bf_get_uint64");
    *result = val;
}


template <limb_t Precision>
void eval_convert_to(long long * result, const bf_float_backend<Precision> & backend) {
    int64_t val = 0;
    auto res = ::bf_get_int64(&val, backend.bf_val(), bf_float_backend<Precision>::bf_flags);
    check_bf_error(res, "bf_get_uint64");
    *result = val;
}


template <limb_t Precision>
void eval_convert_to(long double * result, const bf_float_backend<Precision> & backend) {
    double double_result = 0.0;
    auto res = ::bf_get_float64(backend.bf_val(), &double_result, BF_RNDZ);
    check_bf_error(res, "bf_get_float64");
    *result = static_cast<long double>(double_result);
}



//
// Operations which are required *only* if we have a floating point type:
//


template <limb_t Precision>
void eval_frexp(bf_float_backend<Precision> & result,
                const bf_float_backend<Precision> & arg,
                typename bf_float_backend<Precision>::exponent_type * p_exponent) {
    // special case for infinity/nan/zero values
    auto cls = eval_fpclassify(arg);
    if (cls == FP_INFINITE || cls == FP_ZERO || cls == FP_NAN) {
        result = arg;

        if (p_exponent) {
            *p_exponent = 0;
        }

        return;
    }

    result = arg;
    result.bf_val()->expn = 0;

    if (p_exponent) {
        *p_exponent = arg.bf_val()->expn;
    }
}


template <limb_t Precision>
void eval_frexp(bf_float_backend<Precision> & result,
                const bf_float_backend<Precision> & arg,
                int* p_exponent) {
    typename bf_float_backend<Precision>::exponent_type exp = 0;
    eval_frexp(result, arg, &exp);

    if (p_exponent != nullptr) {
        auto cls = eval_fpclassify(arg);
        if (cls == FP_ZERO || cls == FP_NORMAL) {
            if (exp > static_cast<typename bf_float_backend<Precision>::exponent_type>(INT_MAX) ||
                exp < static_cast<typename bf_float_backend<Precision>::exponent_type>(INT_MIN)) {
                throw std::runtime_error{"eval_frexp: exponent does not fit in int"};
            }

            *p_exponent = static_cast<int>(exp);
        }
    }
}


template <limb_t Precision, typename Exponent>
void eval_ldexp(bf_float_backend<Precision> & result, const bf_float_backend<Precision> & arg, Exponent exponent) {
    using exponent_type = typename bf_float_backend<Precision>::exponent_type;
    static_assert(std::is_signed_v<exponent_type>, "exponent type should be signed");

    if constexpr (std::is_same_v<exponent_type, Exponent>) {
        // default case: using expected type for exponent
        result = arg;
        auto ret = ::bf_mul_2exp(result.bf_val(), exponent, Precision, bf_float_backend<Precision>::bf_flags);
        check_bf_error(ret, "bf_mul_2exp");
    } else {
        if constexpr (sizeof(Exponent) >= sizeof(exponent_type)) {
            // checking for overflow
            if (exponent > static_cast<Exponent>(std::numeric_limits<exponent_type>::max())) {
                throw std::runtime_error{"exponent does not fit into exponent type"};
            }

            // checking for underflow
            if constexpr (std::is_signed_v<Exponent>) {
                if (exponent < static_cast<Exponent>(std::numeric_limits<exponent_type>::min())) {
                    throw std::runtime_error{"exponent does not fit into exponent type"};
                }
            }
        }

        // value of exponent should fit in exponent type
        eval_ldexp(result, arg, static_cast<exponent_type>(exponent));
    }
}


template <limb_t Precision>
void eval_floor(bf_float_backend<Precision> & result, const bf_float_backend<Precision> & arg) {
    result = arg;
    auto ret = ::bf_rint(result.bf_val(), BF_RNDD);
    check_bf_error(ret, "bf_rint");
}


template <limb_t Precision>
void eval_ceil(bf_float_backend<Precision> & result, const bf_float_backend<Precision> & arg) {
    result = arg;
    auto ret = ::bf_rint(result.bf_val(), BF_RNDU);
    check_bf_error(ret, "bf_rint");
}


template <limb_t Precision>
void eval_sqrt(bf_float_backend<Precision> & result, const bf_float_backend<Precision> & arg) {
    auto ret = ::bf_sqrt(result.bf_val(), arg.bf_val(), Precision, bf_float_backend<Precision>::bf_flags);
    check_bf_error(ret, "bf_sqrt");
}




//
// Hashing support, not strictly required, but it is used in our tests:
//

template <limb_t Precision>
std::size_t hash_value(const bf_float_backend<Precision>& arg) {
    // TODO
    return 1;
}



/*********************************************************************************************

     FLOATING POINT FUNCTIONS

***********************************************************************************************/


template <limb_t Precision>
void eval_pow(bf_float_backend<Precision> & result,
              const bf_float_backend<Precision> & a,
              const bf_float_backend<Precision> & b) {
    auto ret = ::bf_pow(result.bf_val(), a.bf_val(), b.bf_val(), Precision, bf_float_backend<Precision>::bf_flags);
    check_bf_error(ret, "bf_pow");
}


template <limb_t Precision>
void eval_acos(bf_float_backend<Precision> & result,
               const bf_float_backend<Precision> & arg) {
    auto ret = ::bf_acos(result.bf_val(), arg.bf_val(), Precision, bf_float_backend<Precision>::bf_flags);
    check_bf_error(ret, "bf_acos");
}


template <limb_t Precision>
void eval_atan(bf_float_backend<Precision> & result,
               const bf_float_backend<Precision> & arg) {
    auto ret = ::bf_atan(result.bf_val(), arg.bf_val(), Precision, bf_float_backend<Precision>::bf_flags);
    check_bf_error(ret, "bf_atan");
}


template <limb_t Precision>
void eval_atan2(bf_float_backend<Precision> & result,
                const bf_float_backend<Precision> & a,
                const bf_float_backend<Precision> & b) {
    auto ret = ::bf_atan2(result.bf_val(), a.bf_val(), b.bf_val(), Precision, bf_float_backend<Precision>::bf_flags);
    check_bf_error(ret, "bf_atan2");
}


template <limb_t Precision>
void eval_exp(bf_float_backend<Precision> & result, const bf_float_backend<Precision> & arg) {
    auto ret = ::bf_exp(result.bf_val(), arg.bf_val(), Precision, bf_float_backend<Precision>::bf_flags);
    check_bf_error(ret, "bf_exp");
}


template <limb_t Precision>
void eval_log(bf_float_backend<Precision> & result, const bf_float_backend<Precision> & arg) {
    auto ret = ::bf_log(result.bf_val(), arg.bf_val(), Precision, bf_float_backend<Precision>::bf_flags);
    check_bf_error(ret, "bf_log");
}


template <limb_t Precision>
void eval_sin(bf_float_backend<Precision> & result, const bf_float_backend<Precision> & arg) {
    auto ret = ::bf_sin(result.bf_val(), arg.bf_val(), Precision, bf_float_backend<Precision>::bf_flags);
    check_bf_error(ret, "bf_sin");
}


template <limb_t Precision>
void eval_cos(bf_float_backend<Precision> & result, const bf_float_backend<Precision> & arg) {
    auto ret = ::bf_cos(result.bf_val(), arg.bf_val(), Precision, bf_float_backend<Precision>::bf_flags);
    check_bf_error(ret, "bf_cos");
}


template <limb_t Precision>
void eval_tan(bf_float_backend<Precision> & result, const bf_float_backend<Precision> & arg) {
    auto ret = ::bf_tan(result.bf_val(), arg.bf_val(), Precision, bf_float_backend<Precision>::bf_flags);
    check_bf_error(ret, "bf_tan");
}


template <limb_t Precision>
void eval_asin(bf_float_backend<Precision> & result, const bf_float_backend<Precision> & arg) {
    auto ret = ::bf_asin(result.bf_val(), arg.bf_val(), Precision, bf_float_backend<Precision>::bf_flags);
    check_bf_error(ret, "bf_asin");
}


template <limb_t Precision>
int eval_fpclassify(const bf_float_backend<Precision> & arg) {
    if (::bf_is_zero(arg.bf_val())) {
        return FP_ZERO;
    } else if (::bf_is_nan(arg.bf_val())) {
        return FP_NAN;
    } else if (!::bf_is_finite(arg.bf_val())) {
        return FP_INFINITE;
    } else {
        return FP_NORMAL;
    }
}


template <limb_t Precision>
bool eval_is_zero(const bf_float_backend<Precision> & arg) {
    return ::bf_is_zero(arg.bf_val()) != 0;
}


template <limb_t Precision>
int eval_get_sign(const bf_float_backend<Precision> & arg) {
    if (arg.bf_val()->sign == 1) {
        return -1;
    } else {
        return (::bf_is_zero(arg.bf_val()) != 0) ? 0 : 1;
    }
}


template <limb_t Precision>
void eval_fabs(bf_float_backend<Precision> & result, const bf_float_backend<Precision> & arg) {
    result = arg;
    if (eval_get_sign(result) < 0) {
        result.negate();
    }
}


template <limb_t Precision>
void eval_abs(bf_float_backend<Precision> & result, const bf_float_backend<Precision> & arg) {
    return eval_fabs(result, arg);
}


}
