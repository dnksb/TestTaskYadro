#include "client.hpp"

Client::Client()
{
    time_start = Time();
}

Client::Client(Time time_start, std::string name)
{
    this->time_start = time_start;
    this->name = name;
}

std::string Client::get_name()
{
    return this->name;
}

bool Client::get_waiting()
{
    return this->waiting;
}

int Client::get_table_num()
{
    return this->table_num;
}

Time Client::get_time()
{
    return this->time_start;
}

void Client::set_waiting(bool waiting)
{
    this->waiting = waiting;
}

void Client::set_time(Time time)
{
    this->time_start = time;
}

void Client::set_table_num(int table_num)
{
    this->table_num = table_num;
}
