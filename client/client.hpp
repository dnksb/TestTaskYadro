#ifndef CLIENT_HPP
#define CLIENT_HPP
#include <iostream>
#include <tuple>
#include "../time/time.hpp"

    class Client
    {
        Time time_start;
        Time time_end;
        std::string name;
        public:
            Client();
            Client(Time time_start, std::string name);

            std::string get_name();
    };

#endif CLIENT_HPP
