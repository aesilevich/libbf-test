
#pragma once

#include "bf_float_backend.hpp"
#include <boost/multiprecision/number.hpp>
#include <boost/container_hash/hash.hpp>


namespace boost::multiprecision {

//
// Import the backend into this namespace:
//
using boost::multiprecision::backends::bf_float_backend;

//
// Typedef whatever number's make use of this backend:
//
template <limb_t Precision = 113>
using bf_float = number<bf_float_backend<Precision>, et_off>;

using bf_float_50 = number<bf_float_backend<50>, et_off>;
using bf_float_100 = number<bf_float_backend<100>, et_off>;
using bf_float_200 = number<bf_float_backend<200>, et_off>;
using bf_float_500 = number<bf_float_backend<500>, et_off>;
using bf_float_1000 = number<bf_float_backend<1000>, et_off>;

//
// Define a category for this number type, one of:
// 
template<limb_t Precision>
struct number_category<bf_float_backend<Precision>>: public std::integral_constant<int, number_kind_floating_point> {};

//
// Utility functions for numeric_limits specialization
//


int bf_float_set_overflow(bf_t *r, int sign, limb_t prec, bf_flags_t flags);


template <limb_t Precision>
bf_float<Precision> bf_float_max() {
    bf_float_backend<Precision> fb;
    bf_float_set_overflow(fb.bf_val(), 0, Precision, ::bf_set_exp_bits(15) | BF_RNDZ | BF_FLAG_SUBNORMAL);
    return bf_float<Precision>{fb};
}


template <limb_t Precision>
bf_float<Precision> bf_float_min() {
    auto e_max = (::limb_t)1 << (bf_get_exp_bits(bf_float_backend<Precision>::bf_flags) - 1);
    auto e_min = -e_max + 3;

    bf_float_backend<Precision> fb;
    ::bf_set_ui(fb.bf_val(), 1);
    fb.bf_val()->expn = e_min;
    return bf_float<Precision>{fb};
}


template <limb_t Precision>
bf_float<Precision> bf_float_epsilon() {
    auto a = bf_float<Precision>{1};
    return ldexp(a, 1 - static_cast<int>(std::numeric_limits<bf_float<Precision>>::digits));
}


template <limb_t Precision>
bf_float<Precision> bf_float_quiet_NaN() {
    return bf_float<Precision>{bf_float_backend<Precision>::quiet_NaN()};
}


template <limb_t Precision>
bf_float<Precision> bf_float_infinity() {
    return bf_float<Precision>{bf_float_backend<Precision>::infinity()};
}


}


namespace std {

template <limb_t Precision, boost::multiprecision::expression_template_option ExpressionTemplates>
class numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_float_backend<Precision>, ExpressionTemplates> >
{
    typedef boost::multiprecision::number<boost::multiprecision::bf_float_backend<Precision>, ExpressionTemplates> number_type;

public:
    static constexpr bool is_specialized = true;
    static number_type min() { return boost::multiprecision::bf_float_min<Precision>(); }
    static number_type max() { return boost::multiprecision::bf_float_max<Precision>(); }
    static number_type lowest();
    static constexpr int                digits       = static_cast<int>(Precision);
    static constexpr int                digits10     = digits * std::log10(2);
    static constexpr int                max_digits10 = digits * std::log10(2);
    static constexpr bool               is_signed    = false;
    static constexpr bool               is_integer   = false;
    static constexpr bool               is_exact     = false;
    static constexpr int                radix        = 2;
    static number_type                  epsilon() { return boost::multiprecision::bf_float_epsilon<Precision>(); }
    static number_type                  round_error();
    static constexpr int                min_exponent      = INT_MIN;
    static constexpr int                min_exponent10    = INT_MIN;
    static constexpr int                max_exponent      = INT_MAX;
    static constexpr int                max_exponent10    = INT_MAX;
    static constexpr bool               has_infinity      = true;
    static constexpr bool               has_quiet_NaN     = true;
    static constexpr bool               has_signaling_NaN = true;
    static constexpr float_denorm_style has_denorm        = denorm_absent;
    static constexpr bool               has_denorm_loss   = false;
    static number_type                        infinity() { return boost::multiprecision::bf_float_infinity<Precision>(); }
    static number_type                        quiet_NaN() { return boost::multiprecision::bf_float_quiet_NaN<Precision>(); }
    static number_type                        signaling_NaN();
    static number_type                        denorm_min();
    static constexpr bool               is_iec559       = false;
    static constexpr bool               is_bounded      = false;
    static constexpr bool               is_modulo       = false;
    static constexpr bool               traps           = false;
    static constexpr bool               tinyness_before = false;
    static constexpr float_round_style  round_style     = round_toward_zero;
};

template <limb_t Precision, boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr int numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_float_backend<Precision>, ExpressionTemplates> >::digits;
template <limb_t Precision, boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr int numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_float_backend<Precision>, ExpressionTemplates> >::digits10;
template <limb_t Precision, boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr int numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_float_backend<Precision>, ExpressionTemplates> >::max_digits10;
template <limb_t Precision, boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_float_backend<Precision>, ExpressionTemplates> >::is_signed;
template <limb_t Precision, boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_float_backend<Precision>, ExpressionTemplates> >::is_integer;
template <limb_t Precision, boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_float_backend<Precision>, ExpressionTemplates> >::is_exact;
template <limb_t Precision, boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr int numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_float_backend<Precision>, ExpressionTemplates> >::radix;
template <limb_t Precision, boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr int numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_float_backend<Precision>, ExpressionTemplates> >::min_exponent;
template <limb_t Precision, boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr int numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_float_backend<Precision>, ExpressionTemplates> >::min_exponent10;
template <limb_t Precision, boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr int numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_float_backend<Precision>, ExpressionTemplates> >::max_exponent;
template <limb_t Precision, boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr int numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_float_backend<Precision>, ExpressionTemplates> >::max_exponent10;
template <limb_t Precision, boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_float_backend<Precision>, ExpressionTemplates> >::has_infinity;
template <limb_t Precision, boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_float_backend<Precision>, ExpressionTemplates> >::has_quiet_NaN;
template <limb_t Precision, boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_float_backend<Precision>, ExpressionTemplates> >::has_signaling_NaN;
template <limb_t Precision, boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr float_denorm_style numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_float_backend<Precision>, ExpressionTemplates> >::has_denorm;
template <limb_t Precision, boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_float_backend<Precision>, ExpressionTemplates> >::has_denorm_loss;
template <limb_t Precision, boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_float_backend<Precision>, ExpressionTemplates> >::is_iec559;
template <limb_t Precision, boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_float_backend<Precision>, ExpressionTemplates> >::is_bounded;
template <limb_t Precision, boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_float_backend<Precision>, ExpressionTemplates> >::is_modulo;
template <limb_t Precision, boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_float_backend<Precision>, ExpressionTemplates> >::traps;
template <limb_t Precision, boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_float_backend<Precision>, ExpressionTemplates> >::tinyness_before;
template <limb_t Precision, boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr float_round_style numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_float_backend<Precision>, ExpressionTemplates> >::round_style;

} // namespace std
