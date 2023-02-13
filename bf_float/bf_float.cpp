
#include "bf_float.hpp"
#include "bf_context.hpp"
#include <iostream>


namespace boost::multiprecision {


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
int bf_float_set_overflow(bf_t *r, int sign, limb_t prec, bf_flags_t flags)
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


}
