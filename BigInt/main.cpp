#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
#include "Base/BigInteger.h"
using namespace std;
int main() {
    stringstream ss;
    for(int i=7; i<=949; i++)
        ss << i;
    
    BigInteger::Boot();

    BigInteger v { ss.str() };
    cout << v << endl;;

    auto prev = chrono::system_clock::now();
    const auto inv = chrono::seconds(1);

    for (
        BigInteger i = 3, x = v / i;
        i < x;
        i += 2, x = v / i)
    {
        if(x*i == v)
        {
            cout << "is not prime number" << endl;
            return 0;
        }

        auto cur = chrono::system_clock::now();
        if(cur - prev > inv)
        {
            cout << i << endl;
            prev = cur;
        }
    }    

    cout << "is PRIME NUMBER!!!" << endl;
    return 0;
}
