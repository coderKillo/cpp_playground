#include <tuple>
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
void update(T t)
{
    std::get<Index<T, Types...>>(m_container) = t;
    m_observer.set(Index<T, Types...>);
    if(m_observer.
}


private:
    MultiTypeEvaluator() = delete;
    MultiTypeEvaluator(const MultiTypeEvaluator&) = delete;
    MultiTypeEvaluator& operator=(const MultiTypeEvaluator&) = delete;
    MultiTypeEvaluator(MultiTypeEvaluator&&) = delete;
    MultiTypeEvaluator& operator=(MultiTypeEvaluator&&) = delete;

    std::bitset<std::tuple_size<container_t>::value> m_observer;
    container_t m_container = {};
    eval_foo_t eval_foo;
};

int main(int argc, char const *argv[])
{
    std::cout << (int)std::tuple_size<std::tuple<int,char,double>>::value << std::endl;   
    return 0;
}
