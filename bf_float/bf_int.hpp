
#pragma once

#include "bf_int_backend.hpp"
#include <boost/multiprecision/number.hpp>
#include <boost/container_hash/hash.hpp>


namespace boost::multiprecision {

//
// Import the backend into this namespace:
//
using boost::multiprecision::backends::bf_int_backend;

//
// Typedef whatever number's make use of this backend:
//
template <limb_t Precision = BF_PREC_INF>
using bf_int = number<bf_int_backend<Precision>, et_off>;

//
// Define a category for this number type, one of:
// 
template<limb_t Precision>
struct number_category<bf_int_backend<Precision>>: public std::integral_constant<int, number_kind_integer> {};

//
// Utility functions for numeric_limits specialization
//


int bf_float_set_overflow(bf_t *r, int sign, limb_t prec, bf_flags_t flags);


template <limb_t Precision>
bf_int<Precision> bf_int_max() {
    return bf_int_backend<Precision>::max();
}


template <limb_t Precision>
bf_int<Precision> bf_int_min() {
    return bf_int_backend<Precision>::min();
}


}


namespace std {

template <limb_t Precision, boost::multiprecision::expression_template_option ExpressionTemplates>
class numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_int_backend<Precision>, ExpressionTemplates> >
{
    typedef boost::multiprecision::number<boost::multiprecision::bf_int_backend<Precision>, ExpressionTemplates> number_type;

    static constexpr int calc_digits10(int digits) {
        return static_cast<int>(digits * std::log10(static_cast<double>(2.0)));
    }

public:
    static constexpr bool is_specialized = true;
    static number_type min() { return boost::multiprecision::bf_int_min<Precision>(); }
    static number_type max() { return boost::multiprecision::bf_int_max<Precision>(); }
    static number_type lowest() { return min(); }
    static constexpr int                digits       = (Precision == BF_PREC_INF) ? INT_MAX : static_cast<int>(Precision);
    static constexpr int                digits10     = calc_digits10(digits);
    static constexpr int                max_digits10 = calc_digits10(digits);
    static constexpr bool               is_signed    = true;
    static constexpr bool               is_integer   = true;
    static constexpr bool               is_exact     = true;
    static constexpr int                radix        = 2;
    static number_type                  epsilon() { return number_type{}; }
    static number_type                  round_error() { return number_type{}; }
    static constexpr int                min_exponent      = 0;
    static constexpr int                min_exponent10    = 0;
    static constexpr int                max_exponent      = 0;
    static constexpr int                max_exponent10    = 0;
    static constexpr bool               has_infinity      = false;
    static constexpr bool               has_quiet_NaN     = false;
    static constexpr bool               has_signaling_NaN = false;
    static constexpr float_denorm_style has_denorm        = denorm_absent;
    static constexpr bool               has_denorm_loss   = false;
    static number_type                        infinity() { return number_type{}; }
    static number_type                        quiet_NaN() { return number_type{}; }
    static number_type                        signaling_NaN() { return number_type{}; }
    static number_type                        denorm_min() { return number_type{}; }
    static constexpr bool               is_iec559       = false;
    static constexpr bool               is_bounded      = (Precision != BF_PREC_INF);
    static constexpr bool               is_modulo       = false;
    static constexpr bool               traps           = false;
    static constexpr bool               tinyness_before = false;
    // static constexpr float_round_style  round_style     = round_toward_zero;
};

template <limb_t Precision, boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr int numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_int_backend<Precision>, ExpressionTemplates> >::digits;
template <limb_t Precision, boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr int numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_int_backend<Precision>, ExpressionTemplates> >::digits10;
template <limb_t Precision, boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr int numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_int_backend<Precision>, ExpressionTemplates> >::max_digits10;
template <limb_t Precision, boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_int_backend<Precision>, ExpressionTemplates> >::is_signed;
template <limb_t Precision, boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_int_backend<Precision>, ExpressionTemplates> >::is_integer;
template <limb_t Precision, boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_int_backend<Precision>, ExpressionTemplates> >::is_exact;
// template <limb_t Precision, boost::multiprecision::expression_template_option ExpressionTemplates>
// constexpr int numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_int_backend<Precision>, ExpressionTemplates> >::radix;
// template <limb_t Precision, boost::multiprecision::expression_template_option ExpressionTemplates>
// constexpr int numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_int_backend<Precision>, ExpressionTemplates> >::min_exponent;
// template <limb_t Precision, boost::multiprecision::expression_template_option ExpressionTemplates>
// constexpr int numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_int_backend<Precision>, ExpressionTemplates> >::min_exponent10;
// template <limb_t Precision, boost::multiprecision::expression_template_option ExpressionTemplates>
// constexpr int numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_int_backend<Precision>, ExpressionTemplates> >::max_exponent;
// template <limb_t Precision, boost::multiprecision::expression_template_option ExpressionTemplates>
// constexpr int numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_int_backend<Precision>, ExpressionTemplates> >::max_exponent10;
// template <limb_t Precision, boost::multiprecision::expression_template_option ExpressionTemplates>
// constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_int_backend<Precision>, ExpressionTemplates> >::has_infinity;
// template <limb_t Precision, boost::multiprecision::expression_template_option ExpressionTemplates>
// constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_int_backend<Precision>, ExpressionTemplates> >::has_quiet_NaN;
// template <limb_t Precision, boost::multiprecision::expression_template_option ExpressionTemplates>
// constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_int_backend<Precision>, ExpressionTemplates> >::has_signaling_NaN;
// template <limb_t Precision, boost::multiprecision::expression_template_option ExpressionTemplates>
// constexpr float_denorm_style numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_int_backend<Precision>, ExpressionTemplates> >::has_denorm;
// template <limb_t Precision, boost::multiprecision::expression_template_option ExpressionTemplates>
// constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_int_backend<Precision>, ExpressionTemplates> >::has_denorm_loss;
// template <limb_t Precision, boost::multiprecision::expression_template_option ExpressionTemplates>
// constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_int_backend<Precision>, ExpressionTemplates> >::is_iec559;
template <limb_t Precision, boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_int_backend<Precision>, ExpressionTemplates> >::is_bounded;
template <limb_t Precision, boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_int_backend<Precision>, ExpressionTemplates> >::is_modulo;
template <limb_t Precision, boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_int_backend<Precision>, ExpressionTemplates> >::traps;
template <limb_t Precision, boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_int_backend<Precision>, ExpressionTemplates> >::tinyness_before;
// template <limb_t Precision, boost::multiprecision::expression_template_option ExpressionTemplates>
// constexpr float_round_style numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_int_backend<Precision>, ExpressionTemplates> >::round_style;


} // namespace std
