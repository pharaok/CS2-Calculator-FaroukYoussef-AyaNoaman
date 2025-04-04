#pragma once
#include <random>
using std::is_integral;


typedef long long ll;

// Header function declarations
template<typename T> T add(T, T);
template<typename T> T sub(T, T);
template<typename T> T mult(T, T);
template<typename T> T div(T, T);
ll fact(ll);
ll gcd(ll, ll);
ll lcm(ll, ll);
template<typename T> T rand(T, T);


template<typename T>
T add(T a, T b) {
    /**
     * Addition function:
     * Takes two numeric inputs of the same type
     * Outputs their sum
     */
    return a+b;
}



template<typename T>
T sub(T a, T b) {
    /**
     * Subtraction function
     * Takes any two numeric inputs of the same type
     * Outputs their difference
     */
    return a-b;
}


template<typename T>
T mult(T a, T b) {
    /**
     * Multiplication function
     * Takes any two numeric inputs of the same type
     * Outputs their product
     */
    return a*b;
}


template<typename T>
T div(T a, T b) {
    /**
     * Division function
     * Takes any two numeric inputs of the same type
     * Outputs their quotient
     */
    return a/b;
}


ll fact(ll a) {
    /**
     * Factorial function
     * Takes an integer type of any length and converts it to long long
     * Outputs the factorial (multplication of all number from 1 to a)
     */
    if (a == 0) {
        return 1;
    } else if (a < 0) {
        return -1;
    }

    ll answer = 1;
    for (; a>0; --a) {
        answer *= a;
    }

    return answer;
}


ll gcd(ll a, ll b) {
    /**
     * Greatest Common Divisor (Largest Common Factor) function
     * Takes any two integer types of any length and converts them to long long
     * Outputs the greatest integer that divides both numbers without a remainder
     */
    if (a == 0) return b;
    return b == 0 ? a : gcd(b, a % b);
}



ll lcm(ll a, ll b) {
    /**
     * Least Common Multiple function
     * Takes any two integer types of any length and converts them to long long
     * Outputs the smallest integer that is a multiple of both numbers
     */
    ll a2 = a, b2 = b;

    while (a2 != b2) {
        a2 > b2 ? b2 += b : a2 += a;
    }

    return a2;
}


template <typename T>
T rand(T a, T b) {
    /**
     * Random Number Generator function
     * Takes any two numeric inputs of the same type
     * Outputs a random number from the range [a, b]
     */
    if constexpr (is_integral<T>) {
        std::default_random_engine generator;
        std::uniform_int_distribution<T> distribution(a, b);
        return distribution(generator);
    } else {
        std::default_random_engine generator;
        std::uniform_real_distribution<T> distribution(a, b);
        return distribution(generator);
    }
}