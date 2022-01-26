// enable_if_a.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//https://sodocumentation.net/cplusplus/topic/1169/sfinae--substitution-failure-is-not-an-error-

#include <iostream>

/*

// ambiguos if negate(1) called

int negate(int i) { return -i; }

template <class F>
auto negate(F f) { return -f(); }
*/

// solution:
int negate(int i) { 
    std::cout << "arithmetic\n";
    return -i; 
}

template <class F, class = typename std::enable_if<!std::is_arithmetic<F>::value>::type>
auto negate(F f) { 
    std::cout << "NOT arithmetic\n";
    return -f(); 
}

int main()
{
    negate(1);
    negate([]() {return 1; });

    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
