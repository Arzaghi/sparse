#pragma once
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

bool test_min_element() {

    Sparse<int> sp(10, 40);

    sp[2] = 20;
    sp.at(5) = 500;
    sp[8] = int(80);

    auto min1 = std::min_element(sp.begin(), sp.end());
    auto min2 = std::min_element(sp.cbegin(), sp.cend());
    auto min3 = std::min_element(sp.rbegin(), sp.rend());
    auto min4 = std::min_element(sp.crbegin(), sp.crend());

    bool res{ true };
    res &= (*min1 == *min2);
    res &= (*min1 == *min3);
    res &= (*min1 == *min4);
    res &= (*min1 == 20);

    std::cout << "Test Min_Element:\t" << (res ? "Pass" : "Failed") << std::endl;

    return res;
}

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

bool test_all_of() {

    Sparse<int> sp(10, 10);

    sp[2] = 20;
    sp.at(5) = 50;
    sp[8] = int(80);

    auto allOf1 = std::all_of(sp.begin(), sp.end(), [](int x) {return x >= 10; });
    auto allOf2 = std::all_of(sp.begin(), sp.end(), [](int x) {return x >= 20; });    
    auto allOf3 = std::all_of(sp.cbegin(), sp.cend(), [](int x) {return x >= 10; });
    auto allOf4 = std::all_of(sp.cbegin(), sp.cend(), [](int x) {return x >= 20; });    
    auto allOf5 = std::all_of(sp.rbegin(), sp.rend(), [](int x) {return x >= 10; });    
    auto allOf6 = std::all_of(sp.rbegin(), sp.rend(), [](int x) {return x >= 20; });    
    auto allOf7 = std::all_of(sp.crbegin(), sp.crend(), [](int x) {return x >= 10; });
    auto allOf8 = std::all_of(sp.crbegin(), sp.crend(), [](int x) {return x >= 20; });

    bool res{ true };
    res &= (allOf1 == true);    
    res &= (allOf2 == false);
    res &= (allOf3 == true);
    res &= (allOf4 == false);
    res &= (allOf5 == true);
    res &= (allOf6 == false);
    res &= (allOf7 == true);
    res &= (allOf8 == false);
    std::cout << "Test All_Of:\t\t" << (res ? "Pass" : "Failed") << std::endl;

    return res;
}

bool test_any_of() {

    Sparse<int> sp(10, 10);

    sp[2] = 20;
    sp.at(5) = 50;
    sp[8] = int(80);


    auto anyOf1 = std::any_of(sp.begin(), sp.end(),     [](int x) {return x == 50; });
    auto anyOf2 = std::any_of(sp.begin(), sp.end(),     [](int x) {return x == 60; });
    auto anyOf3 = std::any_of(sp.cbegin(), sp.cend(),   [](int x) {return x == 50; });
    auto anyOf4 = std::any_of(sp.cbegin(), sp.cend(),   [](int x) {return x == 60; });
    auto anyOf5 = std::any_of(sp.rbegin(), sp.rend(),   [](int x) {return x == 50; });
    auto anyOf6 = std::any_of(sp.rbegin(), sp.rend(),   [](int x) {return x == 60; });
    auto anyOf7 = std::any_of(sp.crbegin(), sp.crend(), [](int x) {return x == 50; });
    auto anyOf8 = std::any_of(sp.crbegin(), sp.crend(), [](int x) {return x == 60; });

    bool res{ true };
    res &= (anyOf1 == true);
    res &= (anyOf2 == false);
    res &= (anyOf3 == true);
    res &= (anyOf4 == false);
    res &= (anyOf5 == true);
    res &= (anyOf6 == false);
    res &= (anyOf7 == true);
    res &= (anyOf8 == false);

    std::cout << "Test Any_Of:\t\t" << (res ? "Pass" : "Failed") << std::endl;
    return res;
}