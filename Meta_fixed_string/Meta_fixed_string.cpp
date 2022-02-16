// Meta_fixed_string.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

template <std::size_t N>
struct fixed_string {
    consexpr fixed_string(const char(&foo)[N + 1]) {
        std::copy_n(foo, N + 1, data);
    }
    auto operator<=>(const fixed_string&) const = default;
    char data[N + 1] = {};
};

template<std::size_t N>
struct fixed_string(const char (&str)[N]) -> fixed_string<N - 1>;


int main()
{
    std::cout << "Hello World!\n";
}
