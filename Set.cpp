#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

std::ostream &operator<<(std::ostream &outst, const std::set<int> &set)
{
    for (auto &i : set)
        outst << " " << i;
    return outst;
}

int main(int argc, char const *argv[])
{
    std::set<int> s1 = {11, 22, 33, 44, 55};
    std::set<int> s2 = {22, 33, 44, 55, 11};

    std::cout << s1 << std::endl;
    std::cout << s2 << std::endl;

    // COMPARE
    if (s2 == s1)
        std::cout << "s1 is same as s2" << std::endl;
    else
        std::cout << "s1 different s2" << std::endl;

    // CAST TO VECTOR
    std::vector<int> vec;
    std::copy(s1.begin(), s1.end(), std::back_inserter(vec));
    std::cout << "Vector contains:";
    for (auto &i : vec)
    {
        std::cout << i << ", ";
    }

    return 0;
}