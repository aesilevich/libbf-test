
#pragma once

#include "libbf.hpp"
#include <memory>


namespace boost::multiprecision::backends {


/// Wrapper around the bf_context_t structure. Performs libbf context initialization/cleanup,
/// provides memory reallocation implementation using realloc, stores static global instance of
/// the bf_float_context.
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


}
