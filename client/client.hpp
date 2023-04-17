#ifndef CLIENT_HPP
#define CLIENT_HPP
#include <iostream>
#include <tuple>
#include "../time/time.hpp"

    class Client
    {
        Time time_start;

        std::string name;
        bool waiting;

        int table_num;

        public:
            Client();
            Client(Time time_start, std::string name);

            std::string get_name();
            bool get_waiting();
            int get_table_num();
            Time get_time();

            void set_waiting(bool waiting);
            void set_time(Time time);
            void set_table_num(int table_num);

    };

#endif CLIENT_HPP
