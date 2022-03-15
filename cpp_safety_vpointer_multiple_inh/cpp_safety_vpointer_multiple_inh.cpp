#include <iostream> 
#include <iomanip> 

//http://www.quizful.net/post/cpp_safaty_vpointer

using namespace std;
int nop() {
    static int nop_x; return ++nop_x; // Don't remove me, compiler! 
};

constexpr size_t lines() { return 6; }

void PrintMemory(const unsigned char memory[],
    const char label[] = "contents")
{
    cout << "Memory " << label << ": " << endl;
    for (size_t i = 0; i < lines(); i++)
    {
        for (size_t j = 0; j < 8; j++)
            cout << setw(2) << setfill('0') << uppercase << hex
            << static_cast<int> (memory[i * 8 + j]) << " ";
        cout << endl;
    }
}

class __declspec(novtable) A // I never instantiate 
{
public:
    unsigned long long content_A;
    A(void) : content_A(0xAAAAAAAAAAAAAAAAull)   {
        cout << "++ A has been constructed" << endl;
    };
    virtual ~A(void)   {
        cout << "-- A has been destructed" << endl;
    };

    virtual void functionA(void) = 0;// { cout << "     A::functionA called " << endl; };
};

class __declspec(novtable) E // I never instantiate 
{
public:
    unsigned long long content_E;
    E(void) : content_E(0xEEEEEEEEEEEEEEEEull)   {
        cout << "++ E has been constructed" << endl;
    };
    virtual ~E(void)   {
        cout << "-- E has been destructed" << endl;
    };

    virtual int functionE(int, int) = 0;// { cout << "     E::functionE called " << endl; };
};

class /*__declspec(novtable)*/ B : public A , public E
{
public:
    unsigned long long content_B;
    B(void) : content_B(0xBBBBBBBBBBBBBBBBull)   {
        cout << "++ B has been constructed" << endl;
    };
    ~B(void)   {
        cout << "-- B has been destructed" << endl;
    };

    void functionA(void) override { cout << 
        "      B::functionA called " << endl; };
    int functionE(int, int) override { cout << 
        "      B::functionE called " << endl; return 1;
    };
};

class /*__declspec(novtable)*/ C : public B 
{
public:
    unsigned long long content_C;
    C(void) : content_C(0xCCCCCCCCCCCCCCCCull)   {
        cout << "++ C has been constructed" << endl;
    };
    ~C(void)   {
        cout << "-- C has been destructed" << endl;
    };

    //void function(void) override { cout << "      C::function called " << endl; };
    //virtual void function2(void) { nop(); };
};

int main()
{
    constexpr size_t size = lines()*8;
    unsigned char memory[size];
    memset(memory, 0x11, size * sizeof(unsigned char));
    PrintMemory(memory, "before placement new");

    new (memory) B;
    PrintMemory(memory, "after placement new B");

    new (memory) C;
    PrintMemory(memory, "after placement new C");

    reinterpret_cast<A*>(memory)->functionA();
    dynamic_cast<E*>(reinterpret_cast<B*>(memory))->functionE(1,2);

   /* cout << "E* e = new B(); " << endl;
    E* e = new B();
    e->functionE();*/

    reinterpret_cast<C*>(memory)->~C();
    PrintMemory(memory, "after destructor C");

    system("pause");
    return 0;
};