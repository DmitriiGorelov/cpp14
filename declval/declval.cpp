// declval.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//https://stackoverflow.com/questions/20303250/is-there-a-reason-declval-returns-add-rvalue-reference-instead-of-add-lvalue-ref/20303350#20303350

//https://arne-mertz.de/2017/01/decltype-declval/

#include <iostream>

#include <utility>
using namespace std;

struct A { char v = 'A'; };
struct B { char v = 'B'; };
struct C { char v = 'C'; };

class Foo {
public:
    Foo(int) { } // (not default-constructible)

    A onLvalue()& { return A{}; }
    B onRvalue()&& { return B{}; }
    C onWhatever() { return C{}; }
};

decltype(declval<Foo& >().onLvalue()) a;
decltype(declval<Foo&&>().onRvalue()) b;
decltype(declval<Foo  >().onWhatever()) c;

template <typename T>
std::string
type_name()
{
    typedef typename std::remove_reference<T>::type TR;
    std::unique_ptr<char, void(*)(void*)> own
    (
#ifndef _MSC_VER
        abi::__cxa_demangle(typeid(TR).name(), nullptr,
            nullptr, nullptr),
#else
        nullptr,
#endif
        std::free
    );
    std::string r = own != nullptr ? own.get() : typeid(TR).name();
    if (std::is_const<TR>::value)
        r += " const";
    if (std::is_volatile<TR>::value)
        r += " volatile";
    if (std::is_lvalue_reference<T>::value)
        r += "&";
    else if (std::is_rvalue_reference<T>::value)
        r += "&&";
    return r;
}

//3
template<typename T, typename U>
using sum_t = decltype(std::declval<T>() + std::declval<U>());

template<typename T, typename U>
auto sum(T t, U u)
{
    sum_t<T, U> s = t + u;
    return s;
}

int main()
{
    //1
    a;
    b;
    c;

    //2
    std::cout << type_name<decltype(declval<Foo& >())>() << "\n";
    std::cout << type_name<decltype(declval<Foo&&>())>() << "\n";
    std::cout << type_name<decltype(declval<Foo  >())>() << "\n";

    //3
    std::string s(" s ");
    std::string u(" u ");
    std::cout << sum(s, u) << std::endl;


    std::cout << "Hello World!\n";
}
