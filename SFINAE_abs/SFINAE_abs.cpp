// SFINAE_abs.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//https://habr.com/ru/company/otus/blog/466915/
#include <iostream>
#include <type_traits>

//n
//template< typename T >
//T myAbs(T val) {
//    if (std::is_signed_v< T >) {
//        return std::abs(val);
//    }
//    else {
//        return val;
//    }
//}

enum class yes_t {} constexpr yes{};

template <typename T>
using IsSigned = typename std::enable_if_t < std::is_signed_v<T>, yes_t >;

template <typename T>
using IsUnSigned = typename std::enable_if_t < std::is_unsigned_v<T>, yes_t >;

template <typename T,
    IsSigned<T> = yes>
T myAbs(T val)
{
    return (val<0?-val:val);
}

template <typename T,
    IsUnSigned<T> = yes>
    T myAbs(T val)
{
    return val;
}

//
int main() {
    auto a{ myAbs(5u) };
    auto b{ myAbs(-5) };
}
