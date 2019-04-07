#include <functional>
#include <iostream>

template <typename T>
class IncrementalCaller
{
    typedef std::function<void()> Callback_Void;
    typedef std::function<void(T)> Callback_Value;

  public:
    IncrementalCaller(Callback_Value &&next)
        : IncrementalCaller(std::move(next), [] {}, [] {})
    {
    }

    IncrementalCaller(Callback_Value &&next, Callback_Void &&end)
        : IncrementalCaller(std::move(next), std::move(end), [] {})
    {
    }

    IncrementalCaller(Callback_Value &&next, Callback_Void &&start, Callback_Void &&end)
        : m_onNext(next), m_onStart(start), m_onEnd(end)
    {
        static_assert(std::is_integral<T>::value, "Type need to be Integral.");
        std::cout << "ctor" << std::endl;
    }

    bool start(T max)
    {
        if (m_busy)
            return false;
        m_count = 0;
        m_max = max;
        m_busy = true;
        m_onStart();
        next();
        return true;
    }
    void next()
    {
        if (!m_busy)
            return;
        if (m_count == m_max)
        {
            m_onEnd();
            m_busy = false;
        }
        else
            m_onNext(m_count++);
    }

  private:
    Callback_Value m_onNext;
    Callback_Void m_onStart;
    Callback_Void m_onEnd;

    T m_count = 0;
    T m_max = 0;
    bool m_busy = false;
};

class MyClass
{
  public:
    int print(int i) { std::cout << i << std::endl; }
};

class MyClass2
{
  private:
    IncrementalCaller<int> m_caller;
    void print(int i) { std::cout << i << std::endl; }
    void printStart() { std::cout << "start: MyClass2" << std::endl; }

  public:
    MyClass2() : m_caller(std::bind(&MyClass2::print, this, std::placeholders::_1), std::bind(&MyClass2::printStart, this)) {}
    ~MyClass2() {}
    void start(int i) { m_caller.start(i); }
    void next() { m_caller.next(); }
};

void test_myclass()
{
    auto print_end = [] { std::cout << "end:" << std::endl; };
    auto mc = MyClass();
    auto cb = std::bind(&MyClass::print, &mc, std::placeholders::_1);

    IncrementalCaller<int> caller(cb, [] { std::cout << "start:" << std::endl; }, print_end);

    caller.start(2);
    caller.next();
    caller.next();
    caller.next();
    caller.next();
}

void test_myclass2()
{
    MyClass2 mc;
    mc.start(2);
    mc.next();
    mc.next();
    mc.next();
}

main(int argc, char const *argv[])
{
    test_myclass();
    test_myclass2();

    return 1;
}
