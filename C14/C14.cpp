#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <tuple>
#include <vector>

//enum Outer { a = 1, b = 2, c = 3 };
//template <typename>
//struct S { enum Inner { a = 100, c = 102 }; };
//
//template <int>
//struct G{ typedef int b; };


int main()
{    
    /*int i = S<G< 5 >> ::c > ::b > ::a;
    i = ::c > ::b >= ::a;*/

    std::vector<std::string> v = { "This", "is", "an", "example" };

    std::string* p;
    std::size_t sz;
    std::tie(p, sz) = std::get_temporary_buffer<std::string>(v.size());
    sz = std::min(sz, v.size());

    std::uninitialized_copy_n(v.begin(), sz, p);

    for (std::string* i = p; i != p + sz; ++i) {
        std::cout << *i << ' ';
        i->~basic_string<char>();
    }
    std::return_temporary_buffer(p);


    
}