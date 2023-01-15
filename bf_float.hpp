
#pragma once

#include <boost/multiprecision/number.hpp>
#include <boost/container_hash/hash.hpp>

extern "C" {
    #include "quickjs/libbf.h"
}

namespace boost {
namespace multiprecision {
namespace backends {


struct bf_float_backend
{
    //
    // Each backend need to declare 3 type lists which declare the types
    // with which this can interoperate.  These lists must at least contain
    // the widest type in each category - so "long long" must be the final
    // type in the signed_types list for example.  Any narrower types if not
    // present in the list will get promoted to the next wider type that is
    // in the list whenever mixed arithmetic involving that type is encountered.
    //
    typedef std::tuple</*signed char, short, int, long,*/ long long>                                     signed_types;
    typedef std::tuple</* unsigned char, unsigned short, unsigned, unsigned long,*/ unsigned long long>  unsigned_types;
    typedef std::tuple</*float,*/ double, long double>                                                   float_types;
    //
    // This typedef is only required if this is a floating point type, it is the type
    // which holds the exponent:
    //
    typedef int exponent_type;

    bf_float_backend();
    bf_float_backend(const bf_float_backend& o);
//   bf_float_backend(bf_float_backend&& o);
    ~bf_float_backend();

    // Optional constructors, we can make this type slightly more efficient
    // by providing constructors from any type we can handle natively.
    // These will also cause number<> to be implicitly constructible
    // from these types unless we make such constructors explicit.
    //
    // bf_float_backend(int o);  // If there's an efficient initialisation from int for example.

    //
    // In the absense of converting constructors, operator= takes the strain.
    // In addition to the usual suspects, there must be one operator= for each type
    // listed in signed_types, unsigned_types, and float_types plus a string constructor.
    //
    bf_float_backend& operator=(const bf_float_backend& o);
    // bf_float_backend& operator=(bf_float_backend&& o);
    bf_float_backend& operator=(unsigned long long i);
    bf_float_backend& operator=(long long i);
    bf_float_backend& operator=(double i);
    bf_float_backend& operator=(long double i);
    bf_float_backend& operator=(const char* s);

    void swap(bf_float_backend& o);
    std::string str(std::streamsize digits, std::ios_base::fmtflags f) const;
    void        negate();
    int         compare(const bf_float_backend& o) const;
    //
    // Comparison with arithmetic types, default just constructs a temporary:
    //
    template <class A>
    typename std::enable_if<boost::multiprecision::detail::is_arithmetic<A>::value, int>::type compare(A i) const
    {
       bf_float_backend t;
       t = i;  //  Note: construct directly from i if supported.
       return compare(t);
    }

    const bf_t* bf_val() const { return &bf_val_; }
    bf_t* bf_val() { return &bf_val_; }

private:
    bf_t bf_val_;
};

//
// Required non-members:
//
void eval_add(bf_float_backend& a, const bf_float_backend& b);
void eval_subtract(bf_float_backend& a, const bf_float_backend& b);
void eval_multiply(bf_float_backend& a, const bf_float_backend& b);
void eval_divide(bf_float_backend& a, const bf_float_backend& b);
//
// Required only for integer types:
//
void eval_modulus(bf_float_backend& a, const bf_float_backend& b);
void eval_bitwise_and(bf_float_backend& a, const bf_float_backend& b);
void eval_bitwise_or(bf_float_backend& a, const bf_float_backend& b);
void eval_bitwise_xor(bf_float_backend& a, const bf_float_backend& b);
void eval_complement(bf_float_backend& a, const bf_float_backend& b);
void eval_left_shift(bf_float_backend& a, unsigned shift);
void eval_right_shift(bf_float_backend& a, unsigned shift);
//
// Conversions: must include at least unsigned long long, long long and long double.
// Everything else is entirely optional:
//
void eval_convert_to(unsigned long long* result, const bf_float_backend& backend);
void eval_convert_to(long long* result, const bf_float_backend& backend);
void eval_convert_to(long double* result, const bf_float_backend& backend);
void eval_convert_to(long double* result, const bf_float_backend& backend);

//void eval_convert_to(unsigned long* result, const bf_float_backend& backend);
//void eval_convert_to(unsigned* result, const bf_float_backend& backend);
//void eval_convert_to(unsigned short* result, const bf_float_backend& backend);
//void eval_convert_to(unsigned char* result, const bf_float_backend& backend);

//void eval_convert_to(char* result, const bf_float_backend& backend);

//void eval_convert_to(long* result, const bf_float_backend& backend);
//void eval_convert_to(int* result, const bf_float_backend& backend);
//void eval_convert_to(short* result, const bf_float_backend& backend);
//void eval_convert_to(signed char* result, const bf_float_backend& backend);

//void eval_convert_to(double* result, const bf_float_backend& backend);
//void eval_convert_to(float* result, const bf_float_backend& backend);

//
// Operations which are required *only* if we have a floating point type:
//
void eval_frexp(bf_float_backend& result, const bf_float_backend& arg, bf_float_backend::exponent_type* p_exponent);
//void eval_frexp(bf_float_backend& result, const bf_float_backend& arg, int* p_exponent);  // throws a runtime_error if the exponent is too large for an int
void eval_ldexp(bf_float_backend& result, const bf_float_backend& arg, bf_float_backend::exponent_type exponent);
//void eval_ldexp(bf_float_backend& result, const bf_float_backend& arg, int exponent);
void eval_floor(bf_float_backend& result, const bf_float_backend& arg);
void eval_ceil(bf_float_backend& result, const bf_float_backend& arg);
void eval_sqrt(bf_float_backend& result, const bf_float_backend& arg);
//
// Operations defined *only* if we have a complex number type, type
// skeleton_real_type is assumed to be the real number type matching
// this type.
//
// void eval_conj(bf_float_backend& result, const bf_float_backend& arg);
// void eval_proj(bf_float_backend& result, const bf_float_backend& arg);
//void eval_real(skeleton_real_type& result, const bf_float_backend& arg);
//void eval_set_real(skeleton_real_type& result, const bf_float_backend& arg);
//void eval_imag(skeleton_real_type& result, const bf_float_backend& arg);
//void eval_set_real(skeleton_type& result, const skeleton_real_type& arg);
//void eval_set_imag(skeleton_type& result, const skeleton_real_type& arg);

//
// Hashing support, not strictly required, but it is used in our tests:
//
std::size_t hash_value(const bf_float_backend& arg);
//
// We're now into strictly optional requirements, everything that follows is
// nice to have, but can be synthesised from the operators above if required.
// Typically these operations are here to improve performance and reduce the
// number of temporaries created.
//
// assign_components: required number types with 2 seperate components (rationals and complex numbers).
// Type skeleton_component_type is whatever the corresponding backend type for the components is:
//
//void assign_conponents(bf_float_backend& result, skeleton_component_type const& a, skeleton_component_type const& b);
//
// Again for arithmetic types, overload for whatever arithmetic types are directly supported:
//
//void assign_conponents(bf_float_backend& result, double a, double b);
//
// Optional comparison operators:
//
#if 0

bool eval_is_zero(const bf_float_backend& arg);
int eval_get_sign(const bf_float_backend& arg);

bool eval_eq(const bf_float_backend& a, const bf_float_backend& b);
bool eval_eq(const bf_float_backend& a, unsigned long long b);
bool eval_eq(const bf_float_backend& a, unsigned long b);
bool eval_eq(const bf_float_backend& a, unsigned b);
bool eval_eq(const bf_float_backend& a, unsigned short b);
bool eval_eq(const bf_float_backend& a, unsigned char b);
bool eval_eq(const bf_float_backend& a, long long b);
bool eval_eq(const bf_float_backend& a, long b);
bool eval_eq(const bf_float_backend& a, int b);
bool eval_eq(const bf_float_backend& a, short b);
bool eval_eq(const bf_float_backend& a, signed char b);
bool eval_eq(const bf_float_backend& a, char b);
bool eval_eq(const bf_float_backend& a, long double b);
bool eval_eq(const bf_float_backend& a, double b);
bool eval_eq(const bf_float_backend& a, float b);

bool eval_eq(unsigned long long a, const bf_float_backend& b);
bool eval_eq(unsigned long a, const bf_float_backend& b);
bool eval_eq(unsigned a, const bf_float_backend& b);
bool eval_eq(unsigned short a, const bf_float_backend& b);
bool eval_eq(unsigned char a, const bf_float_backend& b);
bool eval_eq(long long a, const bf_float_backend& b);
bool eval_eq(long a, const bf_float_backend& b);
bool eval_eq(int a, const bf_float_backend& b);
bool eval_eq(short a, const bf_float_backend& b);
bool eval_eq(signed char a, const bf_float_backend& b);
bool eval_eq(char a, const bf_float_backend& b);
bool eval_eq(long double a, const bf_float_backend& b);
bool eval_eq(double a, const bf_float_backend& b);
bool eval_eq(float a, const bf_float_backend& b);

bool eval_lt(const bf_float_backend& a, const bf_float_backend& b);
bool eval_lt(const bf_float_backend& a, unsigned long long b);
bool eval_lt(const bf_float_backend& a, unsigned long b);
bool eval_lt(const bf_float_backend& a, unsigned b);
bool eval_lt(const bf_float_backend& a, unsigned short b);
bool eval_lt(const bf_float_backend& a, unsigned char b);
bool eval_lt(const bf_float_backend& a, long long b);
bool eval_lt(const bf_float_backend& a, long b);
bool eval_lt(const bf_float_backend& a, int b);
bool eval_lt(const bf_float_backend& a, short b);
bool eval_lt(const bf_float_backend& a, signed char b);
bool eval_lt(const bf_float_backend& a, char b);
bool eval_lt(const bf_float_backend& a, long double b);
bool eval_lt(const bf_float_backend& a, double b);
bool eval_lt(const bf_float_backend& a, float b);

bool eval_lt(unsigned long long a, const bf_float_backend& b);
bool eval_lt(unsigned long a, const bf_float_backend& b);
bool eval_lt(unsigned a, const bf_float_backend& b);
bool eval_lt(unsigned short a, const bf_float_backend& b);
bool eval_lt(unsigned char a, const bf_float_backend& b);
bool eval_lt(long long a, const bf_float_backend& b);
bool eval_lt(long a, const bf_float_backend& b);
bool eval_lt(int a, const bf_float_backend& b);
bool eval_lt(short a, const bf_float_backend& b);
bool eval_lt(signed char a, const bf_float_backend& b);
bool eval_lt(char a, const bf_float_backend& b);
bool eval_lt(long double a, const bf_float_backend& b);
bool eval_lt(double a, const bf_float_backend& b);
bool eval_lt(float a, const bf_float_backend& b);

bool eval_gt(const bf_float_backend& a, const bf_float_backend& b);
bool eval_gt(const bf_float_backend& a, unsigned long long b);
bool eval_gt(const bf_float_backend& a, unsigned long b);
bool eval_gt(const bf_float_backend& a, unsigned b);
bool eval_gt(const bf_float_backend& a, unsigned short b);
bool eval_gt(const bf_float_backend& a, unsigned char b);
bool eval_gt(const bf_float_backend& a, long long b);
bool eval_gt(const bf_float_backend& a, long b);
bool eval_gt(const bf_float_backend& a, int b);
bool eval_gt(const bf_float_backend& a, short b);
bool eval_gt(const bf_float_backend& a, signed char b);
bool eval_gt(const bf_float_backend& a, char b);
bool eval_gt(const bf_float_backend& a, long double b);
bool eval_gt(const bf_float_backend& a, double b);
bool eval_gt(const bf_float_backend& a, float b);

bool eval_gt(unsigned long long a, const bf_float_backend& b);
bool eval_gt(unsigned long a, const bf_float_backend& b);
bool eval_gt(unsigned a, const bf_float_backend& b);
bool eval_gt(unsigned short a, const bf_float_backend& b);
bool eval_gt(unsigned char a, const bf_float_backend& b);
bool eval_gt(long long a, const bf_float_backend& b);
bool eval_gt(long a, const bf_float_backend& b);
bool eval_gt(int a, const bf_float_backend& b);
bool eval_gt(short a, const bf_float_backend& b);
bool eval_gt(signed char a, const bf_float_backend& b);
bool eval_gt(char a, const bf_float_backend& b);
bool eval_gt(long double a, const bf_float_backend& b);
bool eval_gt(double a, const bf_float_backend& b);
bool eval_gt(float a, const bf_float_backend& b);
#endif

//
// Arithmetic operations, starting with addition:
//
#if 0
void eval_add(bf_float_backend& result, unsigned long long arg);
void eval_add(bf_float_backend& result, unsigned long arg);
void eval_add(bf_float_backend& result, unsigned arg);
void eval_add(bf_float_backend& result, unsigned short arg);
void eval_add(bf_float_backend& result, unsigned char arg);
void eval_add(bf_float_backend& result, char arg);
void eval_add(bf_float_backend& result, long long arg);
void eval_add(bf_float_backend& result, long arg);
void eval_add(bf_float_backend& result, int arg);
void eval_add(bf_float_backend& result, short arg);
void eval_add(bf_float_backend& result, signed char arg);
void eval_add(bf_float_backend& result, long double arg);
void eval_add(bf_float_backend& result, double arg);
void eval_add(bf_float_backend& result, float arg);

void eval_add(bf_float_backend& result, const bf_float_backend& a, const bf_float_backend& b);
void eval_add(bf_float_backend& result, const bf_float_backend& a, unsigned long long b);
void eval_add(bf_float_backend& result, const bf_float_backend& a, unsigned long b);
void eval_add(bf_float_backend& result, const bf_float_backend& a, unsigned b);
void eval_add(bf_float_backend& result, const bf_float_backend& a, unsigned short b);
void eval_add(bf_float_backend& result, const bf_float_backend& a, unsigned char b);
void eval_add(bf_float_backend& result, const bf_float_backend& a, long long b);
void eval_add(bf_float_backend& result, const bf_float_backend& a, long b);
void eval_add(bf_float_backend& result, const bf_float_backend& a, int b);
void eval_add(bf_float_backend& result, const bf_float_backend& a, short b);
void eval_add(bf_float_backend& result, const bf_float_backend& a, signed char b);
void eval_add(bf_float_backend& result, const bf_float_backend& a, char b);
void eval_add(bf_float_backend& result, const bf_float_backend& a, long double b);
void eval_add(bf_float_backend& result, const bf_float_backend& a, double b);
void eval_add(bf_float_backend& result, const bf_float_backend& a, float b);

void eval_add(bf_float_backend& result, unsigned long long b, const bf_float_backend& a);
void eval_add(bf_float_backend& result, unsigned long b, const bf_float_backend& a);
void eval_add(bf_float_backend& result, unsigned b, const bf_float_backend& a);
void eval_add(bf_float_backend& result, unsigned short b, const bf_float_backend& a);
void eval_add(bf_float_backend& result, unsigned char b, const bf_float_backend& a);
void eval_add(bf_float_backend& result, long long b, const bf_float_backend& a);
void eval_add(bf_float_backend& result, long b, const bf_float_backend& a);
void eval_add(bf_float_backend& result, int b, const bf_float_backend& a);
void eval_add(bf_float_backend& result, short b, const bf_float_backend& a);
void eval_add(bf_float_backend& result, signed char b, const bf_float_backend& a);
void eval_add(bf_float_backend& result, char b, const bf_float_backend& a);
void eval_add(bf_float_backend& result, long double b, const bf_float_backend& a);
void eval_add(bf_float_backend& result, double b, const bf_float_backend& a);
void eval_add(bf_float_backend& result, float b, const bf_float_backend& a);
#endif

//
// Subtraction:
//
#if 0
void eval_subtract(bf_float_backend& result, unsigned long long arg);
void eval_subtract(bf_float_backend& result, unsigned long arg);
void eval_subtract(bf_float_backend& result, unsigned arg);
void eval_subtract(bf_float_backend& result, unsigned short arg);
void eval_subtract(bf_float_backend& result, unsigned char arg);
void eval_subtract(bf_float_backend& result, char arg);
void eval_subtract(bf_float_backend& result, long long arg);
void eval_subtract(bf_float_backend& result, long arg);
void eval_subtract(bf_float_backend& result, int arg);
void eval_subtract(bf_float_backend& result, short arg);
void eval_subtract(bf_float_backend& result, signed char arg);
void eval_subtract(bf_float_backend& result, long double arg);
void eval_subtract(bf_float_backend& result, double arg);
void eval_subtract(bf_float_backend& result, float arg);

void eval_subtract(bf_float_backend& result, const bf_float_backend& a, const bf_float_backend& b);
void eval_subtract(bf_float_backend& result, const bf_float_backend& a, unsigned long long b);
void eval_subtract(bf_float_backend& result, const bf_float_backend& a, unsigned long b);
void eval_subtract(bf_float_backend& result, const bf_float_backend& a, unsigned b);
void eval_subtract(bf_float_backend& result, const bf_float_backend& a, unsigned short b);
void eval_subtract(bf_float_backend& result, const bf_float_backend& a, unsigned char b);
void eval_subtract(bf_float_backend& result, const bf_float_backend& a, long long b);
void eval_subtract(bf_float_backend& result, const bf_float_backend& a, long b);
void eval_subtract(bf_float_backend& result, const bf_float_backend& a, int b);
void eval_subtract(bf_float_backend& result, const bf_float_backend& a, short b);
void eval_subtract(bf_float_backend& result, const bf_float_backend& a, signed char b);
void eval_subtract(bf_float_backend& result, const bf_float_backend& a, char b);
void eval_subtract(bf_float_backend& result, const bf_float_backend& a, long double b);
void eval_subtract(bf_float_backend& result, const bf_float_backend& a, double b);
void eval_subtract(bf_float_backend& result, const bf_float_backend& a, float b);

void eval_subtract(bf_float_backend& result, unsigned long long b, const bf_float_backend& a);
void eval_subtract(bf_float_backend& result, unsigned long b, const bf_float_backend& a);
void eval_subtract(bf_float_backend& result, unsigned b, const bf_float_backend& a);
void eval_subtract(bf_float_backend& result, unsigned short b, const bf_float_backend& a);
void eval_subtract(bf_float_backend& result, unsigned char b, const bf_float_backend& a);
void eval_subtract(bf_float_backend& result, long long b, const bf_float_backend& a);
void eval_subtract(bf_float_backend& result, long b, const bf_float_backend& a);
void eval_subtract(bf_float_backend& result, int b, const bf_float_backend& a);
void eval_subtract(bf_float_backend& result, short b, const bf_float_backend& a);
void eval_subtract(bf_float_backend& result, signed char b, const bf_float_backend& a);
void eval_subtract(bf_float_backend& result, char b, const bf_float_backend& a);
void eval_subtract(bf_float_backend& result, long double b, const bf_float_backend& a);
void eval_subtract(bf_float_backend& result, double b, const bf_float_backend& a);
void eval_subtract(bf_float_backend& result, float b, const bf_float_backend& a);
#endif

//
// Multiplication:
//
#if 0
void eval_multiply(bf_float_backend& result, unsigned long long arg);
void eval_multiply(bf_float_backend& result, unsigned long arg);
void eval_multiply(bf_float_backend& result, unsigned arg);
void eval_multiply(bf_float_backend& result, unsigned short arg);
void eval_multiply(bf_float_backend& result, unsigned char arg);
void eval_multiply(bf_float_backend& result, char arg);
void eval_multiply(bf_float_backend& result, long long arg);
void eval_multiply(bf_float_backend& result, long arg);
void eval_multiply(bf_float_backend& result, int arg);
void eval_multiply(bf_float_backend& result, short arg);
void eval_multiply(bf_float_backend& result, signed char arg);
void eval_multiply(bf_float_backend& result, long double arg);
void eval_multiply(bf_float_backend& result, double arg);
void eval_multiply(bf_float_backend& result, float arg);

void eval_multiply(bf_float_backend& result, const bf_float_backend& a, const bf_float_backend& b);
void eval_multiply(bf_float_backend& result, const bf_float_backend& a, unsigned long long b);
void eval_multiply(bf_float_backend& result, const bf_float_backend& a, unsigned long b);
void eval_multiply(bf_float_backend& result, const bf_float_backend& a, unsigned b);
void eval_multiply(bf_float_backend& result, const bf_float_backend& a, unsigned short b);
void eval_multiply(bf_float_backend& result, const bf_float_backend& a, unsigned char b);
void eval_multiply(bf_float_backend& result, const bf_float_backend& a, long long b);
void eval_multiply(bf_float_backend& result, const bf_float_backend& a, long b);
void eval_multiply(bf_float_backend& result, const bf_float_backend& a, int b);
void eval_multiply(bf_float_backend& result, const bf_float_backend& a, short b);
void eval_multiply(bf_float_backend& result, const bf_float_backend& a, signed char b);
void eval_multiply(bf_float_backend& result, const bf_float_backend& a, char b);
void eval_multiply(bf_float_backend& result, const bf_float_backend& a, long double b);
void eval_multiply(bf_float_backend& result, const bf_float_backend& a, double b);
void eval_multiply(bf_float_backend& result, const bf_float_backend& a, float b);

void eval_multiply(bf_float_backend& result, unsigned long long b, const bf_float_backend& a);
void eval_multiply(bf_float_backend& result, unsigned long b, const bf_float_backend& a);
void eval_multiply(bf_float_backend& result, unsigned b, const bf_float_backend& a);
void eval_multiply(bf_float_backend& result, unsigned short b, const bf_float_backend& a);
void eval_multiply(bf_float_backend& result, unsigned char b, const bf_float_backend& a);
void eval_multiply(bf_float_backend& result, long long b, const bf_float_backend& a);
void eval_multiply(bf_float_backend& result, long b, const bf_float_backend& a);
void eval_multiply(bf_float_backend& result, int b, const bf_float_backend& a);
void eval_multiply(bf_float_backend& result, short b, const bf_float_backend& a);
void eval_multiply(bf_float_backend& result, signed char b, const bf_float_backend& a);
void eval_multiply(bf_float_backend& result, char b, const bf_float_backend& a);
void eval_multiply(bf_float_backend& result, long double b, const bf_float_backend& a);
void eval_multiply(bf_float_backend& result, double b, const bf_float_backend& a);
void eval_multiply(bf_float_backend& result, float b, const bf_float_backend& a);
#endif

//
// Division:
//
#if 0
void eval_divide(bf_float_backend& result, unsigned long long arg);
void eval_divide(bf_float_backend& result, unsigned long arg);
void eval_divide(bf_float_backend& result, unsigned arg);
void eval_divide(bf_float_backend& result, unsigned short arg);
void eval_divide(bf_float_backend& result, unsigned char arg);
void eval_divide(bf_float_backend& result, char arg);
void eval_divide(bf_float_backend& result, long long arg);
void eval_divide(bf_float_backend& result, long arg);
void eval_divide(bf_float_backend& result, int arg);
void eval_divide(bf_float_backend& result, short arg);
void eval_divide(bf_float_backend& result, signed char arg);
void eval_divide(bf_float_backend& result, long double arg);
void eval_divide(bf_float_backend& result, double arg);
void eval_divide(bf_float_backend& result, float arg);

void eval_divide(bf_float_backend& result, const bf_float_backend& a, const bf_float_backend& b);
void eval_divide(bf_float_backend& result, const bf_float_backend& a, unsigned long long b);
void eval_divide(bf_float_backend& result, const bf_float_backend& a, unsigned long b);
void eval_divide(bf_float_backend& result, const bf_float_backend& a, unsigned b);
void eval_divide(bf_float_backend& result, const bf_float_backend& a, unsigned short b);
void eval_divide(bf_float_backend& result, const bf_float_backend& a, unsigned char b);
void eval_divide(bf_float_backend& result, const bf_float_backend& a, long long b);
void eval_divide(bf_float_backend& result, const bf_float_backend& a, long b);
void eval_divide(bf_float_backend& result, const bf_float_backend& a, int b);
void eval_divide(bf_float_backend& result, const bf_float_backend& a, short b);
void eval_divide(bf_float_backend& result, const bf_float_backend& a, signed char b);
void eval_divide(bf_float_backend& result, const bf_float_backend& a, char b);
void eval_divide(bf_float_backend& result, const bf_float_backend& a, long double b);
void eval_divide(bf_float_backend& result, const bf_float_backend& a, double b);
void eval_divide(bf_float_backend& result, const bf_float_backend& a, float b);

void eval_divide(bf_float_backend& result, unsigned long long b, const bf_float_backend& a);
void eval_divide(bf_float_backend& result, unsigned long b, const bf_float_backend& a);
void eval_divide(bf_float_backend& result, unsigned b, const bf_float_backend& a);
void eval_divide(bf_float_backend& result, unsigned short b, const bf_float_backend& a);
void eval_divide(bf_float_backend& result, unsigned char b, const bf_float_backend& a);
void eval_divide(bf_float_backend& result, long long b, const bf_float_backend& a);
void eval_divide(bf_float_backend& result, long b, const bf_float_backend& a);
void eval_divide(bf_float_backend& result, int b, const bf_float_backend& a);
void eval_divide(bf_float_backend& result, short b, const bf_float_backend& a);
void eval_divide(bf_float_backend& result, signed char b, const bf_float_backend& a);
void eval_divide(bf_float_backend& result, char b, const bf_float_backend& a);
void eval_divide(bf_float_backend& result, long double b, const bf_float_backend& a);
void eval_divide(bf_float_backend& result, double b, const bf_float_backend& a);
void eval_divide(bf_float_backend& result, float b, const bf_float_backend& a);
#endif
//
// Multiply and add/subtract as one:
//
#if 0
void eval_multiply_add(bf_float_backend& result, const bf_float_backend& a, const bf_float_backend& b);
void eval_multiply_add(bf_float_backend& result, const bf_float_backend& a, unsigned long long b);
void eval_multiply_add(bf_float_backend& result, const bf_float_backend& a, unsigned long b);
void eval_multiply_add(bf_float_backend& result, const bf_float_backend& a, unsigned b);
void eval_multiply_add(bf_float_backend& result, const bf_float_backend& a, unsigned short b);
void eval_multiply_add(bf_float_backend& result, const bf_float_backend& a, unsigned char b);
void eval_multiply_add(bf_float_backend& result, const bf_float_backend& a, long long b);
void eval_multiply_add(bf_float_backend& result, const bf_float_backend& a, long b);
void eval_multiply_add(bf_float_backend& result, const bf_float_backend& a, int b);
void eval_multiply_add(bf_float_backend& result, const bf_float_backend& a, short b);
void eval_multiply_add(bf_float_backend& result, const bf_float_backend& a, signed char b);
void eval_multiply_add(bf_float_backend& result, const bf_float_backend& a, char b);
void eval_multiply_add(bf_float_backend& result, const bf_float_backend& a, long double b);
void eval_multiply_add(bf_float_backend& result, const bf_float_backend& a, double b);
void eval_multiply_add(bf_float_backend& result, const bf_float_backend& a, float b);

void eval_multiply_add(bf_float_backend& result, unsigned long long b, const bf_float_backend& a);
void eval_multiply_add(bf_float_backend& result, unsigned long b, const bf_float_backend& a);
void eval_multiply_add(bf_float_backend& result, unsigned b, const bf_float_backend& a);
void eval_multiply_add(bf_float_backend& result, unsigned short b, const bf_float_backend& a);
void eval_multiply_add(bf_float_backend& result, unsigned char b, const bf_float_backend& a);
void eval_multiply_add(bf_float_backend& result, long long b, const bf_float_backend& a);
void eval_multiply_add(bf_float_backend& result, long b, const bf_float_backend& a);
void eval_multiply_add(bf_float_backend& result, int b, const bf_float_backend& a);
void eval_multiply_add(bf_float_backend& result, short b, const bf_float_backend& a);
void eval_multiply_add(bf_float_backend& result, signed char b, const bf_float_backend& a);
void eval_multiply_add(bf_float_backend& result, char b, const bf_float_backend& a);
void eval_multiply_add(bf_float_backend& result, long double b, const bf_float_backend& a);
void eval_multiply_add(bf_float_backend& result, double b, const bf_float_backend& a);
void eval_multiply_add(bf_float_backend& result, float b, const bf_float_backend& a);

void eval_multiply_subtract(bf_float_backend& result, const bf_float_backend& a, const bf_float_backend& b);
void eval_multiply_subtract(bf_float_backend& result, const bf_float_backend& a, unsigned long long b);
void eval_multiply_subtract(bf_float_backend& result, const bf_float_backend& a, unsigned long b);
void eval_multiply_subtract(bf_float_backend& result, const bf_float_backend& a, unsigned b);
void eval_multiply_subtract(bf_float_backend& result, const bf_float_backend& a, unsigned short b);
void eval_multiply_subtract(bf_float_backend& result, const bf_float_backend& a, unsigned char b);
void eval_multiply_subtract(bf_float_backend& result, const bf_float_backend& a, long long b);
void eval_multiply_subtract(bf_float_backend& result, const bf_float_backend& a, long b);
void eval_multiply_subtract(bf_float_backend& result, const bf_float_backend& a, int b);
void eval_multiply_subtract(bf_float_backend& result, const bf_float_backend& a, short b);
void eval_multiply_subtract(bf_float_backend& result, const bf_float_backend& a, signed char b);
void eval_multiply_subtract(bf_float_backend& result, const bf_float_backend& a, char b);
void eval_multiply_subtract(bf_float_backend& result, const bf_float_backend& a, long double b);
void eval_multiply_subtract(bf_float_backend& result, const bf_float_backend& a, double b);
void eval_multiply_subtract(bf_float_backend& result, const bf_float_backend& a, float b);

void eval_multiply_subtract(bf_float_backend& result, unsigned long long b, const bf_float_backend& a);
void eval_multiply_subtract(bf_float_backend& result, unsigned long b, const bf_float_backend& a);
void eval_multiply_subtract(bf_float_backend& result, unsigned b, const bf_float_backend& a);
void eval_multiply_subtract(bf_float_backend& result, unsigned short b, const bf_float_backend& a);
void eval_multiply_subtract(bf_float_backend& result, unsigned char b, const bf_float_backend& a);
void eval_multiply_subtract(bf_float_backend& result, long long b, const bf_float_backend& a);
void eval_multiply_subtract(bf_float_backend& result, long b, const bf_float_backend& a);
void eval_multiply_subtract(bf_float_backend& result, int b, const bf_float_backend& a);
void eval_multiply_subtract(bf_float_backend& result, short b, const bf_float_backend& a);
void eval_multiply_subtract(bf_float_backend& result, signed char b, const bf_float_backend& a);
void eval_multiply_subtract(bf_float_backend& result, char b, const bf_float_backend& a);
void eval_multiply_subtract(bf_float_backend& result, long double b, const bf_float_backend& a);
void eval_multiply_subtract(bf_float_backend& result, double b, const bf_float_backend& a);
void eval_multiply_subtract(bf_float_backend& result, float b, const bf_float_backend& a);
#endif
//
// Increment and decrement:
//
//void eval_increment(bf_float_backend& arg);
//void eval_decrement(bf_float_backend& arg);
//
// abs/fabs:
//
// void eval_abs(bf_float_backend& result, const bf_float_backend& arg);
// void eval_fabs(bf_float_backend& result, const bf_float_backend& arg);
//


//
// Now operations on Integer types, starting with modulus:
//
#if 0
void eval_modulus(bf_float_backend& result, unsigned long long arg);
void eval_modulus(bf_float_backend& result, unsigned long arg);
void eval_modulus(bf_float_backend& result, unsigned arg);
void eval_modulus(bf_float_backend& result, unsigned short arg);
void eval_modulus(bf_float_backend& result, unsigned char arg);
void eval_modulus(bf_float_backend& result, char arg);
void eval_modulus(bf_float_backend& result, long long arg);
void eval_modulus(bf_float_backend& result, long arg);
void eval_modulus(bf_float_backend& result, int arg);
void eval_modulus(bf_float_backend& result, short arg);
void eval_modulus(bf_float_backend& result, signed char arg);
void eval_modulus(bf_float_backend& result, long double arg);
void eval_modulus(bf_float_backend& result, double arg);
void eval_modulus(bf_float_backend& result, float arg);

void eval_modulus(bf_float_backend& result, const bf_float_backend& a, const bf_float_backend& b);
void eval_modulus(bf_float_backend& result, const bf_float_backend& a, unsigned long long b);
void eval_modulus(bf_float_backend& result, const bf_float_backend& a, unsigned long b);
void eval_modulus(bf_float_backend& result, const bf_float_backend& a, unsigned b);
void eval_modulus(bf_float_backend& result, const bf_float_backend& a, unsigned short b);
void eval_modulus(bf_float_backend& result, const bf_float_backend& a, unsigned char b);
void eval_modulus(bf_float_backend& result, const bf_float_backend& a, long long b);
void eval_modulus(bf_float_backend& result, const bf_float_backend& a, long b);
void eval_modulus(bf_float_backend& result, const bf_float_backend& a, int b);
void eval_modulus(bf_float_backend& result, const bf_float_backend& a, short b);
void eval_modulus(bf_float_backend& result, const bf_float_backend& a, signed char b);
void eval_modulus(bf_float_backend& result, const bf_float_backend& a, char b);
void eval_modulus(bf_float_backend& result, const bf_float_backend& a, long double b);
void eval_modulus(bf_float_backend& result, const bf_float_backend& a, double b);
void eval_modulus(bf_float_backend& result, const bf_float_backend& a, float b);

void eval_modulus(bf_float_backend& result, unsigned long long b, const bf_float_backend& a);
void eval_modulus(bf_float_backend& result, unsigned long b, const bf_float_backend& a);
void eval_modulus(bf_float_backend& result, unsigned b, const bf_float_backend& a);
void eval_modulus(bf_float_backend& result, unsigned short b, const bf_float_backend& a);
void eval_modulus(bf_float_backend& result, unsigned char b, const bf_float_backend& a);
void eval_modulus(bf_float_backend& result, long long b, const bf_float_backend& a);
void eval_modulus(bf_float_backend& result, long b, const bf_float_backend& a);
void eval_modulus(bf_float_backend& result, int b, const bf_float_backend& a);
void eval_modulus(bf_float_backend& result, short b, const bf_float_backend& a);
void eval_modulus(bf_float_backend& result, signed char b, const bf_float_backend& a);
void eval_modulus(bf_float_backend& result, char b, const bf_float_backend& a);
void eval_modulus(bf_float_backend& result, long double b, const bf_float_backend& a);
void eval_modulus(bf_float_backend& result, double b, const bf_float_backend& a);
void eval_modulus(bf_float_backend& result, float b, const bf_float_backend& a);
#endif
//
// bitwise AND:
//
#if 0
void eval_bitwise_and(bf_float_backend& result, unsigned long long arg);
void eval_bitwise_and(bf_float_backend& result, unsigned long arg);
void eval_bitwise_and(bf_float_backend& result, unsigned arg);
void eval_bitwise_and(bf_float_backend& result, unsigned short arg);
void eval_bitwise_and(bf_float_backend& result, unsigned char arg);
void eval_bitwise_and(bf_float_backend& result, char arg);
void eval_bitwise_and(bf_float_backend& result, long long arg);
void eval_bitwise_and(bf_float_backend& result, long arg);
void eval_bitwise_and(bf_float_backend& result, int arg);
void eval_bitwise_and(bf_float_backend& result, short arg);
void eval_bitwise_and(bf_float_backend& result, signed char arg);
void eval_bitwise_and(bf_float_backend& result, long double arg);
void eval_bitwise_and(bf_float_backend& result, double arg);
void eval_bitwise_and(bf_float_backend& result, float arg);

void eval_bitwise_and(bf_float_backend& result, const bf_float_backend& a, const bf_float_backend& b);
void eval_bitwise_and(bf_float_backend& result, const bf_float_backend& a, unsigned long long b);
void eval_bitwise_and(bf_float_backend& result, const bf_float_backend& a, unsigned long b);
void eval_bitwise_and(bf_float_backend& result, const bf_float_backend& a, unsigned b);
void eval_bitwise_and(bf_float_backend& result, const bf_float_backend& a, unsigned short b);
void eval_bitwise_and(bf_float_backend& result, const bf_float_backend& a, unsigned char b);
void eval_bitwise_and(bf_float_backend& result, const bf_float_backend& a, long long b);
void eval_bitwise_and(bf_float_backend& result, const bf_float_backend& a, long b);
void eval_bitwise_and(bf_float_backend& result, const bf_float_backend& a, int b);
void eval_bitwise_and(bf_float_backend& result, const bf_float_backend& a, short b);
void eval_bitwise_and(bf_float_backend& result, const bf_float_backend& a, signed char b);
void eval_bitwise_and(bf_float_backend& result, const bf_float_backend& a, char b);
void eval_bitwise_and(bf_float_backend& result, const bf_float_backend& a, long double b);
void eval_bitwise_and(bf_float_backend& result, const bf_float_backend& a, double b);
void eval_bitwise_and(bf_float_backend& result, const bf_float_backend& a, float b);

void eval_bitwise_and(bf_float_backend& result, unsigned long long b, const bf_float_backend& a);
void eval_bitwise_and(bf_float_backend& result, unsigned long b, const bf_float_backend& a);
void eval_bitwise_and(bf_float_backend& result, unsigned b, const bf_float_backend& a);
void eval_bitwise_and(bf_float_backend& result, unsigned short b, const bf_float_backend& a);
void eval_bitwise_and(bf_float_backend& result, unsigned char b, const bf_float_backend& a);
void eval_bitwise_and(bf_float_backend& result, long long b, const bf_float_backend& a);
void eval_bitwise_and(bf_float_backend& result, long b, const bf_float_backend& a);
void eval_bitwise_and(bf_float_backend& result, int b, const bf_float_backend& a);
void eval_bitwise_and(bf_float_backend& result, short b, const bf_float_backend& a);
void eval_bitwise_and(bf_float_backend& result, signed char b, const bf_float_backend& a);
void eval_bitwise_and(bf_float_backend& result, char b, const bf_float_backend& a);
void eval_bitwise_and(bf_float_backend& result, long double b, const bf_float_backend& a);
void eval_bitwise_and(bf_float_backend& result, double b, const bf_float_backend& a);
void eval_bitwise_and(bf_float_backend& result, float b, const bf_float_backend& a);
#endif
//
// bitwise OR:
//
#if 0
void eval_bitwise_or(bf_float_backend& result, unsigned long long arg);
void eval_bitwise_or(bf_float_backend& result, unsigned long arg);
void eval_bitwise_or(bf_float_backend& result, unsigned arg);
void eval_bitwise_or(bf_float_backend& result, unsigned short arg);
void eval_bitwise_or(bf_float_backend& result, unsigned char arg);
void eval_bitwise_or(bf_float_backend& result, char arg);
void eval_bitwise_or(bf_float_backend& result, long long arg);
void eval_bitwise_or(bf_float_backend& result, long arg);
void eval_bitwise_or(bf_float_backend& result, int arg);
void eval_bitwise_or(bf_float_backend& result, short arg);
void eval_bitwise_or(bf_float_backend& result, signed char arg);
void eval_bitwise_or(bf_float_backend& result, long double arg);
void eval_bitwise_or(bf_float_backend& result, double arg);
void eval_bitwise_or(bf_float_backend& result, float arg);

void eval_bitwise_or(bf_float_backend& result, const bf_float_backend& a, const bf_float_backend& b);
void eval_bitwise_or(bf_float_backend& result, const bf_float_backend& a, unsigned long long b);
void eval_bitwise_or(bf_float_backend& result, const bf_float_backend& a, unsigned long b);
void eval_bitwise_or(bf_float_backend& result, const bf_float_backend& a, unsigned b);
void eval_bitwise_or(bf_float_backend& result, const bf_float_backend& a, unsigned short b);
void eval_bitwise_or(bf_float_backend& result, const bf_float_backend& a, unsigned char b);
void eval_bitwise_or(bf_float_backend& result, const bf_float_backend& a, long long b);
void eval_bitwise_or(bf_float_backend& result, const bf_float_backend& a, long b);
void eval_bitwise_or(bf_float_backend& result, const bf_float_backend& a, int b);
void eval_bitwise_or(bf_float_backend& result, const bf_float_backend& a, short b);
void eval_bitwise_or(bf_float_backend& result, const bf_float_backend& a, signed char b);
void eval_bitwise_or(bf_float_backend& result, const bf_float_backend& a, char b);
void eval_bitwise_or(bf_float_backend& result, const bf_float_backend& a, long double b);
void eval_bitwise_or(bf_float_backend& result, const bf_float_backend& a, double b);
void eval_bitwise_or(bf_float_backend& result, const bf_float_backend& a, float b);

void eval_bitwise_or(bf_float_backend& result, unsigned long long b, const bf_float_backend& a);
void eval_bitwise_or(bf_float_backend& result, unsigned long b, const bf_float_backend& a);
void eval_bitwise_or(bf_float_backend& result, unsigned b, const bf_float_backend& a);
void eval_bitwise_or(bf_float_backend& result, unsigned short b, const bf_float_backend& a);
void eval_bitwise_or(bf_float_backend& result, unsigned char b, const bf_float_backend& a);
void eval_bitwise_or(bf_float_backend& result, long long b, const bf_float_backend& a);
void eval_bitwise_or(bf_float_backend& result, long b, const bf_float_backend& a);
void eval_bitwise_or(bf_float_backend& result, int b, const bf_float_backend& a);
void eval_bitwise_or(bf_float_backend& result, short b, const bf_float_backend& a);
void eval_bitwise_or(bf_float_backend& result, signed char b, const bf_float_backend& a);
void eval_bitwise_or(bf_float_backend& result, char b, const bf_float_backend& a);
void eval_bitwise_or(bf_float_backend& result, long double b, const bf_float_backend& a);
void eval_bitwise_or(bf_float_backend& result, double b, const bf_float_backend& a);
void eval_bitwise_or(bf_float_backend& result, float b, const bf_float_backend& a);
#endif
//
// bitwise XOR:
//
#if 0
void eval_bitwise_xor(bf_float_backend& result, unsigned long long arg);
void eval_bitwise_xor(bf_float_backend& result, unsigned long arg);
void eval_bitwise_xor(bf_float_backend& result, unsigned arg);
void eval_bitwise_xor(bf_float_backend& result, unsigned short arg);
void eval_bitwise_xor(bf_float_backend& result, unsigned char arg);
void eval_bitwise_xor(bf_float_backend& result, char arg);
void eval_bitwise_xor(bf_float_backend& result, long long arg);
void eval_bitwise_xor(bf_float_backend& result, long arg);
void eval_bitwise_xor(bf_float_backend& result, int arg);
void eval_bitwise_xor(bf_float_backend& result, short arg);
void eval_bitwise_xor(bf_float_backend& result, signed char arg);
void eval_bitwise_xor(bf_float_backend& result, long double arg);
void eval_bitwise_xor(bf_float_backend& result, double arg);
void eval_bitwise_xor(bf_float_backend& result, float arg);

void eval_bitwise_xor(bf_float_backend& result, const bf_float_backend& a, const bf_float_backend& b);
void eval_bitwise_xor(bf_float_backend& result, const bf_float_backend& a, unsigned long long b);
void eval_bitwise_xor(bf_float_backend& result, const bf_float_backend& a, unsigned long b);
void eval_bitwise_xor(bf_float_backend& result, const bf_float_backend& a, unsigned b);
void eval_bitwise_xor(bf_float_backend& result, const bf_float_backend& a, unsigned short b);
void eval_bitwise_xor(bf_float_backend& result, const bf_float_backend& a, unsigned char b);
void eval_bitwise_xor(bf_float_backend& result, const bf_float_backend& a, long long b);
void eval_bitwise_xor(bf_float_backend& result, const bf_float_backend& a, long b);
void eval_bitwise_xor(bf_float_backend& result, const bf_float_backend& a, int b);
void eval_bitwise_xor(bf_float_backend& result, const bf_float_backend& a, short b);
void eval_bitwise_xor(bf_float_backend& result, const bf_float_backend& a, signed char b);
void eval_bitwise_xor(bf_float_backend& result, const bf_float_backend& a, char b);
void eval_bitwise_xor(bf_float_backend& result, const bf_float_backend& a, long double b);
void eval_bitwise_xor(bf_float_backend& result, const bf_float_backend& a, double b);
void eval_bitwise_xor(bf_float_backend& result, const bf_float_backend& a, float b);

void eval_bitwise_xor(bf_float_backend& result, unsigned long long b, const bf_float_backend& a);
void eval_bitwise_xor(bf_float_backend& result, unsigned long b, const bf_float_backend& a);
void eval_bitwise_xor(bf_float_backend& result, unsigned b, const bf_float_backend& a);
void eval_bitwise_xor(bf_float_backend& result, unsigned short b, const bf_float_backend& a);
void eval_bitwise_xor(bf_float_backend& result, unsigned char b, const bf_float_backend& a);
void eval_bitwise_xor(bf_float_backend& result, long long b, const bf_float_backend& a);
void eval_bitwise_xor(bf_float_backend& result, long b, const bf_float_backend& a);
void eval_bitwise_xor(bf_float_backend& result, int b, const bf_float_backend& a);
void eval_bitwise_xor(bf_float_backend& result, short b, const bf_float_backend& a);
void eval_bitwise_xor(bf_float_backend& result, signed char b, const bf_float_backend& a);
void eval_bitwise_xor(bf_float_backend& result, char b, const bf_float_backend& a);
void eval_bitwise_xor(bf_float_backend& result, long double b, const bf_float_backend& a);
void eval_bitwise_xor(bf_float_backend& result, double b, const bf_float_backend& a);
void eval_bitwise_xor(bf_float_backend& result, float b, const bf_float_backend& a);
#endif
//
// left and right shift:
//
//void eval_left_shift(bf_float_backend& result, const bf_float_backend& arg, std::size_t shift);
//void eval_right_shift(bf_float_backend& result, const bf_float_backend& arg, std::size_t shift);
//
// Quotient and remainder:
//
// void eval_qr(const bf_float_backend& numerator, const bf_float_backend& denominator, bf_float_backend& quotient, skeleteon_backend& remainder);
//
// Misc integer ops:
//
// unsigned long long eval_integer_modulus(const bf_float_backend& arg, unsigned long long modulus);
// unsigned long eval_integer_modulus(const bf_float_backend& arg, unsigned long modulus);
// unsigned eval_integer_modulus(const bf_float_backend& arg, unsigned modulus);
// unsigned short eval_integer_modulus(const bf_float_backend& arg, unsigned short modulus);
// unsigned char eval_integer_modulus(const bf_float_backend& arg, unsigned char modulus);
//
// std::size_t  eval_lsb(const bf_float_backend& arg);
// std::size_t  eval_msb(const bf_float_backend& arg);
// bool  eval_bit_test(const bf_float_backend& arg, std::size_t bit);
// void  eval_bit_set(const bf_float_backend& arg, std::size_t bit);
// void  eval_bit_unset(const bf_float_backend& arg, std::size_t bit);
// void  eval_bit_flip(const bf_float_backend& arg, std::size_t bit);
//
// GCD/LCD:
//
#if 0
void eval_gcd(bf_float_backend& result, const bf_float_backend& a, const bf_float_backend& b);
void eval_gcd(bf_float_backend& result, const bf_float_backend& a, unsigned long long b);
void eval_gcd(bf_float_backend& result, const bf_float_backend& a, unsigned long b);
void eval_gcd(bf_float_backend& result, const bf_float_backend& a, unsigned b);
void eval_gcd(bf_float_backend& result, const bf_float_backend& a, unsigned short b);
void eval_gcd(bf_float_backend& result, const bf_float_backend& a, unsigned char b);
void eval_gcd(bf_float_backend& result, const bf_float_backend& a, long long b);
void eval_gcd(bf_float_backend& result, const bf_float_backend& a, long b);
void eval_gcd(bf_float_backend& result, const bf_float_backend& a, int b);
void eval_gcd(bf_float_backend& result, const bf_float_backend& a, short b);
void eval_gcd(bf_float_backend& result, const bf_float_backend& a, signed char b);
void eval_gcd(bf_float_backend& result, const bf_float_backend& a, char b);
void eval_gcd(bf_float_backend& result, unsigned long long a, const bf_float_backend& b);
void eval_gcd(bf_float_backend& result, unsigned long a, const bf_float_backend& b);
void eval_gcd(bf_float_backend& result, unsigned a, const bf_float_backend& b);
void eval_gcd(bf_float_backend& result, unsigned short a, const bf_float_backend& b);
void eval_gcd(bf_float_backend& result, unsigned char a, const bf_float_backend& b);
void eval_gcd(bf_float_backend& result, long long a, const bf_float_backend& b);
void eval_gcd(bf_float_backend& result, long a, const bf_float_backend& b);
void eval_gcd(bf_float_backend& result, int a, const bf_float_backend& b);
void eval_gcd(bf_float_backend& result, short a, const bf_float_backend& b);
void eval_gcd(bf_float_backend& result, signed char a, const bf_float_backend& b);
void eval_gcd(bf_float_backend& result, char a, const bf_float_backend& b);

void eval_lcm(bf_float_backend& result, const bf_float_backend& a, const bf_float_backend& b);
void eval_lcm(bf_float_backend& result, const bf_float_backend& a, unsigned long long b);
void eval_lcm(bf_float_backend& result, const bf_float_backend& a, unsigned long b);
void eval_lcm(bf_float_backend& result, const bf_float_backend& a, unsigned b);
void eval_lcm(bf_float_backend& result, const bf_float_backend& a, unsigned short b);
void eval_lcm(bf_float_backend& result, const bf_float_backend& a, unsigned char b);
void eval_lcm(bf_float_backend& result, const bf_float_backend& a, long long b);
void eval_lcm(bf_float_backend& result, const bf_float_backend& a, long b);
void eval_lcm(bf_float_backend& result, const bf_float_backend& a, int b);
void eval_lcm(bf_float_backend& result, const bf_float_backend& a, short b);
void eval_lcm(bf_float_backend& result, const bf_float_backend& a, signed char b);
void eval_lcm(bf_float_backend& result, const bf_float_backend& a, char b);
void eval_lcm(bf_float_backend& result, unsigned long long a, const bf_float_backend& b);
void eval_lcm(bf_float_backend& result, unsigned long a, const bf_float_backend& b);
void eval_lcm(bf_float_backend& result, unsigned a, const bf_float_backend& b);
void eval_lcm(bf_float_backend& result, unsigned short a, const bf_float_backend& b);
void eval_lcm(bf_float_backend& result, unsigned char a, const bf_float_backend& b);
void eval_lcm(bf_float_backend& result, long long a, const bf_float_backend& b);
void eval_lcm(bf_float_backend& result, long a, const bf_float_backend& b);
void eval_lcm(bf_float_backend& result, int a, const bf_float_backend& b);
void eval_lcm(bf_float_backend& result, short a, const bf_float_backend& b);
void eval_lcm(bf_float_backend& result, signed char a, const bf_float_backend& b);
void eval_lcm(bf_float_backend& result, char a, const bf_float_backend& b);
#endif
//
// Modular exponentiation:
//
#if 0
void eval_powm(bf_float_backend& result, const bf_float_backend& a, const bf_float_backend& b, const bf_float_backend& c);  // a^b % c
void eval_powm(bf_float_backend& result, const bf_float_backend& a, const bf_float_backend& b, unsigned long long c);
void eval_powm(bf_float_backend& result, const bf_float_backend& a, const bf_float_backend& b, unsigned long c);
void eval_powm(bf_float_backend& result, const bf_float_backend& a, const bf_float_backend& b, unsigned c);
void eval_powm(bf_float_backend& result, const bf_float_backend& a, const bf_float_backend& b, unsigned short c);
void eval_powm(bf_float_backend& result, const bf_float_backend& a, const bf_float_backend& b, unsigned char c);
void eval_powm(bf_float_backend& result, const bf_float_backend& a, const bf_float_backend& b, long long c);
void eval_powm(bf_float_backend& result, const bf_float_backend& a, const bf_float_backend& b, long c);
void eval_powm(bf_float_backend& result, const bf_float_backend& a, const bf_float_backend& b, int c);
void eval_powm(bf_float_backend& result, const bf_float_backend& a, const bf_float_backend& b, short c);
void eval_powm(bf_float_backend& result, const bf_float_backend& a, const bf_float_backend& b, signed char c);

void eval_powm(bf_float_backend& result, const bf_float_backend& a, unsigned long long b, const bf_float_backend& c);
void eval_powm(bf_float_backend& result, const bf_float_backend& a, unsigned long b, const bf_float_backend& c);
void eval_powm(bf_float_backend& result, const bf_float_backend& a, unsigned b, const bf_float_backend& c);
void eval_powm(bf_float_backend& result, const bf_float_backend& a, unsigned short b, const bf_float_backend& c);
void eval_powm(bf_float_backend& result, const bf_float_backend& a, unsigned char b, const bf_float_backend& c);
void eval_powm(bf_float_backend& result, const bf_float_backend& a, long long b, const bf_float_backend& c);
void eval_powm(bf_float_backend& result, const bf_float_backend& a, long b, const bf_float_backend& c);
void eval_powm(bf_float_backend& result, const bf_float_backend& a, int b, const bf_float_backend& c);
void eval_powm(bf_float_backend& result, const bf_float_backend& a, short b, const bf_float_backend& c);
void eval_powm(bf_float_backend& result, const bf_float_backend& a, signed char b, const bf_float_backend& c);

void eval_powm(bf_float_backend& result, const bf_float_backend& a, unsigned long long b, unsigned long long c);
void eval_powm(bf_float_backend& result, const bf_float_backend& a, unsigned long b, unsigned long c);
void eval_powm(bf_float_backend& result, const bf_float_backend& a, unsigned b, unsigned c);
void eval_powm(bf_float_backend& result, const bf_float_backend& a, unsigned short b, unsigned short c);
void eval_powm(bf_float_backend& result, const bf_float_backend& a, unsigned char b, unsigned char c);
void eval_powm(bf_float_backend& result, const bf_float_backend& a, long long b, long long c);
void eval_powm(bf_float_backend& result, const bf_float_backend& a, long b, long c);
void eval_powm(bf_float_backend& result, const bf_float_backend& a, int b, int c);
void eval_powm(bf_float_backend& result, const bf_float_backend& a, short b, short c);
void eval_powm(bf_float_backend& result, const bf_float_backend& a, signed char b, signed char c);
#endif
//
// Integer sqrt:
//
// void eval_integer_sqrt(bf_float_backend& result, const bf_float_backend& arg, bf_float_backend& remainder);

/*********************************************************************************************

     FLOATING POINT FUNCTIONS

***********************************************************************************************/

void eval_pow(bf_float_backend& result, const bf_float_backend& a, const bf_float_backend& b);
void eval_acos(bf_float_backend& result, const bf_float_backend& arg);
void eval_atan(bf_float_backend& result, const bf_float_backend& arg);
void eval_atan2(bf_float_backend& result, const bf_float_backend& a, const bf_float_backend& b);
void eval_exp(bf_float_backend& result, const bf_float_backend& arg);
void eval_log(bf_float_backend& result, const bf_float_backend& arg);
void eval_sin(bf_float_backend& result, const bf_float_backend& arg);
void eval_cos(bf_float_backend& result, const bf_float_backend& arg);
void eval_tan(bf_float_backend& result, const bf_float_backend& arg);
void eval_asin(bf_float_backend& result, const bf_float_backend& arg);


int eval_fpclassify(const bf_float_backend& arg);

#if 0

void eval_trunc(bf_float_backend& result, const bf_float_backend& arg);
void eval_round(bf_float_backend& result, const bf_float_backend& arg);
void eval_exp2(bf_float_backend& result, const bf_float_backend& arg);
void eval_log10(bf_float_backend& result, const bf_float_backend& arg);
void eval_sinh(bf_float_backend& result, const bf_float_backend& arg);
void eval_cosh(bf_float_backend& result, const bf_float_backend& arg);
void eval_tanh(bf_float_backend& result, const bf_float_backend& arg);
void eval_asinh(bf_float_backend& result, const bf_float_backend& arg);
void eval_acosh(bf_float_backend& result, const bf_float_backend& arg);
void eval_atanh(bf_float_backend& result, const bf_float_backend& arg);
void eval_fmod(bf_float_backend& result, const bf_float_backend& a, const bf_float_backend& b);
void eval_modf(bf_float_backend& result, const bf_float_backend& a, const bf_float_backend& b);
void eval_scalbn(bf_float_backend& result, const bf_float_backend& arg, bf_float_backend::exponent_type e);
void eval_scalbln(bf_float_backend& result, const bf_float_backend& arg, bf_float_backend::exponent_type e);
skeleton_type::exponent_type eval_ilogb(const bf_float_backend& arg);

void eval_remquo(bf_float_backend& result, const bf_float_backend& a, const bf_float_backend& b, int* p_n);
void eval_remquo(bf_float_backend& result, const bf_float_backend& a, unsigned long long b, int* p_n);
void eval_remquo(bf_float_backend& result, const bf_float_backend& a, unsigned long b, int* p_n);
void eval_remquo(bf_float_backend& result, const bf_float_backend& a, unsigned b, int* p_n);
void eval_remquo(bf_float_backend& result, const bf_float_backend& a, unsigned short b, int* p_n);
void eval_remquo(bf_float_backend& result, const bf_float_backend& a, unsigned char b, int* p_n);
void eval_remquo(bf_float_backend& result, const bf_float_backend& a, long long b, int* p_n);
void eval_remquo(bf_float_backend& result, const bf_float_backend& a, long b, int* p_n);
void eval_remquo(bf_float_backend& result, const bf_float_backend& a, int b, int* p_n);
void eval_remquo(bf_float_backend& result, const bf_float_backend& a, short b, int* p_n);
void eval_remquo(bf_float_backend& result, const bf_float_backend& a, signed char b, int* p_n);
void eval_remquo(bf_float_backend& result, const bf_float_backend& a, long double b, int* p_n);
void eval_remquo(bf_float_backend& result, const bf_float_backend& a, double b, int* p_n);
void eval_remquo(bf_float_backend& result, const bf_float_backend& a, float b, int* p_n);
void eval_remquo(bf_float_backend& result, unsigned long long a, const bf_float_backend& b, int* p_n);
void eval_remquo(bf_float_backend& result, unsigned long a, const bf_float_backend& b, int* p_n);
void eval_remquo(bf_float_backend& result, unsigned a, const bf_float_backend& b, int* p_n);
void eval_remquo(bf_float_backend& result, unsigned short a, const bf_float_backend& b, int* p_n);
void eval_remquo(bf_float_backend& result, unsigned char a, const bf_float_backend& b, int* p_n);
void eval_remquo(bf_float_backend& result, long long a, const bf_float_backend& b, int* p_n);
void eval_remquo(bf_float_backend& result, long a, const bf_float_backend& b, int* p_n);
void eval_remquo(bf_float_backend& result, int a, const bf_float_backend& b, int* p_n);
void eval_remquo(bf_float_backend& result, short a, const bf_float_backend& b, int* p_n);
void eval_remquo(bf_float_backend& result, signed char a, const bf_float_backend& b, int* p_n);

void eval_remainder(bf_float_backend& result, const bf_float_backend& a, const bf_float_backend& b);
void eval_remainder(bf_float_backend& result, const bf_float_backend& a, unsigned long long b);
void eval_remainder(bf_float_backend& result, const bf_float_backend& a, unsigned long b);
void eval_remainder(bf_float_backend& result, const bf_float_backend& a, unsigned b);
void eval_remainder(bf_float_backend& result, const bf_float_backend& a, unsigned short b);
void eval_remainder(bf_float_backend& result, const bf_float_backend& a, unsigned char b);
void eval_remainder(bf_float_backend& result, const bf_float_backend& a, long long b);
void eval_remainder(bf_float_backend& result, const bf_float_backend& a, long b);
void eval_remainder(bf_float_backend& result, const bf_float_backend& a, int b);
void eval_remainder(bf_float_backend& result, const bf_float_backend& a, short b);
void eval_remainder(bf_float_backend& result, const bf_float_backend& a, signed char b);
void eval_remainder(bf_float_backend& result, const bf_float_backend& a, long double b);
void eval_remainder(bf_float_backend& result, const bf_float_backend& a, double b);
void eval_remainder(bf_float_backend& result, const bf_float_backend& a, float b);
void eval_remainder(bf_float_backend& result, unsigned long long a, const bf_float_backend& b);
void eval_remainder(bf_float_backend& result, unsigned long a, const bf_float_backend& b);
void eval_remainder(bf_float_backend& result, unsigned a, const bf_float_backend& b);
void eval_remainder(bf_float_backend& result, unsigned short a, const bf_float_backend& b);
void eval_remainder(bf_float_backend& result, unsigned char a, const bf_float_backend& b);
void eval_remainder(bf_float_backend& result, long long a, const bf_float_backend& b);
void eval_remainder(bf_float_backend& result, long a, const bf_float_backend& b);
void eval_remainder(bf_float_backend& result, int a, const bf_float_backend& b);
void eval_remainder(bf_float_backend& result, short a, const bf_float_backend& b);
void eval_remainder(bf_float_backend& result, signed char a, const bf_float_backend& b);

void eval_fdim(bf_float_backend& result, const bf_float_backend& a, const bf_float_backend& b);
void eval_fdim(bf_float_backend& result, const bf_float_backend& a, unsigned long long b);
void eval_fdim(bf_float_backend& result, const bf_float_backend& a, unsigned long b);
void eval_fdim(bf_float_backend& result, const bf_float_backend& a, unsigned b);
void eval_fdim(bf_float_backend& result, const bf_float_backend& a, unsigned short b);
void eval_fdim(bf_float_backend& result, const bf_float_backend& a, unsigned char b);
void eval_fdim(bf_float_backend& result, const bf_float_backend& a, long long b);
void eval_fdim(bf_float_backend& result, const bf_float_backend& a, long b);
void eval_fdim(bf_float_backend& result, const bf_float_backend& a, int b);
void eval_fdim(bf_float_backend& result, const bf_float_backend& a, short b);
void eval_fdim(bf_float_backend& result, const bf_float_backend& a, signed char b);
void eval_fdim(bf_float_backend& result, const bf_float_backend& a, long double b);
void eval_fdim(bf_float_backend& result, const bf_float_backend& a, double b);
void eval_fdim(bf_float_backend& result, const bf_float_backend& a, float b);
void eval_fdim(bf_float_backend& result, unsigned long long a, const bf_float_backend& b);
void eval_fdim(bf_float_backend& result, unsigned long a, const bf_float_backend& b);
void eval_fdim(bf_float_backend& result, unsigned a, const bf_float_backend& b);
void eval_fdim(bf_float_backend& result, unsigned short a, const bf_float_backend& b);
void eval_fdim(bf_float_backend& result, unsigned char a, const bf_float_backend& b);
void eval_fdim(bf_float_backend& result, long long a, const bf_float_backend& b);
void eval_fdim(bf_float_backend& result, long a, const bf_float_backend& b);
void eval_fdim(bf_float_backend& result, int a, const bf_float_backend& b);
void eval_fdim(bf_float_backend& result, short a, const bf_float_backend& b);
void eval_fdim(bf_float_backend& result, signed char a, const bf_float_backend& b);

void eval_fmax(bf_float_backend& result, const bf_float_backend& a, const bf_float_backend& b);
void eval_fmax(bf_float_backend& result, const bf_float_backend& a, unsigned long long b);
void eval_fmax(bf_float_backend& result, const bf_float_backend& a, unsigned long b);
void eval_fmax(bf_float_backend& result, const bf_float_backend& a, unsigned b);
void eval_fmax(bf_float_backend& result, const bf_float_backend& a, unsigned short b);
void eval_fmax(bf_float_backend& result, const bf_float_backend& a, unsigned char b);
void eval_fmax(bf_float_backend& result, const bf_float_backend& a, long long b);
void eval_fmax(bf_float_backend& result, const bf_float_backend& a, long b);
void eval_fmax(bf_float_backend& result, const bf_float_backend& a, int b);
void eval_fmax(bf_float_backend& result, const bf_float_backend& a, short b);
void eval_fmax(bf_float_backend& result, const bf_float_backend& a, signed char b);
void eval_fmax(bf_float_backend& result, const bf_float_backend& a, long double b);
void eval_fmax(bf_float_backend& result, const bf_float_backend& a, double b);
void eval_fmax(bf_float_backend& result, const bf_float_backend& a, float b);
void eval_fmax(bf_float_backend& result, unsigned long long a, const bf_float_backend& b);
void eval_fmax(bf_float_backend& result, unsigned long a, const bf_float_backend& b);
void eval_fmax(bf_float_backend& result, unsigned a, const bf_float_backend& b);
void eval_fmax(bf_float_backend& result, unsigned short a, const bf_float_backend& b);
void eval_fmax(bf_float_backend& result, unsigned char a, const bf_float_backend& b);
void eval_fmax(bf_float_backend& result, long long a, const bf_float_backend& b);
void eval_fmax(bf_float_backend& result, long a, const bf_float_backend& b);
void eval_fmax(bf_float_backend& result, int a, const bf_float_backend& b);
void eval_fmax(bf_float_backend& result, short a, const bf_float_backend& b);
void eval_fmax(bf_float_backend& result, signed char a, const bf_float_backend& b);

void eval_fmin(bf_float_backend& result, const bf_float_backend& a, const bf_float_backend& b);
void eval_fmin(bf_float_backend& result, const bf_float_backend& a, unsigned long long b);
void eval_fmin(bf_float_backend& result, const bf_float_backend& a, unsigned long b);
void eval_fmin(bf_float_backend& result, const bf_float_backend& a, unsigned b);
void eval_fmin(bf_float_backend& result, const bf_float_backend& a, unsigned short b);
void eval_fmin(bf_float_backend& result, const bf_float_backend& a, unsigned char b);
void eval_fmin(bf_float_backend& result, const bf_float_backend& a, long long b);
void eval_fmin(bf_float_backend& result, const bf_float_backend& a, long b);
void eval_fmin(bf_float_backend& result, const bf_float_backend& a, int b);
void eval_fmin(bf_float_backend& result, const bf_float_backend& a, short b);
void eval_fmin(bf_float_backend& result, const bf_float_backend& a, signed char b);
void eval_fmin(bf_float_backend& result, const bf_float_backend& a, long double b);
void eval_fmin(bf_float_backend& result, const bf_float_backend& a, double b);
void eval_fmin(bf_float_backend& result, const bf_float_backend& a, float b);
void eval_fmin(bf_float_backend& result, unsigned long long a, const bf_float_backend& b);
void eval_fmin(bf_float_backend& result, unsigned long a, const bf_float_backend& b);
void eval_fmin(bf_float_backend& result, unsigned a, const bf_float_backend& b);
void eval_fmin(bf_float_backend& result, unsigned short a, const bf_float_backend& b);
void eval_fmin(bf_float_backend& result, unsigned char a, const bf_float_backend& b);
void eval_fmin(bf_float_backend& result, long long a, const bf_float_backend& b);
void eval_fmin(bf_float_backend& result, long a, const bf_float_backend& b);
void eval_fmin(bf_float_backend& result, int a, const bf_float_backend& b);
void eval_fmin(bf_float_backend& result, short a, const bf_float_backend& b);
void eval_fmin(bf_float_backend& result, signed char a, const bf_float_backend& b);

void eval_hypot(bf_float_backend& result, const bf_float_backend& a, const bf_float_backend& b);
void eval_hypot(bf_float_backend& result, const bf_float_backend& a, unsigned long long b);
void eval_hypot(bf_float_backend& result, const bf_float_backend& a, unsigned long b);
void eval_hypot(bf_float_backend& result, const bf_float_backend& a, unsigned b);
void eval_hypot(bf_float_backend& result, const bf_float_backend& a, unsigned short b);
void eval_hypot(bf_float_backend& result, const bf_float_backend& a, unsigned char b);
void eval_hypot(bf_float_backend& result, const bf_float_backend& a, long long b);
void eval_hypot(bf_float_backend& result, const bf_float_backend& a, long b);
void eval_hypot(bf_float_backend& result, const bf_float_backend& a, int b);
void eval_hypot(bf_float_backend& result, const bf_float_backend& a, short b);
void eval_hypot(bf_float_backend& result, const bf_float_backend& a, signed char b);
void eval_hypot(bf_float_backend& result, const bf_float_backend& a, long double b);
void eval_hypot(bf_float_backend& result, const bf_float_backend& a, double b);
void eval_hypot(bf_float_backend& result, const bf_float_backend& a, float b);
void eval_hypot(bf_float_backend& result, unsigned long long a, const bf_float_backend& b);
void eval_hypot(bf_float_backend& result, unsigned long a, const bf_float_backend& b);
void eval_hypot(bf_float_backend& result, unsigned a, const bf_float_backend& b);
void eval_hypot(bf_float_backend& result, unsigned short a, const bf_float_backend& b);
void eval_hypot(bf_float_backend& result, unsigned char a, const bf_float_backend& b);
void eval_hypot(bf_float_backend& result, long long a, const bf_float_backend& b);
void eval_hypot(bf_float_backend& result, long a, const bf_float_backend& b);
void eval_hypot(bf_float_backend& result, int a, const bf_float_backend& b);
void eval_hypot(bf_float_backend& result, short a, const bf_float_backend& b);
void eval_hypot(bf_float_backend& result, signed char a, const bf_float_backend& b);

void eval_logb(bf_float_backend& result, const bf_float_backend& arg);
void eval_nearbtint(bf_float_backend& result, const bf_float_backend& arg);
void eval_rint(bf_float_backend& result, const bf_float_backend& arg);
void eval_log2(bf_float_backend& result, const bf_float_backend& arg);
#endif


} // namespace backends

//
// Import the backend into this namespace:
//
using boost::multiprecision::backends::bf_float_backend;
//
// Typedef whatever number's make use of this backend:
//
typedef number<bf_float_backend, et_off> bf_float;
//
// Define a category for this number type, one of:
// 
//    number_kind_integer
//    number_kind_floating_point
//    number_kind_rational
//    number_kind_fixed_point
//    number_kind_complex
//
template<>
struct number_category<bf_float_backend > : public std::integral_constant<int, number_kind_floating_point>
{};


bf_float bf_float_max();
bf_float bf_float_min();
bf_float bf_float_elipson();
bf_float bf_float_quiet_NaN();
bf_float bf_float_infinity();

//
// These 2 traits classes are required for complex types only:
//
/*
template <expression_template_option ExpressionTemplates>
struct component_type<number<bf_float_backend, ExpressionTemplates> >
{
   typedef number<skeleton_real_type, ExpressionTemplates> type;
};

template <expression_template_option ExpressionTemplates>
struct complex_result_from_scalar<number<skeleton_real_type, ExpressionTemplates> >
{
   typedef number<bf_float_backend, ExpressionTemplates> type;
};
*/

/**************************************************************

OVERLOADABLE FUNCTIONS - FLOATING POINT TYPES ONLY

****************************************************************/

#if 0

template <boost::multiprecision::expression_template_option ExpressionTemplates>
int sign(const number<bf_float_backend, ExpressionTemplates>& arg);
template <boost::multiprecision::expression_template_option ExpressionTemplates>
int signbit(const number<bf_float_backend, ExpressionTemplates>& arg);
template <boost::multiprecision::expression_template_option ExpressionTemplates>
number<bf_float_backend, ExpressionTemplates> changesign(const number<bf_float_backend, ExpressionTemplates>& arg);
template <boost::multiprecision::expression_template_option ExpressionTemplates>
number<bf_float_backend, ExpressionTemplates> copysign(const number<bf_float_backend, ExpressionTemplates>& a, const number<bf_float_backend, ExpressionTemplates>& b);

template <boost::multiprecision::expression_template_option ExpressionTemplates>
number<bf_float_backend, ExpressionTemplates> cbrt(const number<bf_float_backend, ExpressionTemplates>& arg);
template <boost::multiprecision::expression_template_option ExpressionTemplates>
number<bf_float_backend, ExpressionTemplates> erf(const number<bf_float_backend, ExpressionTemplates>& arg);
template <boost::multiprecision::expression_template_option ExpressionTemplates>
number<bf_float_backend, ExpressionTemplates> erfc(const number<bf_float_backend, ExpressionTemplates>& arg);
template <boost::multiprecision::expression_template_option ExpressionTemplates>
number<bf_float_backend, ExpressionTemplates> expm1(const number<bf_float_backend, ExpressionTemplates>& arg);
template <boost::multiprecision::expression_template_option ExpressionTemplates>
number<bf_float_backend, ExpressionTemplates> log1p(const number<bf_float_backend, ExpressionTemplates>& arg);
template <boost::multiprecision::expression_template_option ExpressionTemplates>
number<bf_float_backend, ExpressionTemplates> tgamma(const number<bf_float_backend, ExpressionTemplates>& arg);
template <boost::multiprecision::expression_template_option ExpressionTemplates>
number<bf_float_backend, ExpressionTemplates> lgamma(const number<bf_float_backend, ExpressionTemplates>& arg);

template <boost::multiprecision::expression_template_option ExpressionTemplates>
long lrint(const number<bf_float_backend, ExpressionTemplates>& arg);
template <boost::multiprecision::expression_template_option ExpressionTemplates>
long long llrint(const number<bf_float_backend, ExpressionTemplates>& arg);

template <boost::multiprecision::expression_template_option ExpressionTemplates>
number<bf_float_backend, ExpressionTemplates> nextafter(const number<bf_float_backend, ExpressionTemplates>& a, const number<bf_float_backend, ExpressionTemplates>& b);
template <boost::multiprecision::expression_template_option ExpressionTemplates>
number<bf_float_backend, ExpressionTemplates> nexttoward(const number<bf_float_backend, ExpressionTemplates>& a, const number<bf_float_backend, ExpressionTemplates>& b);

#endif


}} // namespace boost::multiprecision

/**********************************************************************************

FLOATING POINT ONLY
Nice to have stuff for better integration with Boost.Math.

***********************************************************************************/

namespace boost {
namespace math {
namespace tools {

#if 0

template <>
int digits<boost::multiprecision::number<boost::multiprecision::skeleton_number> >();

template <>
boost::multiprecision::mpfr_float max_value<boost::multiprecision::skeleton_number>();

template <>
boost::multiprecision::mpfr_float min_value<boost::multiprecision::skeleton_number>();

#endif

} // namespace tools

namespace constants {
namespace detail {

#if 0
template <boost::multiprecision::expression_template_option ExpressionTemplates>
struct constant_pi<boost::multiprecision::number<boost::multiprecision::bf_float_backend, ExpressionTemplates> >
{
   typedef boost::multiprecision::number<boost::multiprecision::bf_float_backend, ExpressionTemplates> result_type;
   //
   // Fixed N-digit precision, return reference to internal/cached object:
   //
   template <int N>
   static inline const result_type& get(const std::integral_constant<int, N>&);
   //
   // Variable precision, returns fresh result each time (unless precision is unchanged from last call):
   //
   static inline const result_type  get(const std::integral_constant<int, 0>&);
};
//
// Plus any other constants supported natively by this type....
//
#endif

} // namespace detail
} // namespace constants

}} // namespace boost::math


namespace std {

template <boost::multiprecision::expression_template_option ExpressionTemplates>
class numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_float_backend, ExpressionTemplates> >
{
    typedef boost::multiprecision::number<boost::multiprecision::bf_float_backend, ExpressionTemplates> number_type;

public:
    static constexpr bool is_specialized = true;
    static number_type(min)() { return boost::multiprecision::bf_float_min(); }
    static number_type(max)() { return boost::multiprecision::bf_float_max(); }
    static number_type lowest();
    static constexpr int                digits       = 113;
    static constexpr int                digits10     = LIMB_DIGITS;
    static constexpr int                max_digits10 = LIMB_DIGITS;
    static constexpr bool               is_signed    = false;
    static constexpr bool               is_integer   = false;
    static constexpr bool               is_exact     = false;
    static constexpr int                radix        = 2;
    static number_type                        epsilon() { return boost::multiprecision::bf_float_elipson(); }
    static number_type                        round_error();
    static constexpr int                min_exponent      = INT_MIN;
    static constexpr int                min_exponent10    = INT_MIN;
    static constexpr int                max_exponent      = INT_MAX;
    static constexpr int                max_exponent10    = INT_MAX;
    static constexpr bool               has_infinity      = true;
    static constexpr bool               has_quiet_NaN     = false;
    static constexpr bool               has_signaling_NaN = true;
    static constexpr float_denorm_style has_denorm        = denorm_absent;
    static constexpr bool               has_denorm_loss   = false;
    static number_type                        infinity() { return boost::multiprecision::bf_float_infinity(); }
    static number_type                        quiet_NaN() { return boost::multiprecision::bf_float_quiet_NaN(); }
    static number_type                        signaling_NaN();
    static number_type                        denorm_min();
    static constexpr bool               is_iec559       = false;
    static constexpr bool               is_bounded      = false;
    static constexpr bool               is_modulo       = false;
    static constexpr bool               traps           = false;
    static constexpr bool               tinyness_before = false;
    static constexpr float_round_style  round_style     = round_toward_zero;
};

template <boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr int numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_float_backend, ExpressionTemplates> >::digits;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr int numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_float_backend, ExpressionTemplates> >::digits10;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr int numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_float_backend, ExpressionTemplates> >::max_digits10;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_float_backend, ExpressionTemplates> >::is_signed;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_float_backend, ExpressionTemplates> >::is_integer;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_float_backend, ExpressionTemplates> >::is_exact;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr int numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_float_backend, ExpressionTemplates> >::radix;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr int numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_float_backend, ExpressionTemplates> >::min_exponent;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr int numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_float_backend, ExpressionTemplates> >::min_exponent10;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr int numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_float_backend, ExpressionTemplates> >::max_exponent;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr int numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_float_backend, ExpressionTemplates> >::max_exponent10;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_float_backend, ExpressionTemplates> >::has_infinity;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_float_backend, ExpressionTemplates> >::has_quiet_NaN;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_float_backend, ExpressionTemplates> >::has_signaling_NaN;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr float_denorm_style numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_float_backend, ExpressionTemplates> >::has_denorm;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_float_backend, ExpressionTemplates> >::has_denorm_loss;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_float_backend, ExpressionTemplates> >::is_iec559;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_float_backend, ExpressionTemplates> >::is_bounded;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_float_backend, ExpressionTemplates> >::is_modulo;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_float_backend, ExpressionTemplates> >::traps;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_float_backend, ExpressionTemplates> >::tinyness_before;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr float_round_style numeric_limits<boost::multiprecision::number<boost::multiprecision::bf_float_backend, ExpressionTemplates> >::round_style;

} // namespace std
