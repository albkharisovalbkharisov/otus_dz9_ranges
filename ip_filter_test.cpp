#include <boost/test/tools/old/interface.hpp>
#include <charconv>
#include <fstream>
#include <sstream>
#define BOOST_TEST_MODULE ip_filter_test_module

#include "ip_filter.h"
#include "ip_pool.h"
#include <iostream>
#include <boost/test/unit_test.hpp>

namespace rv = std::ranges::views;

auto apply_filter(IpPool& pool, auto f)
{
    IpPool result;
    for (auto& ip : pool | f)
    {
        result.push_back(ip);
    }
    return result;
}

class IpPoolFactory {
public:
    IpPool createPool(std::string str) {
        std::istringstream input{str};
        IpPool pool;
        std::istream input_stream{input.rdbuf()};
        pool.parse(input_stream);
        return pool;
    }
};

BOOST_AUTO_TEST_SUITE(ip_filter_test_suite)
IpPoolFactory factory;

std::vector<std::tuple<std::string, std::function<bool(Ip)>, IpPool>> test_cases_data = 
{
    {"\
1.39.22.224	5	6\n\
1.40.22.224	5	6\n\
1.162.145.156	111	0",
    keep<1>{},
    {{{1,162,145,156}, {1,40,22,224}, {1,39,22,224}}}
    },

    {"\
1.39.22.224	5	6\n\
1.40.22.224	5	6\n\
1.162.145.156	111	0",
    keep<1,40>{},
    {{{1,40,22,224}}}
    },

    {"\
36.39.22.224	5	6\n\
113.2.22.224	5	6\n\
113.162.36.156	111	0",
    keep_any<36>{},
    {{{113,162,36,156}, {36,39,22,224}}}
    }

};

BOOST_AUTO_TEST_CASE(test_logic)
{
    for (int i = 0; const auto& data : test_cases_data) {
        //std::cout << std::get<0>(data) << std::endl;
        auto pool = factory.createPool(std::get<0>(data));
        std::ranges::sort(pool, std::ranges::greater());
        auto result = apply_filter(pool, rv::filter(std::get<1>(data)));
        auto expected = std::get<2>(data);
        BOOST_CHECK_MESSAGE(result == expected, "iteration " << i++ << ", "
                << "expected: " << expected
                << "result: " << result
                );
//        ++i;
    }
}

BOOST_AUTO_TEST_SUITE_END()

