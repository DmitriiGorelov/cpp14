// void_t.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//https://sodocumentation.net/cplusplus/topic/1169/sfinae--substitution-failure-is-not-an-error-

#include <iostream>
#include <vector>
#include <type_traits>

//1 - struct

// before c++17:
template <class...>
struct make_void { using type = void; };

template <typename... T>
using void_t = typename make_void<T...>::type;

//let's check if a type has a member function foo() that takes no arguments:
template <class T, class = void>
struct has_foo : std::false_type {};

// works for all types of foo()
template <class T>
struct has_foo<T, void_t<decltype(std::declval<T&>().foo())>> : std::true_type {};

//works only for void foo()
//template <class T>
//struct has_foo<T, decltype(std::declval<T&>().foo())> : std::true_type {};


// does not work at all
//template <class T>
//struct has_foo<T, decltype(T::foo)> : std::true_type {
//};

// how to use:
template<typename T, typename Enable>
void call_me(T& f) {
}

template<typename T,
    typename std::enable_if<!has_foo<T>::value, bool>::type = true>
    void call_me(T& f) {
    std::cout << "Method not found!\n";
}

template<typename T,
    typename std::enable_if<has_foo<T>::value, bool>::type = true>
    void call_me(T& f) {
    f.foo();
}

struct strcut1 {
    void foo() {
        std::cout << "FOO 1 called\n";
    }
};

struct strcut2 {
    std::vector<int> foo() {
        std::cout << "FOO 2 called\n";
        return {1,2,3};
    }
};

struct strcutn {
    
};

//2 - const expr
template<typename T, typename = void>
constexpr bool is_having_foo{};

template<typename T>
constexpr bool is_having_foo<
    T,
    void_t<decltype(std::declval<T>().foo())>
> = true;

template<typename T, typename Enable>
void call_me2(T& f) {
}

template<typename T, std::enable_if_t<is_having_foo<T>, bool> = true>
void call_me2(T& f)
{
    f.foo();
}

template<typename T, std::enable_if_t<!is_having_foo<T>, bool> = true>
void call_me2(T& f)
{
    static_assert(false,"method foo() not found!");
}

int main()
{
    //1 - struct
    {
        strcut1 s1;
        call_me(s1);

        strcut2 s2;
        call_me(s2);

        strcutn sn;
        call_me(sn);
    }

    //2 - const expr
    {
        strcut1 s1;
        call_me2(s1);

        strcut2 s2;
        call_me2(s2);

        strcutn sn;
        //call_me2(sn); // uncomment to trigger static_assert
    }

    std::cout << "Hello World!\n";
}
