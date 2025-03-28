#include <random>
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
    return a/b;
}


template<typename T>
T div(const T& a, const T& b) {
    return a/b;
}


template<typename T>
T fact(const T& a) {
    if (a == 0) {
        return 1;
    }

    T answer = 1;
    for (; a>0; --a) {
        answer *= a;
    }

    return answer;
}


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
//     std::random_device rd;
//     std::mt19937 gen(rd());
//     if ( type(a))  // work on checking type
//     std::uniform_real_distribution<T> distr(a, b);

//     return T(distr(gen));
// }