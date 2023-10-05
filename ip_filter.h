#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

template<uint8_t... Values>
class keep {
public:
    auto operator()(auto cont) {
        std::vector nums{Values...};
        std::vector<uint8_t> nums2{cont.begin(), cont.begin() + nums.size()};
        return nums == nums2;
    }
};

template <uint8_t Value>
class keep_any {
public:
    auto operator()(auto cont) {
        return std::find(cont.begin(), cont.end(), Value) != cont.end();
    }
};


