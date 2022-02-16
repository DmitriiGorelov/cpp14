#include <iostream>

class C0
{
    void f1() {}
    void f2() {}
    void f3() {}
    void f4() {}
    void f5() {}
    void f6() {}
    void f7() {}
};

class C1
{
    virtual void f1() {}
};

class C2
{
    virtual void f1() {}
    virtual void f2() {}
    virtual void f3() {}
    virtual void f4() {}
    virtual void f5() {}
    virtual void f6() {}
    virtual void f7() {}
    virtual void f8() {}
    virtual void f9() {}
};

class C3
{
    int i;
};

class C4
{
    int i;
    char ch;
};

class C5
{
    int i;
    char ch1;
    char ch2;
    char ch3;
    char ch4;
};

class C6
{
    bool b;
};

class C21 : C2
{
    void f1()final {}
    void f2()final {}
    void f3()final {}
    void f4()final {}
    void f5()final {}
    void f6()final {}
    void f7()final {}
    void f8()final {}
    void f9()final {}

    void f10() {}
    void f11() {}
    void f12() {}
    void f13() {}
    void f14() {}
    void f15() {}
    void f16() {}
    void f17() {}
    void f18() {}
    void f19() {}

    virtual void f20() {}
    virtual void f21() {}
    virtual void f22() {}
    virtual void f23() {}
    virtual void f24() {}
    virtual void f25() {}
    virtual void f26() {}
    virtual void f27() {}
    virtual void f28() {}
    virtual void f29() {}

};

class C22 : C21
{

};

int main()
{
    // if win32 - size of classes with abstract method will be 4 bytes
    // if x64 - size of classes with abstract methods will be 8 bytes

    std::cout << "sizeof(C0) = " << sizeof(C0) << std::endl;
    std::cout << "sizeof(C1) = " << sizeof(C1) << std::endl;
    std::cout << "sizeof(C2) = " << sizeof(C2) << std::endl;
    std::cout << "sizeof(C21) = " << sizeof(C21) << std::endl;
    std::cout << "sizeof(C22) = " << sizeof(C22) << std::endl;
    std::cout << "sizeof(C3) = " << sizeof(C3) << std::endl;
    std::cout << "sizeof(C4) = " << sizeof(C4) << std::endl;
    std::cout << "sizeof(C5) = " << sizeof(C5) << std::endl;
    std::cout << "sizeof(C6) = " << sizeof(C6) << std::endl;

    C0 c0;
    C1 c1;
    C2 c2;
    C21 c21;
    C22 c22;
    C3 c3;
    C4 c4;
    C5 c5;
    C6 c6;
    std::cout << "sizeof(object of C0) = " << sizeof(c0) << std::endl;    
    std::cout << "sizeof(object of C1) = " << sizeof(c1) << std::endl;    
    std::cout << "sizeof(object of C2) = " << sizeof(c2) << std::endl;
    std::cout << "sizeof(object of C21) = " << sizeof(c21) << std::endl;
    std::cout << "sizeof(object of C22) = " << sizeof(c22) << std::endl;
    std::cout << "sizeof(object of C3) = " << sizeof(c3) << std::endl;
    std::cout << "sizeof(object of C4) = " << sizeof(c4) << std::endl;
    std::cout << "sizeof(object of C5) = " << sizeof(c5) << std::endl;
    std::cout << "sizeof(object of C6) = " << sizeof(c6) << std::endl;


    return 0;
}