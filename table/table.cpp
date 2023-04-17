#include "table.hpp"

Table::Table()
{
    status = true;
    time_use = Time(0,0);
    cof = 0;
    client = nullptr;
}

bool Table::get_status() const
{
    return status;
}

Client* Table::get_client() const
{
    return this->client;
}

int Table::get_cof() const
{
    return this->cof;
}

void Table::set_client(Client* client)
{
    this->status = false;
    this->client = client;
    this->client->set_waiting(false);
}

void Table::left_client(Time time)
{
    this->time_use += time - client->get_time();
    this->cof += Time(time - client->get_time()).floor();
    this->status = true;
    this->client = nullptr;
}

void Table::left_client(Time time, Time time_start)
{
    this->time_use += time - time_start;
    this->cof += Time(time - time_start).floor();
    this->status = true;
    this->client = nullptr;
}

void Table::set_status(bool status)
{
    this->status = status;
}

Time Table::get_time() const
{
    return this->time_use;
}
