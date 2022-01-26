// pattern_command.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>


class Command
{
public:
    Command() {}
    virtual ~Command() {}

    virtual void Execute() {};
};

template<class Receiver>
class SimpleCommand : public Command
{
public:
    typedef void (Receiver::* Action)();
    SimpleCommand(Receiver* r, Action a)
        : _receiver(r)
        , _action(a)
    {}

    void Execute() override
    {
        (_receiver->*_action)();
    }
private:
    Action _action;
    Receiver* _receiver;
};

class MyClass {
public:
    void Execute() { std::cout << "EXECUTED!" << std::endl; }
};

MyClass* r = new MyClass;

Command* c = new SimpleCommand<MyClass>(r, &MyClass::Execute);

int main()
{
    std::cout << "PATTERN COMMAND\n";

    c->Execute();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
