#include <iostream>
using std::cout;


template<typename T>
void checkBool(T var) {
    if (bool == bool) cout << "YES";
    else cout << "NO";
}


int main() {
    bool a = true;
    checkBool(a);
    checkBool(14);

    return 0;
}