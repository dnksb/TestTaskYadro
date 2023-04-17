#ifndef TABLE_HPP
#define TABLE_HPP
#include <iostream>
#include <tuple>
#include "../client/client.hpp"
#include "../time/time.hpp"

class Table
{
    bool status;
    Client* client;
    Time time_use;
    public:
        Table(Client* _client, Time _time_use, bool _status) :
        client(_client),
        time_use(_time_use),
        status(_status){};
        Table();

        bool get_status() const;

        void set_client(Client* client);
};

#endif
