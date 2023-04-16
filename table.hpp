#ifndef TABLE_HPP
#define TABLE_HPP
#include <iostream>
#include <tuple>
#include "client.hpp"
#include "time.hpp"

namespace test
{
    class Table
    {
        bool free;
        Client client;
        Time time_use;

    };
}

#endif
