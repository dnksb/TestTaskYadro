#include "client.hpp"

Client::Client()
{
    time_start = Time();
    time_end = Time();
}

Client::Client(Time time_start, std::string name)
{
    this->time_start = time_start;
    this->time_end = Time();
    this->name = name;
}

std::string Client::get_name()
{
    return this->name;
}
