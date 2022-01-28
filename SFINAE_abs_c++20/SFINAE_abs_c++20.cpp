// SFINAE_abs_c++20.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//https://en.cppreference.com/w/cpp/language/constraints

#include <iostream>
#include <concepts>
#include <type_traits>

template< typename T >
concept IsArithmetic = std::is_arithmetic_v< T >;

template< typename T >
concept IsSigned = std::is_signed_v< T >;

template< typename T>
    requires IsSigned<T> && IsArithmetic<T>
T myAbs(T val)
{   
        return((val <= -1) ? -val : val);
}

int main()
{
    //unsigned int a{ myAbs(5u) };
    int b{ myAbs< int >(5u) };
    int c{ myAbs(-5) };


    std::string d{ myAbs( 'd' ) };
    std::cout << d << std::endl;
}