// SFINAE.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// https://riptutorial.com/cplusplus/example/3780/what-is-sfinae

#include <iostream>


//1
template <class T>
auto begin(T& c) -> decltype(c.begin()) { return c.begin(); }

template <class T, size_t N>
T* begin(T(&arr)[N]) { return arr; }


//2 error
template <class T>
void add_one(T& val) { val += 1; }


int main()
{
    //1
    int vals[10];
    begin(vals); // OK. The first function template substitution fails because
                 // vals.begin() is ill-formed. This is not an error! That function
                 // is just removed from consideration as a viable overload candidate,
                 // leaving us with the array overload. 

    //2
    int i = 4;
    add_one(i); // ok
    std::string msg = "Hello";
    add_one(msg); // error. msg += 1 is ill-formed for std::string, but this
                  // failure is NOT in the immediate context of substituting T

    std::cout << "Hello World!\n";
}
