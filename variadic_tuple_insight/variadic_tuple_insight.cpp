// variadic-tuple.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//https://github.com/eliben/code-for-blog/blob/master/2014/variadic-tuple.cpp

// To compile with dumping record layout:
// $ clang++ -o variadic-tuple -Xclang -fdump-record-layouts variadic-tuple.cpp
//           -Wall -g -std=c++11
#include <cstdint>
#include <iostream>
#include <string>
#include <typeinfo>
#include <cstddef>

template <class... Ts> struct tuple {};

/* First instantiated from: insights.cpp:51 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
struct tuple<double, unsigned long, const char*> : public tuple<unsigned long, const char*>
{
    inline tuple(double t, unsigned long __ts1, const char* __ts2)
        : tuple<unsigned long, const char*>(__ts1, __ts2)
        , tail{ t }
    {
    }

    double tail;
};

#endif


/* First instantiated from: insights.cpp:17 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
struct tuple<unsigned long, const char*> : public tuple<const char*>
{
    inline tuple(unsigned long t, const char* __ts1)
        : tuple<const char*>(__ts1)
        , tail{ t }
    {
    }

    unsigned long tail;
};

#endif


/* First instantiated from: insights.cpp:17 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
struct tuple<const char*> : public tuple<>
{
    inline tuple(const char* t)
        : tuple<>()
        , tail{ t }
    {
    }

    const char* tail;
};

#endif


/* First instantiated from: insights.cpp:17 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
struct tuple<>
{
};

#endif


template<class T, class ... Ts>
struct tuple<T, Ts...> : public tuple<Ts...>
{
    inline tuple(T t, Ts... ts)
        : tuple<Ts...>{ ts... }
        , tail{ t }
    {
    }

    T tail;
};



template <std::size_t, class> struct elem_type_holder;

/* First instantiated from: insights.cpp:44 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
struct elem_type_holder<0, tuple<double, unsigned long, const char*> >
{
    using type = double;
};

#endif


/* First instantiated from: insights.cpp:44 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
struct elem_type_holder<1, tuple<double, unsigned long, const char*> >
{
    using type = typename elem_type_holder<1UL - 1, tuple<unsigned long, const char*> >::type;
};

#endif


/* First instantiated from: insights.cpp:32 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
struct elem_type_holder<0, tuple<unsigned long, const char*> >
{
    using type = unsigned long;
};

#endif


/* First instantiated from: insights.cpp:44 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
struct elem_type_holder<2, tuple<double, unsigned long, const char*> >
{
    using type = typename elem_type_holder<2UL - 1, tuple<unsigned long, const char*> >::type;
};

#endif


/* First instantiated from: insights.cpp:32 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
struct elem_type_holder<1, tuple<unsigned long, const char*> >
{
    using type = typename elem_type_holder<1UL - 1, tuple<const char*> >::type;
};

#endif


/* First instantiated from: insights.cpp:32 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
struct elem_type_holder<0, tuple<const char*> >
{
    using type = const char*;
};

#endif


/* First instantiated from: insights.cpp:61 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
struct elem_type_holder<1, tuple<double, int, const char*> >
{
    using type = typename elem_type_holder<1UL - 1, tuple<int, const char*> >::type;
};

#endif


/* First instantiated from: insights.cpp:32 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
struct elem_type_holder<0, tuple<int, const char*> >
{
    using type = int;
};

#endif


template<class T, class ... Ts>
struct elem_type_holder<0, tuple<T, Ts...> >
{
    using type = T;
};



template<std::size_t k, class T, class ... Ts>
struct elem_type_holder<k, tuple<T, Ts...> >
{
    using type = typename elem_type_holder<k - 1, tuple<Ts...> >::type;
};



template <std::size_t k, class... Ts>
typename std::enable_if<
    k == 0, typename elem_type_holder<0, tuple<Ts...>>::type&>::type
    get(tuple<Ts...>& t) {
    return t.tail;
}

/* First instantiated from: insights.cpp:53 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
typename std::enable_if<0UL == 0, typename elem_type_holder<0, tuple<double, unsigned long, const char*> >::type&>::type get<0, double, unsigned long, const char*>(tuple<double, unsigned long, const char*>& t)
{
    return t.tail;
}
#endif


/* First instantiated from: insights.cpp:47 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
typename std::enable_if<0UL == 0, typename elem_type_holder<0, tuple<unsigned long, const char*> >::type&>::type get<0, unsigned long, const char*>(tuple<unsigned long, const char*>& t)
{
    return t.tail;
}
#endif


/* First instantiated from: insights.cpp:47 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
typename std::enable_if<0UL == 0, typename elem_type_holder<0, tuple<const char*> >::type&>::type get<0, const char*>(tuple<const char*>& t)
{
    return t.tail;
}
#endif


template <std::size_t k, class T, class... Ts>
typename std::enable_if<
    k != 0, typename elem_type_holder<k, tuple<T, Ts...>>::type&>::type
    get(tuple<T, Ts...>& t) {
    tuple<Ts...>& base = t;
    return get<k - 1>(base);
}

/* First instantiated from: insights.cpp:54 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
typename std::enable_if<1UL != 0, typename elem_type_holder<1UL, tuple<double, unsigned long, const char*> >::type&>::type get<1, double, unsigned long, const char*>(tuple<double, unsigned long, const char*>& t)
{
    tuple<unsigned long, const char*>& base = static_cast<tuple<unsigned long, const char*>&>(t);
    return get<1UL - 1>(base);
}
#endif


/* First instantiated from: insights.cpp:55 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
typename std::enable_if<2UL != 0, typename elem_type_holder<2UL, tuple<double, unsigned long, const char*> >::type&>::type get<2, double, unsigned long, const char*>(tuple<double, unsigned long, const char*>& t)
{
    tuple<unsigned long, const char*>& base = static_cast<tuple<unsigned long, const char*>&>(t);
    return get<2UL - 1>(base);
}
#endif


/* First instantiated from: insights.cpp:47 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
typename std::enable_if<1UL != 0, typename elem_type_holder<1UL, tuple<unsigned long, const char*> >::type&>::type get<1, unsigned long, const char*>(tuple<unsigned long, const char*>& t)
{
    tuple<const char*>& base = static_cast<tuple<const char*>&>(t);
    return get<1UL - 1>(base);
}
#endif


int main(int argc, char** argv)
{
    tuple<double, uint64_t, const char*> t1 = tuple<double, uint64_t, const char*>(12.199999999999999, 42, "big");
    std::operator<<(std::operator<<(std::cout, "0th elem is ").operator<<(get<0>(t1)), "\n");
    std::operator<<(std::operator<<(std::cout, "1th elem is ").operator<<(get<1>(t1)), "\n");
    std::operator<<(std::operator<<(std::operator<<(std::cout, "2th elem is "), get<2>(t1)), "\n");
    get<1>(t1) = 103;
    std::operator<<(std::operator<<(std::cout, "1th elem is ").operator<<(get<1>(t1)), "\n");
    typename elem_type_holder<1, tuple<double, int, const char*> >::type foo;
    std::operator<<(std::operator<<(std::cout, typeid(foo).name()), "\n");
    return 0;
}

