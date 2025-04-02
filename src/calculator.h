#pragma once

template<typename T> T add(T, T);
template<typename T> T sub(T, T);
template<typename T> T mult(T, T);
template<typename T> T div(T, T);
template<typename T> T fact(T);
template<typename T> T gcd(T, T);
template<typename T> T lcm(T, T);
template<typename T> T rand(T, T);

typedef long long ll;

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


////////////////////////////////////////////
ll fact(int16_t a) {
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

ll fact(uint16_t a) {
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

ll fact(int32_t a) {
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

ll fact(uint32_t a) {
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

ll fact(int64_t a) {
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

ll fact(uint64_t a) {
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
////////////////////////////////////////////


template<typename T>
T gcd(T a, T b) {
    if (a == 0) return b;
    return b == 0 ? a : gcd(b, a % b);
}


// template<typename T>
long long lcm(long long a, long long b) {
    long long a2 = a, b2 = b;

    while (a2 != b2) {
        a2 > b2 ? b2 += b : a2 += a;
    }

    return a2;
}
