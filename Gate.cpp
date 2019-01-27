
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <functional>

class Gate
{
public:
    Gate(const int size):m_in(size){}
    Gate(const Gate&) = delete;
    Gate& operator=(const Gate&) = delete;    
    Gate(Gate&&) = delete;
    Gate& operator=(Gate&&) = delete;    

void in_set(const size_t  pos, const  bool value)
{
    if(pos < m_in.size()) m_in[pos] = value;
}

bool out_and() const
{
    return std::find(m_in.begin(), m_in.end(), false) == m_in.end(); 
}

bool out_or() const
{
    return std::find(m_in.begin(), m_in.end(), true) != m_in.end();
}

protected:
    std::vector<bool> m_in;
};

class FuncAndGate
{
public:
    FuncAndGate(const size_t size, const std::function<void()> &func)
    :m_gate(size)
    ,m_callback(func)
    {}
    void in_set(const uint8_t pos, const bool value)
    {
        m_gate.in_set(pos, value);
        if(m_gate.out_and())
            m_callback();   
    }
    Gate m_gate;
    std::function<void()> m_callback;
};

// ### Start Test ### 

void print(bool b)
{
    auto p = b? "True":"False";
    std::cout <<  p << std::endl;
}

void print_out(const Gate& g)
{
    std::cout << "AND is:"; 
    g.out_and();
    print(g.out_and());
    std::cout << "OR is:";
    print(g.out_or());
    std::cout << std::endl;
}

void print_test()
{
    std::cout << "Out True" << std::endl;
}

int main()
{
    std::cout << "Test Gate" << std::endl;
    Gate g(2);
    print_out(g);

    g.in_set(0,true);
    print_out(g);

    g.in_set(1,true);
    print_out(g);

    std::cout << "###################" << std::endl;
    std::cout << "Test Func" << std::endl;
    FuncAndGate fg(2, print_test);
    fg.in_set(0,true);
    fg.in_set(1,true);
}