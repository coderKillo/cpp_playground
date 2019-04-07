#include <vector>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <unistd.h>

using namespace std;

int main(int argc, char const *argv[])
{
    vector<int> vec1(1000000);
    vector<int> vec2;

    auto start = chrono::steady_clock::now();

    vec2.reserve(vec1.size());
    std::copy(vec1.begin(), vec1.end(), std::back_inserter(vec2));

    auto end = chrono::steady_clock::now();

    cout << chrono::duration_cast<chrono::microseconds>(end - start).count();
    return 0;
}
