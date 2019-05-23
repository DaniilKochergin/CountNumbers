#include <iostream>
#include <vector>
#include <unordered_set>
#include "gtest.h"
#include <random>
#include <algorithm>


unsigned solve(std::vector<int> const &, std::vector<int> const &);

TEST(small_test, special_test) {
    EXPECT_TRUE(solve({1, 4, 7}, {3, 5, 12}) == 0);
    EXPECT_TRUE(solve({0}, {0}) == 1);
    EXPECT_TRUE(solve({}, {}) == 0);
    EXPECT_TRUE(solve({INT32_MAX}, {INT32_MIN}) == 0);
    EXPECT_TRUE(solve({INT32_MAX, 0, INT32_MIN}, {INT32_MIN, 1, INT32_MAX, 239}) == 2);
    EXPECT_TRUE(solve({}, {0, 1, 2}) == 0);
    EXPECT_TRUE(solve({121234, 1, 42}, {}) == 0);
}

namespace {
    unsigned const number_of_iterations = 100;
    size_t const size_of_small_array = 100;
    size_t const size_of_big_array = 10000;
    std::mt19937 random;
}

std::pair<std::vector<int>, std::vector<int>>
random_arrays_without_coincidence(size_t first_size, size_t second_size, std::unordered_set<int> s1 = {}) {
    std::unordered_set<int> s;
    while (s.size() < first_size + second_size) {
        int num = random();
        auto it = s1.find(num);
        if (it == s1.end()) {
            s.insert(num);
        }
    }
    std::vector<int> a;
    std::vector<int> b;
    for (int v : s) {
        if (a.size() < first_size) a.push_back(v);
        else b.push_back(v);
    }
    return std::make_pair(a, b);
}

TEST(randmom_test, small_size_array_random_test_without_coincidence) {
    for (size_t i = 0; i < number_of_iterations; ++i) {

        std::pair<std::vector<int>, std::vector<int>> a = random_arrays_without_coincidence(size_of_small_array,
                                                                                            size_of_small_array);


        std::shuffle(a.first.begin(), a.first.end(),std::mt19937());
        EXPECT_TRUE(solve(a.first, a.second) == 0);
    }
}


TEST(randmom_test, big_size_array_random_test_without_coincidence) {
    for (size_t i = 0; i < number_of_iterations; ++i) {
        std::pair<std::vector<int>, std::vector<int>> a = random_arrays_without_coincidence(size_of_big_array,
                                                                                            size_of_big_array);
        std::shuffle(a.first.begin(), a.first.end(),std::mt19937());
        EXPECT_TRUE(solve(a.first, a.second) == 0);
    }
}


TEST(random_test, big_and_small_size_array_random_test_without_coincidence) {
    for (size_t i = 0; i < number_of_iterations; ++i) {
        std::pair<std::vector<int>, std::vector<int>> a = random_arrays_without_coincidence(size_of_big_array,
                                                                                            size_of_small_array);
        std::shuffle(a.first.begin(), a.first.end(),std::mt19937());
        std::shuffle(a.second.begin(), a.second.end(),std::mt19937());
        EXPECT_TRUE(solve(a.first, a.second) == 0);
    }
}

TEST(random_test, small_and_big_size_array_random_test_without_coincidence) {
    for (size_t i = 0; i < number_of_iterations; ++i) {
        std::pair<std::vector<int>, std::vector<int>> a = random_arrays_without_coincidence(size_of_small_array,
                                                                                            size_of_big_array);
        std::shuffle(a.first.begin(), a.first.end(),std::mt19937());
        std::shuffle(a.second.begin(), a.second.end(),std::mt19937());
        EXPECT_TRUE(solve(a.first, a.second) == 0);
    }
}


TEST(random_test, small_random_test_with_coincidence) {
    for (size_t i = 0; i < number_of_iterations; ++i) {
        size_t ans = random() % size_of_small_array;
        std::unordered_set<int> s;
        while (s.size() < ans) {
            s.insert(random());
        }
        std::vector<int> a;
        std::vector<int> b;
        for (int g:s) {
            a.push_back(g);
        }
        b = a;
        std::pair<std::vector<int>, std::vector<int>> p = random_arrays_without_coincidence(size_of_small_array,
                                                                                            size_of_small_array, s);

        for (int cur : p.first) {
            a.push_back(cur);
        }
        for (int cur : p.second) {
            b.push_back(cur);
        }
        std::shuffle(a.begin(), a.end(),std::mt19937());
        std::shuffle(b.begin(), b.end(),std::mt19937());
        EXPECT_TRUE(solve(a, b) == ans);

    }
}

TEST(random_test, big_random_test_with_coincidence) {
    for (size_t i = 0; i < number_of_iterations; ++i) {
        size_t ans = random() % size_of_small_array;
        std::unordered_set<int> s;
        while (s.size() < ans) {
            s.insert(random());
        }
        std::vector<int> a;
        std::vector<int> b;
        for (int g:s) {
            a.push_back(g);
        }
        b = a;
        std::pair<std::vector<int>, std::vector<int>> p = random_arrays_without_coincidence(size_of_big_array,
                                                                                            size_of_big_array, s);
        for (int cur : p.first) {
            a.push_back(cur);
        }
        for (int cur : p.second) {
            b.push_back(cur);
        }
        std::shuffle(a.begin(), a.end(),std::mt19937());
        std::shuffle(b.begin(), b.end(),std::mt19937());
    }
}


TEST(random_test, randon_size_with_coincidence) {
    for (size_t i = 0; i < number_of_iterations; ++i) {
        size_t size1 = static_cast<size_t >(random()) % size_of_big_array;
        size_t size2 = static_cast<size_t >(random()) % size_of_big_array;
        size_t ans = random() % (std::min(size1, size2));
        std::unordered_set<int> s;
        while (s.size() < ans) {
            s.insert(random());
        }
        std::vector<int> a;
        std::vector<int> b;
        for (int g:s) {
            a.push_back(g);
        }
        b = a;
        std::pair<std::vector<int>, std::vector<int>> p = random_arrays_without_coincidence(size1,
                                                                                            size2, s);
        std::shuffle(a.begin(), a.end(),std::mt19937());
        std::shuffle(b.begin(), b.end(),std::mt19937());

        for (int cur : p.first) {
            a.push_back(cur);
        }
        for (int cur : p.second) {
            b.push_back(cur);
        }
    }
}