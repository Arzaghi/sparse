#include <iostream>
#include <algorithm>
#include <numeric>
#include "../sparse.hpp"

bool test_acculmulate() {

    Sparse<int> sp(10, 10);

    sp[2] = 20;
    sp.at(5) = 50;
    sp[8] = int(80);    

    auto sum1 = std::accumulate(sp.begin(), sp.end(), 0);
    auto sum2 = std::accumulate(sp.cbegin(), sp.cend(), 0);
    auto sum3 = std::accumulate(sp.rbegin(), sp.rend(), 0);
    auto sum4 = std::accumulate(sp.crbegin(), sp.crend(), 0);

    bool res{ true };
    res &= (sum1 == sum2);
    res &= (sum1 == sum3);
    res &= (sum1 == sum4);
    res &= (sum1 == 220);

    std::cout << "Test Accumulate:\t" << (res ? "Pass" : "Failed") << std::endl;

    return res;
}