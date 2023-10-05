#include <charconv>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ranges>
#include <array>

#include "ip_filter.h"
#include "ip_pool.h"

namespace rv = std::ranges::views;

int main(void)
{
    IpPool ip_pool{};

    try {
        ip_pool.parse(std::cin);
    } catch (std::exception &e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    std::ranges::sort(ip_pool, std::ranges::greater());

    std::cerr << "----------- all" << std::endl;
    for (const auto& ip : ip_pool) {
        std::cout << ip << std::endl;
    }

    std::cerr << "----------- [0]=1" << std::endl;
    for (auto ip : ip_pool | rv::filter(keep<1>{})) {
        std::cout << ip << std::endl;
    }

    std::cerr << "----------- [0]=46 [1]=70" << std::endl;
    for (auto ip : ip_pool | rv::filter(keep<46,70>{})) {
        std::cout << ip << std::endl;
    }

    std::cerr << "----------- any 46" << std::endl;
    for (auto ip : ip_pool | rv::filter(keep_any<46>{})) {
        std::cout << ip << std::endl;
    }

    return 0;
}

