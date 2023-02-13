
#pragma once

#include "bf_backend.hpp"
#include "bf_context.hpp"
#include "bf_error.hpp"
#include "libbf.hpp"
#include <boost/multiprecision/number.hpp>


namespace boost::multiprecision::backends {


template <::limb_t Precision>
class bf_int_backend: public bf_backend {
public:
    static const ::bf_flags_t bf_flags;

    bf_int_backend(): bf_backend{bf_flags} {}
    bf_int_backend(const bf_int_backend & o) = default;
//   bf_int_backend(bf_int_backend && o) = default;

    // Construction from bf backend with another precision
    template <::limb_t Precision2>
    bf_int_backend(const bf_int_backend<Precision2> & other):
    bf_backend{other} {
        // checking upper bound for conversion from higher preicsion
        if constexpr (Precision2 > Precision) {
            if (other.compare(max()) > 0) {
                *this = max();
            }
        }
    }

    ~bf_int_backend() = default;


    bf_int_backend & operator=(const bf_int_backend & o) { assign(o); return *this; }
    bf_int_backend & operator=(long long i) { assign(i); return *this; }
    bf_int_backend & operator=(unsigned long long i) { assign(i); return *this; }

    // bf_int_backend & operator=(__int128 i) { assign(i); return *this; };
    // bf_int_backend & operator=(unsigned __int128 i) { assign(i); return *this; };

    // bf_int_backend& operator=(bf_int_backend&& o);

    bf_int_backend & operator=(signed char i) { assign(i); return *this; }
    bf_int_backend & operator=(short i) { assign(i); return *this; }
    bf_int_backend & operator=(int i) { assign(i); return *this; }
    bf_int_backend & operator=(long i) { assign(i); return *this; }

    bf_int_backend & operator=(unsigned char i) { assign(i); return *this; }
    bf_int_backend & operator=(unsigned short i) { assign(i); return *this; }
    bf_int_backend & operator=(unsigned int i) { assign(i); return *this; }
    bf_int_backend & operator=(unsigned long i) { assign(i); return *this; }

    bf_int_backend & operator=(double i) { assign(i); return *this; }
    bf_int_backend & operator=(long double i) { assign(i); return *this; }
    bf_int_backend & operator=(__float128 i) { assign(i); return *this; }

    bf_int_backend & operator=(const char * s) {
        from_string(s);

        // rounding number and checking that it requal to this
        bf_int_backend rounded = *this;
        auto ret = ::bf_rint(rounded.bf_val(), BF_RNDD);
        check_bf_error(ret, "bf_rint");
        if (compare(rounded) != 0) {
            throw std::runtime_error{"parsed number is not integer"};
        }

        return *this;
    }

    std::string str(std::streamsize digits, std::ios_base::fmtflags f) const {
        auto res = ::bf_ftoa(nullptr, bf_val(), 10, 0, BF_RNDZ | BF_FTOA_FORMAT_FRAC);
        if (!res) {
            throw std::runtime_error{"bf_ftoa returned null"};
        }

        return res;
    }

    static bf_int_backend<Precision> max() {
        if constexpr (Precision == BF_PREC_INF) {
            return {};
        } else {
            bf_int_backend<Precision> res;
            res = 1;
            auto ret = ::bf_mul_2exp(res.bf_val(), Precision, Precision, bf_int_backend<Precision>::bf_flags);
            check_bf_error(ret, "bf_mul_2exp");
            return res;
        }
    }

    static bf_int_backend<Precision> min() {
        if constexpr (Precision == BF_PREC_INF) {
            return {};
        } else {
            auto res = max();
            res.negate();
            return res;
        }
    }
};


template <::limb_t Precision>
const ::bf_flags_t bf_int_backend<Precision>::bf_flags = BF_RNDZ;


//
// Required non-members:
//


template <limb_t Precision>
void eval_add(bf_int_backend<Precision> & a, const bf_int_backend<Precision> & b) {
    bf_int_backend<Precision> res;
    auto ret = ::bf_add(res.bf_val(), a.bf_val(), b.bf_val(), Precision, bf_int_backend<Precision>::bf_flags);
    check_bf_error(ret, "bf_add");
    a = res;
}


template <limb_t Precision>
void eval_subtract(bf_int_backend<Precision> & a, const bf_int_backend<Precision> & b) {
    bf_int_backend<Precision> res;
    auto ret = ::bf_sub(res.bf_val(), a.bf_val(), b.bf_val(), Precision, bf_int_backend<Precision>::bf_flags);
    check_bf_error(ret, "bf_add");
    a = res;
}


template <limb_t Precision>
void eval_multiply(bf_int_backend<Precision> & a, const bf_int_backend<Precision> & b) {
    bf_int_backend<Precision> res;
    auto ret = ::bf_mul(res.bf_val(), a.bf_val(), b.bf_val(), Precision, bf_int_backend<Precision>::bf_flags);
    check_bf_error(ret, "bf_mul");
    a = res;
}


template <limb_t Precision>
void eval_divide(bf_int_backend<Precision>& a, const bf_int_backend<Precision>& b) {
    bf_int_backend<Precision> zero;
    zero = 0;

    if (b.compare(zero) == 0) {
        throw std::overflow_error{"division by zero"};
    }

    bf_int_backend<Precision> res;
    bf_int_backend<Precision> rem;
    auto ret = ::bf_divrem(res.bf_val(), rem.bf_val(), a.bf_val(), b.bf_val(), Precision, BF_RNDZ, BF_RNDZ);
    check_bf_error(ret, "bf_divrem");
    a = res;
}



//
// Conversions: must include at least unsigned long long, long long and long double.
// Everything else is entirely optional:
//


template <limb_t Precision>
void eval_convert_to(unsigned long long * result, const bf_int_backend<Precision> & backend) {
    // checking for negative values
    bf_int_backend<Precision> zero;
    zero = 0;
    if (backend.compare(zero) < 0) {
        throw std::range_error{"can't convert negative value to unsigned long long"};
    }

    // checking for overflow if precision is greater than long long precision
    if constexpr (Precision > std::numeric_limits<unsigned long long>::digits) {
        auto long_long_max = std::numeric_limits<unsigned long long>::max();
        bf_int_backend<Precision> long_long_max_backend;
        long_long_max_backend = long_long_max;

        if (backend.compare(long_long_max_backend) > 0) {
            // we should calculate modulus by (max + 1) for unsigned values

            bf_int_backend<Precision> mod_backend;
            mod_backend = 1;
            eval_add(mod_backend, long_long_max_backend);

            bf_int_backend<Precision> res_backend = backend;
            eval_modulus(res_backend, mod_backend);
            uint64_t val = 0;
            auto res = ::bf_get_uint64(&val, res_backend.bf_val());
            check_bf_error(res, "bf_get_uint64");
            *result = val;            
            return;
        }
    }

    uint64_t val = 0;
    auto res = ::bf_get_uint64(&val, backend.bf_val());
    check_bf_error(res, "bf_get_uint64");
    *result = val;
}


template <limb_t Precision>
void eval_convert_to(long long * result, const bf_int_backend<Precision> & backend) {
    // checking for overflow/underflow if precision is greater than long long precision
    if constexpr (Precision > std::numeric_limits<long long>::digits) {
        auto long_long_max = std::numeric_limits<long long>::max();
        bf_int_backend<Precision> long_long_max_backend;
        long_long_max_backend = long_long_max;

        if (backend.compare(long_long_max_backend) > 0) {
            *result = long_long_max;
            return;
        }

        auto long_long_min = std::numeric_limits<long long>::min();
        bf_int_backend<Precision> long_long_min_backend;
        long_long_min_backend = long_long_min;

        if (backend.compare(long_long_min_backend) < 0) {
            *result = long_long_min;
            return;
        }
    }

    int64_t val = 0;
    auto res = ::bf_get_int64(&val, backend.bf_val(), bf_int_backend<Precision>::bf_flags);
    check_bf_error(res, "bf_get_uint64");
    *result = val;
}


template <limb_t Precision>
void eval_convert_to(long double * result, const bf_int_backend<Precision> & backend) {
    double double_result = 0.0;
    auto res = ::bf_get_float64(backend.bf_val(), &double_result, BF_RNDZ);
    check_bf_error(res, "bf_get_float64");
    *result = static_cast<long double>(double_result);
}



//
// Hashing support, not strictly required, but it is used in our tests:
//

template <limb_t Precision>
std::size_t hash_value(const bf_int_backend<Precision> & arg) {
    // TODO
    return 1;
}



//
// Required only for integer types:
//


template <limb_t Precision>
void eval_qr(const bf_int_backend<Precision> & numerator,
             const bf_int_backend<Precision> & denominator,
             bf_int_backend<Precision> & quotient,
             bf_int_backend<Precision> & remainder) {
    auto ret = ::bf_divrem(quotient.bf_val(),
                           remainder.bf_val(),
                           numerator.bf_val(),
                           denominator.bf_val(),
                           Precision,
                           BF_RNDZ,
                           BF_RNDZ);
    check_bf_error(ret, "bf_divrem");
}


template <limb_t Precision>
void eval_modulus(bf_int_backend<Precision> & a, const bf_int_backend<Precision> & b) {
    bf_int_backend<Precision> res;
    bf_int_backend<Precision> rem;
    auto ret = ::bf_divrem(res.bf_val(), rem.bf_val(), a.bf_val(), b.bf_val(), Precision, BF_RNDZ, BF_RNDZ);
    check_bf_error(ret, "bf_divrem");
    a = rem;
}


template <limb_t Precision>
void eval_bitwise_and(bf_int_backend<Precision> & a, const bf_int_backend<Precision> & b) {
    bf_int_backend<Precision> res;
    auto ret = ::bf_logic_and(res.bf_val(), a.bf_val(), b.bf_val());
    check_bf_error(ret, "bf_logic_and");
    a = res;
}


template <limb_t Precision>
void eval_bitwise_or(bf_int_backend<Precision> & a, const bf_int_backend<Precision> & b) {
    bf_int_backend<Precision> res;
    auto ret = ::bf_logic_or(res.bf_val(), a.bf_val(), b.bf_val());
    check_bf_error(ret, "bf_logic_or");
    a = res;
}


template <limb_t Precision>
void eval_bitwise_xor(bf_int_backend<Precision> & a, const bf_int_backend<Precision> & b) {
    bf_int_backend<Precision> res;
    auto ret = ::bf_logic_xor(res.bf_val(), a.bf_val(), b.bf_val());
    check_bf_error(ret, "bf_logic_xor");
    a = res;
}


template <limb_t Precision>
void eval_complement(bf_int_backend<Precision> & a, const bf_int_backend<Precision> & b) {
    // a = b;
    // for (::limb_t i = 0; i < a.bf_val()->len; ++i) {
    //     a.bf_val()->tab[i] = ~a.bf_val()->tab[i];
    // }

    bf_int_backend<Precision> one;
    one = 1;

    bf_int_backend<Precision> mone;
    mone = -1;

    a = b;
    eval_add(a, one);
    eval_multiply(a, mone);
}


template <limb_t Precision>
void eval_left_shift(bf_int_backend<Precision> & result, std::size_t shift) {
    auto ret = ::bf_mul_2exp(result.bf_val(), shift, Precision, bf_int_backend<Precision>::bf_flags);
    check_bf_error(ret, "bf_mul_2exp");
}


template <limb_t Precision>
void eval_right_shift(bf_int_backend<Precision> & result, std::size_t shift) {
    if (shift == 0) {
        return;
    }

    bf_int_backend<Precision> div_val;
    div_val = 1;
    eval_left_shift(div_val, shift);

    bool is_neg = result.bf_val()->sign != 0;
    if (is_neg) {
        bf_int_backend<Precision> mone;
        bf_int_backend<Precision> zero;
        mone = -1;
        zero = 0;

        // result = result * -1
        eval_multiply(result, mone);

        // result = result + 2 ^ (shift - 1)
        bf_int_backend<Precision> add_val;
        add_val = 1;
        eval_left_shift(add_val, shift - 1);
        eval_add(result, add_val);

        // result = result / 2 ^ shift
        eval_divide(result, div_val);

        if (result.compare(zero) == 0) {
            result = mone;
        } else {
            // result = result * -1
            eval_multiply(result, mone);
        }
    } else {
        eval_divide(result, div_val);
    }
}


} // namespace boost::multiprecision::backends


namespace boost::multiprecision::default_ops {

template <typename Backend>
struct double_precision_type;

// Correct specialization of the double_precision_type traits is required for correct
// work on the default implementation of powm function
template <::limb_t Precision>
struct double_precision_type<backends::bf_int_backend<Precision>> {
    using type = typename std::conditional <
        Precision == BF_PREC_INF,
        backends::bf_int_backend<Precision>,
        backends::bf_int_backend<Precision * 2>
    >::type;
};

}