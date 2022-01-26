// enable_if_11_a.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <type_traits>

namespace detail {

    template<typename T, typename Enable, typename... Args>
    class A_impl;

    template<typename T, typename... Args>
    class A_impl<T, typename std::enable_if<T::value>::type, Args...> {
        // code here
    public:
        A_impl() { std::cout << "1" << std::endl; }
    };

    template<typename T, typename... Args>
    class A_impl<T, typename std::enable_if<!T::value>::type, Args...> {
        // code here
    public:
        A_impl() { std::cout << "2" << std::endl; }
    };
}

template<typename T, typename...Args>
class A : public detail::A_impl<T, void, Args...> {};

//somethin called "value" must exist. 
struct s {
    typename bool value;
};

struct s1 {
    bool value = false;
};

// but not method
struct s2 {
    //bool value() { return false; };
};

int main()
{
    A<s, int, double> a;
    A<s1, int, double> b;
    //A<s2, int, double> c;

    std::cout << "Hello World!\n";
}
