// align.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

int distance(void* first, void* second)
{
    return reinterpret_cast<int>(first) - reinterpret_cast<int>(second);
}

int main()
{

    alignas(int) unsigned char buf[sizeof(int)];
    new (buf) int(256);    
    std::cout << (int)buf[1] << std::endl;

    auto buf2 = new unsigned char[10];    
    buf2[9] = 0;
    buf2[0] = 256;
    std::cout << (int)buf2[1] << std::endl;
    delete[] buf2;

    alignas(16) int f[4];
    alignas(1024) int s[4];
    std::cout << distance(f, s) << std::endl;

    int f2[4];
    int s2[4];
    std::cout << distance(f2, s2) << std::endl;

    std::cout << "Hello World!\n";
}

