// enums.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

typedef uint32_t LongWord;

namespace TFXPlugID
{
    typedef LongWord T;

    enum E : T
    {
        Plug_0 = 0,

        Plug_Unknown = (std::numeric_limits<T>::max)(),
    };
}

int main()
{
    std::cout << "ENUMS\n";

    int value(100);
    TFXPlugID::E some = TFXPlugID::E(value);

    std::cout << "value " << value << " as TFXPlugID is " << some;
}

