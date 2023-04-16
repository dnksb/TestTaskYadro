#ifndef TABLE_HPP
#define TABLE_HPP
#include <iostream>
#include <tuple>

namespace test
{
    class Table
    {
        bool free;
        Client client;
        std::tuple<int, int> time_use;

    };
}

#endif
