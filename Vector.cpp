#include <vector>
#include <set>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <unistd.h>

using namespace std;

struct MyStruct
{
    vector<int> vec;
};

void Test1(const vector<int> &vec)
{
    MyStruct struct1;
    std::copy(vec.begin(), vec.end(), std::back_inserter(struct1.vec));
}
void Test2(const vector<int> &vec)
{
    MyStruct struct2;
    struct2.vec.reserve(vec.size());
    std::copy(vec.begin(), vec.end(), std::back_inserter(struct2.vec));
}
void Test3(const vector<int> &vec)
{
    MyStruct struct3{vector<int>(vec.begin(), vec.end())};
}

int main(int argc, char const *argv[])
{
    vector<int> vec1(10000000);

    for (auto i : {1, 2, 3})
    {
        auto start = chrono::steady_clock::now();

        switch (i)
        {
        case 1:
            Test1(vec1);
            break;
        case 2:
            Test2(vec1);
            break;
        case 3:
            Test3(vec1);
            break;

        default:
            break;
        }

        auto end = chrono::steady_clock::now();

        cout << "Test " << i << " takes " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " us" << endl;
    }
    return 0;
}
