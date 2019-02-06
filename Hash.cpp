#include <iostream>
#include <functional>
#include <string>

size_t hash_func(const std::string &str)
{
    return std::hash<std::string>()(str);
}

int main()
{
    std::cout << "hash is: " << hash_func("hi") << std::endl;
    std::cout << "hash retry is: " << hash_func("hi") << std::endl;

    return 0;
}
