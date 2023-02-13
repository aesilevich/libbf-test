
#pragma once

#include "bf_context.hpp"
#include "bf_error.hpp"
#include "libbf.hpp"
#include <cassert>
#include <boost/multiprecision/number.hpp>
#include <boost/container_hash/hash.hpp>
#include <iostream>


namespace boost::multiprecision::backends { 


class bf_backend {
public:
    //
    // Each backend need to declare 3 type lists which declare the types
    // with which this can interoperate.  These lists must at least contain
    // the widest type in each category - so "long long" must be the final
    // type in the signed_types list for example.  Any narrower types if not
    // present in the list will get promoted to the next wider type that is
    // in the list whenever mixed arithmetic involving that type is encountered.
    //
    using signed_types = std::tuple<signed char, short, int, long, long long>;
    using unsigned_types = std::tuple<unsigned char, unsigned short, unsigned, unsigned long, unsigned long long>;
    using float_types = std::tuple<float, double, long double>;

    //
    // This typedef is only required if this is a floating point type, it is the type
    // which holds the exponent:
    //
    using exponent_type = ::slimb_t;


    // Constructs libbf backend with specified flags. Calls bf_init to initialize
    // bf value struct.
    explicit bf_backend(::bf_flags_t flags):
    bf_flags_{flags} {
        ::bf_init(bf_context::bf_ctx(), &bf_val_);
    }


    // Copy constructor
    bf_backend(const bf_backend & o):
    bf_backend{o.bf_flags()} {
        auto ret = ::bf_set(&bf_val_, o.bf_val());
        check_bf_error(ret, "bf_set");
    }


//   bf_float_backend(bf_float_backend&& o);


    ~bf_backend() {
        ::bf_delete(bf_val());
    }


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


    void assign(const bf_backend & o) {
        auto ret = ::bf_set(bf_val(), o.bf_val());
        check_bf_error(ret, "bf_set");
    }


    void assign(long long i) {
        auto ret = ::bf_set_si(bf_val(), static_cast<int64_t>(i));
        check_bf_error(ret, "bf_set_si");
    }


    void assign(unsigned long long i) {
        auto ret = ::bf_set_ui(bf_val(), i);
        check_bf_error(ret, "bf_set_ui");
    }


    // void assign(__int128 i) {
    //     assert(false && "NYI");
    // }


    // void assign(unsigned __int128 i) {
    //     assert(false && "NYI");
    // }


    // bf_float_backend& operator=(bf_float_backend&& o);

    void assign(signed char i) { assign(static_cast<long long>(i)); }
    void assign(short i) { assign(static_cast<long long>(i)); }
    void assign(int i) { assign(static_cast<long long>(i)); }
    void assign(long i) { assign(static_cast<long long>(i)); }

    void assign(unsigned char i) { assign(static_cast<unsigned long long>(i)); }
    void assign(unsigned short i) { assign(static_cast<unsigned long long>(i)); }
    void assign(unsigned int i) { assign(static_cast<unsigned long long>(i)); }
    void assign(unsigned long i) { assign(static_cast<unsigned long long>(i)); }


    void assign(double i) {
        auto ret = ::bf_set_float64(bf_val(), i);
        check_bf_error(ret, "bf_set_float64");
    }


    void assign(long double i) {
        auto ret = ::bf_set_float64(bf_val(), static_cast<double>(i));
        check_bf_error(ret, "bf_set_float64");
    }


    void assign(__float128 i) {
        // TODO: do we need correct implementation for testing?
        assign(static_cast<double>(i));
    }


    void from_string(const char * s, ::limb_t prec) {
        const char * end = nullptr;
        auto ret = ::bf_atof(bf_val(), s, &end, 10, prec, bf_flags_);
        check_bf_error(ret, "bf_atof");

        assert(end != nullptr && "invalid pointer to end character");
        if (*end != 0) {
            throw std::runtime_error{"bf_atof can't parse entire string"};
        }
    }


    void swap(bf_backend & o) {
        auto tmp = o.bf_val_;
        o.bf_val_ = bf_val_;
        bf_val_ = tmp;
    }


    void negate() {
        ::bf_neg(bf_val());
    }


    int compare(const bf_backend & o) const {
        return ::bf_cmp(bf_val(), o.bf_val());
    }


    //
    // Comparison with arithmetic types, default just constructs a temporary:
    //
    template <class A>
    typename std::enable_if<boost::multiprecision::detail::is_arithmetic<A>::value, int>::type compare(A i) const
    {
       bf_backend t{bf_flags()};
       t.assign(i);
       return compare(t);
    }

    const ::bf_t * bf_val() const { return &bf_val_; }
    ::bf_t * bf_val() { return &bf_val_; }
    ::bf_flags_t bf_flags() const { return bf_flags_; }

private:
    ::bf_t bf_val_;                 // libbf value structure
    ::bf_flags_t bf_flags_;         // libbf flags
};


}
