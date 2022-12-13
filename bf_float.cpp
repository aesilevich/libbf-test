
#include "bf_float.hpp"


namespace boost::multiprecision::backends {


class bf_float_context {
public:
    bf_float_context() {
        ::bf_context_init(&ctx_, &bf_float_context::bf_realloc_func, this);
    }

    ~bf_float_context() {
        ::bf_context_end(&ctx_);
    }

    bf_context_t* ctx() {
        return &ctx_;
    }

    void* realloc(void* ptr, size_t size) {
        return ::realloc(ptr, size);
    }

    static bf_float_context & instance() {
        if (!s_ctx_) {
            s_ctx_ = std::make_unique<bf_float_context>();
        }

        return *s_ctx_;
    }

    static bf_context_t* bf_ctx() {
        return instance().ctx();
    }

private:
    static void* bf_realloc_func(void* opaque, void* ptr, size_t size) {
        return reinterpret_cast<bf_float_context*>(opaque)->realloc(ptr, size);
    }

    bf_context_t ctx_;
    static std::unique_ptr<bf_float_context> s_ctx_;
};


std::unique_ptr<bf_float_context> bf_float_context::s_ctx_;


static const limb_t libbf_default_prec = 113;
static const bf_flags_t libbf_default_flags = bf_set_exp_bits(15) | BF_RNDN | BF_FLAG_SUBNORMAL;


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


// Checks for libbf error and throws corresponding exception
void check_bf_error(int ret, const std::string_view & op) {
    ret &= ~(BF_ST_INEXACT);
    // ret &= ~(BF_ST_UNDERFLOW);
    // ret &= ~(BF_ST_OVERFLOW);

    if (ret == 0) {
        return;
    }


    throw std::runtime_error{std::string{op} + std::string{" operation failed: "} + bf_error_string(ret)};
}


bf_float_backend::bf_float_backend() {
    ::bf_init(bf_float_context::bf_ctx(), &bf_val_);
}


bf_float_backend::bf_float_backend(const bf_float_backend& o):
bf_float_backend{} {
    auto ret = ::bf_set(&bf_val_, o.bf_val());
    check_bf_error(ret, "bf_set");
}


bf_float_backend::~bf_float_backend() {
    ::bf_delete(bf_val());
}


bf_float_backend& bf_float_backend::operator=(const bf_float_backend& o) {
    auto ret = ::bf_set(bf_val(), o.bf_val());
    check_bf_error(ret, "bf_set");
    return *this;
}


// bf_float_backend& bf_float_backend::operator=(bf_float_backend&& o) {
// }


bf_float_backend& bf_float_backend::operator=(unsigned long long i) {
    auto ret = ::bf_set_ui(bf_val(), i);
    check_bf_error(ret, "bf_set_ui");
    return *this;
}


bf_float_backend& bf_float_backend::operator=(long long i) {
    auto ret = ::bf_set_si(bf_val(), i);
    check_bf_error(ret, "bf_set_si");
    return *this;
}


bf_float_backend& bf_float_backend::operator=(double i) {
    auto ret = ::bf_set_float64(bf_val(), i);
    check_bf_error(ret, "bf_set_float64");
    return *this;
}


bf_float_backend& bf_float_backend::operator=(const char* s) {
    auto ret = ::bf_atof(bf_val(), s, nullptr, 10, BF_PREC_INF, libbf_default_flags);
    check_bf_error(ret, "bf_atof");
    return *this;
}


void bf_float_backend::swap(bf_float_backend& o) {
    auto tmp = o.bf_val_;
    o.bf_val_ = bf_val_;
    bf_val_ = tmp;
}


std::string bf_float_backend::str(std::streamsize digits, std::ios_base::fmtflags f) const {
    auto res = ::bf_ftoa(nullptr, bf_val(), 10, libbf_default_prec, libbf_default_flags);
    if (!res) {
        throw std::runtime_error{"bf_ftoa returned null"};
    }

    return res;
}


void bf_float_backend::negate() {
    ::bf_neg(bf_val());
}


int bf_float_backend::compare(const bf_float_backend& o) const {
    return ::bf_cmp(bf_val(), o.bf_val());
}


void eval_add(bf_float_backend& a, const bf_float_backend& b) {
    bf_float_backend res;
    auto ret = ::bf_add(res.bf_val(), a.bf_val(), b.bf_val(), libbf_default_prec, libbf_default_flags);
    check_bf_error(ret, "bf_add");
    a = res;
}


void eval_subtract(bf_float_backend& a, const bf_float_backend& b) {
    bf_float_backend res;
    auto ret = ::bf_sub(res.bf_val(), a.bf_val(), b.bf_val(), libbf_default_prec, libbf_default_flags);
    check_bf_error(ret, "bf_add");
    a = res;
}


void eval_multiply(bf_float_backend& a, const bf_float_backend& b) {
    bf_float_backend res;
    auto ret = ::bf_mul(res.bf_val(), a.bf_val(), b.bf_val(), libbf_default_prec, libbf_default_flags);
    check_bf_error(ret, "bf_add");
    a = res;
}


void eval_divide(bf_float_backend& a, const bf_float_backend& b) {
    bf_float_backend res;
    auto ret = ::bf_div(res.bf_val(), a.bf_val(), b.bf_val(), libbf_default_prec, libbf_default_flags);
    check_bf_error(ret, "bf_div");
    a = res;
}

void eval_convert_to(unsigned long long* result, const bf_float_backend& backend) {
    uint64_t val = 0;
    auto res = ::bf_get_uint64(&val, backend.bf_val());
    check_bf_error(res, "bf_get_uint64");
    *result = val;
}


void eval_convert_to(long long* result, const bf_float_backend& backend) {
    int64_t val = 0;
    auto res = ::bf_get_int64(&val, backend.bf_val(), libbf_default_flags);
    check_bf_error(res, "bf_get_uint64");
    *result = val;
}


void eval_convert_to(double* result, const bf_float_backend& backend) {
    auto res = ::bf_get_float64(backend.bf_val(), result, BF_RNDZ);
    check_bf_error(res, "bf_get_float64");
}


void eval_pow(bf_float_backend& result, const bf_float_backend& a, const bf_float_backend& b) {
    auto ret = ::bf_pow(result.bf_val(), a.bf_val(), b.bf_val(), libbf_default_prec, libbf_default_flags);
    check_bf_error(ret, "bf_pow");
}


// copied from libbf.c
static inline limb_t bf_float_limb_mask(int start, int last)
{
    limb_t v;
    int n;
    n = last - start + 1;
    if (n == LIMB_BITS)
        v = -1;
    else
        v = (((limb_t)1 << n) - 1) << start;
    return v;
}

// copied from libbf.c
static int bf_float_set_overflow(bf_t *r, int sign, limb_t prec, bf_flags_t flags)
{
    slimb_t i, l, e_max;
    int rnd_mode;
    
    rnd_mode = flags & BF_RND_MASK;
    if (prec == BF_PREC_INF ||
        rnd_mode == BF_RNDN ||
        rnd_mode == BF_RNDNA ||
        rnd_mode == BF_RNDA ||
        (rnd_mode == BF_RNDD && sign == 1) ||
        (rnd_mode == BF_RNDU && sign == 0)) {
        bf_set_inf(r, sign);
    } else {
        /* set to maximum finite number */
        l = (prec + LIMB_BITS - 1) / LIMB_BITS;
        if (bf_resize(r, l)) {
            bf_set_nan(r);
            return BF_ST_MEM_ERROR;
        }
        r->tab[0] = bf_float_limb_mask((-prec) & (LIMB_BITS - 1),
                                       LIMB_BITS - 1);
        for(i = 1; i < l; i++)
            r->tab[i] = (limb_t)-1;
        e_max = (limb_t)1 << (bf_get_exp_bits(flags) - 1);
        r->expn = e_max;
        r->sign = sign;
    }
    return BF_ST_OVERFLOW | BF_ST_INEXACT;
}


bf_float_backend bf_float_backend_max() {
    bf_float_backend fb;
    bf_float_set_overflow(fb.bf_val(), 0, libbf_default_prec, bf_set_exp_bits(15) | BF_RNDZ| BF_FLAG_SUBNORMAL);
    return fb;
}


bf_float_backend bf_float_backend_min() {
    bf_float_backend fb;
    ::bf_set_ui(fb.bf_val(), 0);
    return fb;
}


}


// static int bf_float_set_overflow(bf_t* r, int sign, limb_t prec, bf_flags_t flags)
// {
//     slimb_t i, l, e_max;
//     int rnd_mode;
    
//     rnd_mode = flags & BF_RND_MASK;

//         /* set to maximum finite number */
//         l = (prec + LIMB_BITS - 1) / LIMB_BITS;
//         if (bf_resize(r, l)) {
//             bf_set_nan(r);
//             return BF_ST_MEM_ERROR;
//         }
//         r->tab[0] = limb_mask((-prec) & (LIMB_BITS - 1),
//                               LIMB_BITS - 1);
//         for(i = 1; i < l; i++)
//             r->tab[i] = (limb_t)-1;
//         e_max = (limb_t)1 << (bf_get_exp_bits(flags) - 1);
//         r->expn = e_max;
//         r->sign = sign;
// }


namespace boost::multiprecision {

bf_float bf_float_max() {
    return bf_float{backends::bf_float_backend_max()};
}


bf_float bf_float_min() {
    return bf_float{backends::bf_float_backend_min()};
}


bf_float bf_float_elipson() {
    return bf_float{std::numeric_limits<double>::epsilon()};
}


bf_float bf_float_quiet_NaN() {
    assert(false && "NYI");
    return bf_float{};
}


}
