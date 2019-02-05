
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <functional>

class Gate
{
  public:
    Gate(const size_t size) : m_in(size) {}
    Gate(const Gate &) = delete;
    Gate &operator=(const Gate &) = delete;
    Gate(Gate &&) = delete;
    Gate &operator=(Gate &&) = delete;

    bool in_set(const size_t pos, const bool value)
    {
        if (pos < m_in.size())
            if (m_in[pos] != value)
            {
                m_in[pos] = value;
                return true;
            }
        return false;
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
        : m_gate(size), m_callback(func)
    {
    }
    void in_set(const uint8_t pos)
    {
        if (m_gate.in_set(pos, true))
            if (m_gate.out_and())
                m_callback();
    }
    void in_reset(const uint8_t pos)
    {
        if (m_gate.in_set(pos, false))
            if (m_gate.out_and())
                m_callback();
    }
    void set_func(const std::function<void()> &func) { m_callback = func; }

  private:
    Gate m_gate;
    std::function<void()> m_callback;
};

class FuncAndTwoGate
{
  public:
    FuncAndTwoGate(const std::function<void()> &func) : m_FuncAndGate(2, func) {}
    FuncAndTwoGate() : m_FuncAndGate(2, []() {}) {}
    void set_1() { m_FuncAndGate.in_set(0); }
    void set_2() { m_FuncAndGate.in_set(1); }
    void set_func(const std::function<void()> &func) { m_FuncAndGate.set_func(func); }

  private:
    FuncAndGate m_FuncAndGate;
};

// ### Start Test ###

void print(bool b)
{
    auto p = b ? "True" : "False";
    std::cout << p << std::endl;
}

void print_out(const Gate &g)
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

    g.in_set(0, true);
    print_out(g);

    g.in_set(1, true);
    print_out(g);

    std::cout << "###################" << std::endl;
    std::cout << "Test Func And Gate" << std::endl;
    FuncAndGate fg(2, print_test);
    std::cout << "Set 1" << std::endl;
    fg.in_set(0);
    std::cout << "Set 2" << std::endl;
    fg.in_set(1);

    std::cout << "###################" << std::endl;
    std::cout << "Test Func Two And Gate" << std::endl;
    FuncAndTwoGate fgt(print_test);
    std::cout << "Set 1" << std::endl;
    fgt.set_1();
    std::cout << "Set 2" << std::endl;
    fgt.set_2();
}