
extern "C" {
#include "quickjs/libbf.h"
}

#include <string>
#include <iostream>
#include <vector>
#include <boost/multiprecision/cpp_bin_float.hpp>
#include "bf_float.hpp"


namespace bmp = boost::multiprecision;


static void * bf_realloc(void * opaque, void * ptr, size_t size) {
    return ::realloc(ptr, size);
}


// void dump_bf(const bf_t * bf) {
//     std::vector<char> chars;
//     chars.resize(10000);
//     bf_ftoa()
// }


int main() {
    // std::string a_str = "2.95673953882856110908505797851830720901489257812500000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
    // std::string b_str = "5.3091550971799097169423475861549377441406250e2";
    // std::string res_str = "9.16137091634529046709182958669115589757019722367818747705232600776240821857227718551873067599347313641575272826830417174591636547915061517391300131065931465784194067711359196329143298499263726513131614582697830908424187934868152998838921216586737465291051289708299364409624364999366486746226077050764e249";

    std::string a_str = "9.85291419463953934609889984130859375e+4";
    std::string b_str = "8.4167086266170372255146503448486328125e+2";
    std::string res_str = "8.66781019918879108354226292713799369912745098619466567318041467361236175866573114777000418440761829061824953361563557580935951901405814080757565313129904800947783606850513184296612628910656615168927761935861462770335134108408073175949783551491164949747086136599355880600420490275164555515512645668845e4202";

    bmp::bf_float a(a_str);
    bmp::bf_float b(b_str);
    auto res = bmp::pow(a, b);
    std::cerr << "RESULT: " << res << std::endl;
    

    // using bmp_float = bmp::cpp_bin_float_100;
    // bmp_float a(a_str);
    // bmp_float b(b_str);
    // auto res = bmp::pow(a, b);
    // std::cerr << std::setprecision(std::numeric_limits<bmp_float>::digits10)
    //           << std::fixed
    //           << res
    //           << std::endl;

    // bf_context_t ctx;
    // bf_context_init(&ctx, &bf_realloc, nullptr);

    // bf_t a, b, res;
    // bf_init(&ctx, &a);
    // bf_init(&ctx, &b);
    // bf_init(&ctx, &res);

    // auto ret = bf_atof(&a, a_str.c_str(), nullptr, 10, BF_PREC_INF, BF_FLAG_SUBNORMAL);
    // std::cerr << "RET 1: " << ret << "\n";

    // ret = bf_atof(&b, b_str.c_str(), nullptr, 10, BF_PREC_INF, BF_FLAG_SUBNORMAL);
    // std::cerr << "RET 2: " << ret << "\n";

    // ret = bf_pow(&res, &a, &b, 200, BF_FLAG_SUBNORMAL);
    // std::cerr << "RET 3: " << ret << "\n";

    // auto str = bf_ftoa(nullptr, &res, 10, BF_PREC_INF, BF_FTOA_FORMAT_FREE_MIN);
    // if (str == nullptr) {
    //     std::cerr << "bf_ftoa returned null\n";
    // } else {
    //     std::cerr << "RESULT: " << str << "\n";
    // }

    // bf_free(&ctx, str);

    // bf_delete(&a);
    // bf_delete(&b);
    // bf_delete(&res);

    // bf_context_end(&ctx);


    return 0;
}
