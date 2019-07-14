#include <tuple>
#include <utility>
#include <functional>
#include <bitset>
#include <iostream>

template <class T, class Tuple>
struct Index;

template <class T, class... Types>
struct Index<T, std::tuple<T, Types...>> {
    static const std::size_t value = 0;
};

template <class T, class U, class... Types>
struct Index<T, std::tuple<U, Types...>> {
    static const std::size_t value = 1 + Index<T, std::tuple<Types...>>::value;
};

template <class... Types>
class MultiTypeEvaluator
{
    typedef std::function<void(Types...)> eval_foo_t;
    typedef std::tuple<Types...> container_t;
public:
    MultiTypeEvaluator(eval_foo_t && func):eval_foo(func) {}

    template<typename T>
    void set(T&& t)
    {
        std::get<T>(m_container) = std::move(t);
        m_observer.set(Index<T, container_t>::value);
        if(m_observer.all())
            apply(std::index_sequence_for<Types...>{});
    }

private:
    MultiTypeEvaluator() = delete;
    MultiTypeEvaluator(const MultiTypeEvaluator&) = delete;
    MultiTypeEvaluator& operator=(const MultiTypeEvaluator&) = delete;
    MultiTypeEvaluator(MultiTypeEvaluator&&) = delete;
    MultiTypeEvaluator& operator=(MultiTypeEvaluator&&) = delete;

    template<std::size_t... Is>
    void apply(std::index_sequence<Is...>)
    {
        eval_foo(std::move(std::get<Is>(m_container))...);
    }

    std::bitset<std::tuple_size<container_t>::value> m_observer;
    container_t m_container;
    eval_foo_t eval_foo;
};

struct MyStruct
{
    MyStruct() { std::cout << "default ctor" << std::endl;}
    MyStruct(const MyStruct& m) 
    { 
        std::cout << "copy ctor" << std::endl;
        i = m.i; 
        c = m.c; 
    }
    MyStruct(MyStruct&& m) 
    { 
        std::cout << "move ctor" << std::endl;
        i = m.i; 
        c = m.c; 
    }
    MyStruct& operator=(const MyStruct& m) 
    { 
        std::cout << "copy oper" << std::endl;
        i = m.i; 
        c = m.c; 
        return *this;
    }
    MyStruct& operator=(MyStruct&& m) 
    { 
        std::cout << "move oper" << std::endl;
        i = m.i; 
        c = m.c; 
        return *this;
    }
    int i;
    char c;
};

void update(MyStruct m, int i, char c)
{
    std::cout << m.i << m.c << i << c << std::endl;   
}


int main(int argc, char const *argv[])
{
    MultiTypeEvaluator<MyStruct, int, char> mt(update);

    mt.set<int>(1);
    mt.set<char>('s');
    mt.set<MyStruct>({});

    return 0;
}
