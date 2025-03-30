#include <random>
#include <type_traits>
#include "calculator.h"


template<typename T>
T add(const T& a, const T& b) {
    return a+b;
}


template<typename T>
T sub(const T& a, const T& b) {
    return a-b;
}


template<typename T>
T mult(const T& a, const T& b) {
    return a*b;
}


template<typename T>
T div(const T& a, const T& b) {
    return a/b;
}


////////////////////////////////////////////
bigint fact(const int16_t& a) {
    if (a == 0) {
        return 1;
    } else if (a < 0) {
        return -1;
    }

    bigint answer = 1;
    for (; a>0; --a) {
        answer *= a;
    }

    return answer;
}

bigint fact(const uint16_t& a) {
    if (a == 0) {
        return 1;
    } else if (a < 0) {
        return -1;
    }

    bigint answer = 1;
    for (; a>0; --a) {
        answer *= a;
    }

    return answer;
}

bigint fact(const int32_t& a) {
    if (a == 0) {
        return 1;
    } else if (a < 0) {
        return -1;
    }

    bigint answer = 1;
    for (; a>0; --a) {
        answer *= a;
    }

    return answer;
}

bigint fact(const uint32_t& a) {
    if (a == 0) {
        return 1;
    } else if (a < 0) {
        return -1;
    }

    bigint answer = 1;
    for (; a>0; --a) {
        answer *= a;
    }

    return answer;
}

bigint fact(const int64_t& a) {
    if (a == 0) {
        return 1;
    } else if (a < 0) {
        return -1;
    }

    bigint answer = 1;
    for (; a>0; --a) {
        answer *= a;
    }

    return answer;
}

bigint fact(const uint64_t& a) {
    if (a == 0) {
        return 1;
    } else if (a < 0) {
        return -1;
    }

    bigint answer = 1;
    for (; a>0; --a) {
        answer *= a;
    }

    return answer;
}
////////////////////////////////////////////


template<typename T>
T gcd(const T& a, const T& b) {
    return a == 0 ? b;
    return b == 0 ? a : gcd(b, a % b);
}


template<typename T>
T lcm(const T& a, const T& b) {
    T a2 = a, b2 = b;

    while (a2 != b2) {
        a2 > b2 ? b2 += b : a2 += a;
    }

    return a2;
}


// template<typename T>
// T rand(const T& a, const T& b) {
//     bigint a2 = bigint(a);
//     bigint b2 = bigint(b);

//     int lenA = a2.length();
//     int lenB = b3.length();

//     if (lenA > lenB) {
//         for (int i = 0; i < lenA-lenB; ++i) {

//         }
//     }
//     std::random_device rd;
//     std::mt19937 gen(rd());
//     std::uniform_real_distribution<T> distr(a, b);

//     return T(distr(gen));
}