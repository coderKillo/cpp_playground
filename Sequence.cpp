
#include <iostream>
#include <functional>

class Sequence
{
public:
    Sequence(std::function<bool(void)> &&func):m_func(func){}
    virtual void start() 
    {
        if(m_func())
            return;
        if(!m_next)
            return;
        m_next->start();
    }
    std::function<bool(void)> m_func;
    Sequence* m_next = nullptr;
};

class SequenceManager
{

};


int main(int argc, char const *argv[])
{
    Sequence t1(
        [](){
                std::cout << 1 << std::endl;
                return false;
            });
    Sequence t2(
        [](){
                std::cout << 2 << std::endl;
                return false;
            });

    t1.m_next = &t2;
    t1.start();

    return 0;
}


