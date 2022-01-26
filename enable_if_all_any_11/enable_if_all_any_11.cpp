// enable_if_all_any_11.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//https://riptutorial.com/cplusplus/example/18254/enable-if-all---enable-if-any


#include <iostream>
#include <type_traits>

/// Helper for prior to C++14.
template<bool B, class T, class F >
using conditional_t = typename std::conditional<B, T, F>::type;

/// Emulate C++17 std::conjunction.
template<bool...> struct seq_or : std::false_type {};
template<bool...> struct seq_and : std::true_type {};

template<bool B1, bool... Bs>
struct seq_or<B1, Bs...> :
    conditional_t<B1, std::true_type, seq_or<Bs...>> {};

template<bool B1, bool... Bs>
struct seq_and<B1, Bs...> :
    conditional_t<B1, seq_and<Bs...>, std::false_type> {};

//Then the implementation is quite straight - forward:
template<bool... Bs>
using enable_if_any = std::enable_if<seq_or<Bs...>::value>;

template<bool... Bs>
using enable_if_all = std::enable_if<seq_and<Bs...>::value>;

//Eventually some helpers :
template<bool... Bs>
using enable_if_any_t = typename enable_if_any<Bs...>::type;

template<bool... Bs>
using enable_if_all_t = typename enable_if_all<Bs...>::type;

/*
//The usage is also straight - forward:
/// SFINAE constraints on all of the parameters in Args.
template<typename ...Args,
    enable_if_all_t<custom_conditions_v<Args>...>* = nullptr> 
    void func(Args &&...args) { //... };

/// SFINAE constraints on any of the parameters in Args.
template<typename ...Args,
    enable_if_any_t<custom_conditions_v<Args>...>* = nullptr>
    void func(Args &&...args) { //... };
    */

int main()
{
    //func(2, true);

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
