#include <iostream>
#include <algorithm>
#include <numeric>
#include "../sparse.hpp"

bool test_max_element() {

    Sparse<int> sp(10, 10);

    sp[2] = 20;
    sp.at(5) = 500;
    sp[8] = int(80);

    auto max1 = std::max_element(sp.begin(), sp.end());
    auto max2 = std::max_element(sp.cbegin(), sp.cend());
    auto max3 = std::max_element(sp.rbegin(), sp.rend());
    auto max4 = std::max_element(sp.crbegin(), sp.crend());

    bool res{ true };
    res &= (*max1 == *max2);
    res &= (*max1 == *max3);
    res &= (*max1 == *max4);
    res &= (*max1 == 500);

    std::cout << "Test Max_Element:\t" << (res ? "Pass" : "Failed") << std::endl;

    return res;
}



