#include <array>
#include <string>
#include <iostream>
#include <vector>
#include <charconv>
#include <ranges>

using Ip = std::array<uint8_t, 4>;
using IpVector = std::vector<Ip>;
class IpPool;

std::ostream& operator<<(std::ostream& os, Ip ip);
std::ostream& operator<<(std::ostream& os, const IpPool& pool);

class IpPool : public IpVector
{
public:
    void parse(std::istream& is);
};

