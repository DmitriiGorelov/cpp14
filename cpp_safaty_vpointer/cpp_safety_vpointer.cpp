#include <iostream> 
#include <iomanip> 

//http://www.quizful.net/post/cpp_safaty_vpointer

using namespace std;
int nop() {
    static int nop_x; return ++nop_x; // Don't remove me, compiler! 
};

void PrintMemory(const unsigned char memory[],
    const char label[] = "contents")
{
    cout << "Memory " << label << ": " << endl;
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 8; j++)
            cout << setw(2) << setfill('0') << uppercase << hex
            << static_cast<int> (memory[i * 8 + j]) << " ";
        cout << endl;
    }
}

//v1
/*class A
{
public:
    unsigned long long content_A;
    A(void) : content_A(0xAAAAAAAAAAAAAAAAull)
    {
        cout << "++ A has been constructed" << endl;
    };
    ~A(void)
    {
        cout << "-- A has been destructed" << endl;
    };

    virtual void function(void) { nop(); };
};

int main()
{
    const size_t size = 32;
    unsigned char memory[size];
    memset(memory, 0x11, size * sizeof(unsigned char));
    PrintMemory(memory, "before placement new");

    new (memory) A;
    PrintMemory(memory, "after placement new");
    reinterpret_cast<A*>(memory)->~A();

    system("pause");
    return 0;
};
*/

//v2

class __declspec(novtable) A // I never instantiate 
{
public:
    unsigned long long content_A;
    A(void) : content_A(0xAAAAAAAAAAAAAAAAull)
    {
        cout << "++ A has been constructed" << endl;
    };
    ~A(void)
    {
        cout << "-- A has been destructed" << endl;
    };

    virtual void function(void) = 0;// { cout << "     A::function called " << endl; };
};

class __declspec(novtable) B : public A // I always instantiate instead of A 
{
public:
    unsigned long long content_B;
    B(void) : content_B(0xBBBBBBBBBBBBBBBBull)
    {
        cout << "++ B has been constructed" << endl;
    };
    ~B(void)
    {
        cout << "-- B has been destructed" << endl;
    };

    void function(void) override { cout << "      B::function called " << endl; };
};

class /*__declspec(novtable)*/ C : public B // exception at function() call if __declspec(novtable) used here
{
public:
    unsigned long long content_C;
    C(void) : content_C(0xCCCCCCCCCCCCCCCCull)
    {
        cout << "++ C has been constructed" << endl;
    };
    ~C(void)
    {
        cout << "-- C has been destructed" << endl;
    };

    //void function(void) override { cout << "      C::function called " << endl; };
    virtual void function2(void) { nop(); };
};

int main()
{
    const size_t size = 32;
    unsigned char memory[size];
    memset(memory, 0x11, size * sizeof(unsigned char));
    PrintMemory(memory, "before placement new");

    new (memory) C;
    reinterpret_cast<A*>(memory)->function();

    PrintMemory(memory, "after placement new");
    reinterpret_cast<A*>(memory)->~A();    
    PrintMemory(memory, "after destructor A");
    reinterpret_cast<B*>(memory)->~B();
    PrintMemory(memory, "after destructor B");
    reinterpret_cast<C*>(memory)->~C();
    PrintMemory(memory, "after destructor C");

    reinterpret_cast<A*>(memory)->function();

    system("pause");
    return 0;
};