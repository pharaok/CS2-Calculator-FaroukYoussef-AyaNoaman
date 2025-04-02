#pragma once


typedef long long ll;


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
    return a+b;
}


template<typename T>
T sub(T a, T b) {
    return a-b;
}


template<typename T>
T mult(T a, T b) {
    return a*b;
}


template<typename T>
T div(T a, T b) {
    return a/b;
}


ll fact(ll a) {
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
    if (a == 0) return b;
    return b == 0 ? a : gcd(b, a % b);
}



ll lcm(ll a, ll b) {
    ll a2 = a, b2 = b;

    while (a2 != b2) {
        a2 > b2 ? b2 += b : a2 += a;
    }

    return a2;
}
