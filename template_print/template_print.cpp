// template_print.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

template<typename ...Args>
void pass(Args &&...) {}

template<typename ...Types>
void print(const Types&... tN)
{
    pass(([&]{std::cout << tN; }(), 0)...);    
}

// Fold expression since c++17
template <typename ...Types>
void print17(const Types& ...tN)
{
    (std::cout << ... << tN); // () must exist!
}

int main()
{
    print("11: ", "Hello, ", "World", "\n");
    print("\n");

    print17("17: ", "Hello, ", "World", "\n");
}
