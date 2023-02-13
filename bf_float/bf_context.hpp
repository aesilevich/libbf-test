
#pragma once

#include "libbf.hpp"
#include <memory>
#include <iostream>


namespace boost::multiprecision::backends {


/// Wrapper around the bf_context_t structure. Performs libbf context initialization/cleanup,
/// provides memory reallocation implementation using realloc, stores static global instance of
/// the bf_context.
class bf_context {
public:
    bf_context() {
        ::bf_context_init(&ctx_, &bf_context::bf_realloc_func, this);
    }

    ~bf_context() {
        ::bf_context_end(&ctx_);
    }

    bf_context_t* ctx() {
        return &ctx_;
    }

    void* realloc(void* ptr, size_t size) {
        return ::realloc(ptr, size);
    }

    static bf_context & instance() {
        // we can't use shared pointer or delete global context instance because
        // some functions in boost.math store numbers in static variables, and
        // order of destruction of static variables in not specified.
        if (!s_ctx_) {
            s_ctx_ = new bf_context;
        }

        return *s_ctx_;
    }

    static bf_context_t* bf_ctx() {
        return instance().ctx();
    }

private:
    static void* bf_realloc_func(void* opaque, void* ptr, size_t size) {
        return reinterpret_cast<bf_context*>(opaque)->realloc(ptr, size);
    }

    bf_context_t ctx_;
    static bf_context * s_ctx_;
};


}
