#include <iostream>
#include <string>

template <class... Ts>
struct Class
{
    template <typename T>
    void print(const T &value)
    {
        std::cout << value << ", ";
    }

    Class(Ts... args)
    {
        std::cout << "This contains" << std::endl;
        auto x = {(print(args), 0)...};
        std::cout << std::endl;
    }
};

int main()
{
    Class<int> x1(1);
    Class<int, char> x2(2, '2');
    Class<int, char, std::string> x3(2, '2', "test");
}