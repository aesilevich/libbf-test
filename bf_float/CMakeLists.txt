

add_library(bf_float STATIC
            bf_error.cpp
            bf_error.hpp
            bf_float_backend.hpp
            bf_int_backend.hpp
            bf_float_context.cpp
            bf_float_context.hpp
            bf_float.cpp
            bf_float.hpp
            bf_int.hpp)

target_link_libraries(bf_float PUBLIC bf Boost::multiprecision mpfr)
