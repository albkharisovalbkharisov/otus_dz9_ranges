#include "ip_pool.h"

namespace rv = std::ranges::views;

void IpPool::parse(std::istream& is) {
    for (std::string line; std::getline(is, line); ) {
        auto ip_str = std::string_view{line.begin(), line.begin() + line.find('\t')};

        Ip ip;
        for (int result, i = 0; auto x : ip_str | rv::split('.')) {
            auto [_, ec] = std::from_chars(x.begin(), x.end(), result);
            if (ec != std::errc()) {
                std::cout << "Error: input string: \'" << std::string_view{x.begin(), x.end()} << "\'" << std::endl;
                throw std::runtime_error("Wrong input format");
            }
            ip[i++] = result;
        }
        push_back(ip);
    }
}

std::ostream& operator<<(std::ostream& os, Ip ip) {
    return os << static_cast<unsigned>(ip[0]) << "."
              << static_cast<unsigned>(ip[1]) << "."
              << static_cast<unsigned>(ip[2]) << "."
              << static_cast<unsigned>(ip[3]);
}

std::ostream& operator<<(std::ostream& os, const IpPool& pool)
{
    for (const auto& ip : pool) {
        std::cout << ip << " ";
    }
    return os;
}

