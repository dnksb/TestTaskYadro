#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
#include <queue>
#include "./table/table.hpp"
#include "./time/time.hpp"
#include "./client/client.hpp"

int amount_table;
int price;

std::vector<Table> tables;
std::vector<Client> clients;
std::queue<Client*> clients_waiting;

Time time_start;
Time time_end;

std::ifstream fin;
std::ofstream report;

void init_tables(int amount_table);
void interpreter(std::string line);

std::vector<std::string>* split(std::string line);

void client_came(std::string time, std::string client_name);
void client_sat(std::string time, std::string client_name, int num_table);
void client_wait(std::string time, std::string client_name);
void client_left(std::string time, std::string client_name);

bool one_table_free();
int amount_waiting_client();
Client* find_client(std::string client_name);
void decrease_queue(std::string time, int num_table);

void report_time_use();
void time_off();

int main(int argc, char* argv[])
{
    std::string filename = argv[1];
    fin = std::ifstream();

    clients_waiting = std::queue<Client*>();

    std::string time = "";
    price = 0;

    try
    {
        fin.open(filename);
        report.open("report_" + filename);
        if (!fin.is_open() || !report.is_open())
        {
            std::cout << "не удалось открыть файл" << std::endl;
            return 1;
        }
    }
    catch (std::exception ex)
    {
        std::cout << ex.what() << std::endl;
        return 1;
    }

    try
    {
        fin >> amount_table;
        fin >> time;
        report << time;
        time_start.set_time(time);
        fin >> time;
        time_end.set_time(time);
        fin >> price;
    }
    catch (std::exception ex)
    {
        std::cout << ex.what() << std::endl;
        return 1;
    }

    init_tables(amount_table);

    try
    {
        std::string line = "";
        while(!fin.eof())
        {
            std::getline(fin, line);
            report << line << std::endl;
            std::cout << line << std::endl;
            interpreter(line);
        }
    }
    catch (std::exception ex)
    {
        std::cout << ex.what() << std::endl;
        return 1;
    }

    time_off();

    report_time_use();

    return 0;
}

void init_tables(int amount_table)
{
    tables = std::vector<Table>(amount_table);
    for(int i = 0; i < amount_table; i++)
    {
        tables[i] = Table();
    }
}

void interpreter(std::string line)
{
    auto commands = split(line);
    if(commands->size() != 3 && commands->size() != 4)
    {
        std::cout << "не правильный формат записи: " << line << std::endl;
        return;
    }

    auto time = (*commands)[0];
    auto num_operation = atoi((*commands)[1].c_str());
    auto client_name = (*commands)[2];

    if(Time(time) < time_start)
    {
        if(num_operation == 1)
            report << time + " 13 NotOpenYet\n";
        else
            report << time + " 13 YouShallNotPass\n";
        return;
    }

    switch (num_operation)
    {
    case 1:
        client_came(time, client_name);
        break;
    case 2:
        client_sat(time, client_name, atoi((*commands)[3].c_str()) - 1);
        break;
    case 3:
        client_wait(time, client_name);
        break;
    case 4:
        client_left(time, client_name);
        break;
    default:
        break;
    }

    delete commands;
}

std::vector<std::string>* split(std::string line)
{
    char str[line.length() + 1];

    for (int x = 0; x < sizeof(str); x++) {
        str[x] = line[x];
    }

    auto* commands = new std::vector<std::string>();
    char *token = strtok(str, " ");

    while(token != NULL)
    {
        commands->insert(commands->end(), token);
        token = strtok(NULL, " ");
    }
    return commands;
}

void client_came(std::string time, std::string client_name)
{
    clients.insert(clients.end(), Client(Time(time), client_name));
}

void client_sat(std::string time, std::string client_name, int num_table)
{
    Client* client = find_client(client_name);
    if(client == nullptr)
        report << time + " 13 ClientUnknown\n";
    else if(!tables[num_table].get_status())
        report << time + " 13 PlaceIsBusy\n";
    else
    {
        client->set_time(Time(time));
        tables[num_table].set_client(client);
        client->set_table_num(num_table);
    }
}

void client_wait(std::string time, std::string client_name)
{
    if(one_table_free())
    {
        report << time + " 13 ICanWaitNoLonger!\n";
        return;
    }
    else if(amount_waiting_client() > amount_table)
    {
        report << time + " 11 " + client_name << std::endl;
        return;
    }
    else
    {
        clients_waiting.push(find_client(client_name));
    }
}

void client_left(std::string time, std::string client_name)
{
    auto client = find_client(client_name);
    if(client == nullptr)
        report << time + " 13 ClientUnknown\n";
    else
    {
        std::cout << client->get_time().output() << std::endl;
        std::cout << Time(time).output() << std::endl;
        int num_table = client->get_table_num();
        tables[num_table].left_client(Time(time), client->get_time());
        decrease_queue(time, num_table);
    }
}

void decrease_queue(std::string time, int num_table)
{
    auto client = clients_waiting.front();
    if(client != nullptr)
    {
        client_sat(time, client->get_name(), num_table);
        report << time + " 12 " + client->get_name() << " " << num_table + 1 << std::endl;
        clients_waiting.pop();
    }
}

Client* find_client(std::string client_name)
{
    for (int i = 0; i < clients.size(); i++)
        if  (clients[i].get_name() == client_name)
                return& clients[i];
    return nullptr;
}

bool one_table_free()
{
    for (int i = 0; i < tables.size(); i++)
        if(tables[i].get_status())
            return true;
    return false;
}

int amount_waiting_client()
{
    int amount = 0;
    for (int i = 0; i < clients.size(); i++)
        if(clients[i].get_waiting())
            amount++;
    return amount;
}

void time_off()
{
    for (int i = 0; i < tables.size(); i++)
        if(!tables[i].get_status())
        {
            auto client = tables[i].get_client();
            std::cout << client->get_time().output() << std::endl;
            report << time_end.output() << " 11 " << client->get_name() << std::endl;
            tables[i].left_client(Time(time_end));
        }

    report << time_end.output() << std::endl;
}

void report_time_use()
{
    for (int i = 0; i < tables.size(); i++)
    {
        auto time = tables[i].get_time();
        report << i + 1 << " " << price * tables[i].get_cof() << " " << time.output() << std::endl;
    }
}
