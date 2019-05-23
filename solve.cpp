#include <iostream>
#include <vector>
#include <unordered_set>
#include "gtest.h"


unsigned solve(std::vector<int> const &v1, std::vector<int> const &v2) {
    std::unordered_set<int> s;
    unsigned res = 0;
    if (v1.size() < v2.size()) {
        for (int a : v1) {
            s.insert(a);
        }

        for (int a : v2) {
            auto it = s.find(a);
            if (it != s.end()) {
                res++;
            }
        }
    } else {
        for (int a : v2) {
            s.insert(a);
        }

        for (int a : v1) {
            auto it = s.find(a);
            if (it != s.end()) {
                res++;
            }
        }
    }
    return res;
}

