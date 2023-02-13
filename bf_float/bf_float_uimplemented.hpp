
// List of unimplemented optional functions for bf_float.


namespace boost::multiprecision::backends {


//
// Optional conversions
//
#if 0
void eval_convert_to(unsigned long* result, const bf_float_backend& backend);
void eval_convert_to(unsigned* result, const bf_float_backend& backend);
void eval_convert_to(unsigned short* result, const bf_float_backend& backend);
void eval_convert_to(unsigned char* result, const bf_float_backend& backend);

void eval_convert_to(char* result, const bf_float_backend& backend);

void eval_convert_to(long* result, const bf_float_backend& backend);
void eval_convert_to(int* result, const bf_float_backend& backend);
void eval_convert_to(short* result, const bf_float_backend& backend);
void eval_convert_to(signed char* result, const bf_float_backend& backend);

void eval_convert_to(double* result, const bf_float_backend& backend);
void eval_convert_to(float* result, const bf_float_backend& backend);
#endif


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


}


namespace boost::multiprecision {


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


}



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


