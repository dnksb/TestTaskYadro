#include "table.hpp"

Table::Table()
{
    status = true;
    time_use = Time();
    client = nullptr;
}

bool Table::get_status() const
{
    return status;
}

void Table::set_client(Client* client)
{
    std::cout << client->get_name() << std::endl;
    this->client = client;
}
