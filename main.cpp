#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
#include "./table/table.hpp"
#include "./time/time.hpp"
#include "./client/client.hpp"

std::vector<Table> tables;
std::vector<Client> clients;

Time time_start;
Time time_end;

std::ifstream fin;
std::ofstream report;

void init_tables(int amount_table);
void interpreter(std::string line);
std::vector<std::string>* split(std::string line);
std::string* insert(std::string* array, int* size);
void client_came(std::string time, std::string client_name);
void client_sat(std::string time, std::string client_name, int num_table);
Client* find_client(std::string client_name);

int main(int argc, char* argv[])
{
    std::string filename = argv[1];
    fin = std::ifstream();

    int amount_table = 0;
    std::string time = "";
    int price = 0;

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
            interpreter(line);
        }
    }
    catch (std::exception ex)
    {
        std::cout << ex.what() << std::endl;
        return 1;
    }

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
    auto client_name = (*commands)[0];

    if(Time(time) < time_start)
    {
        report << time + " 13 NotOpenYet\n";
        return;
    }

    switch (num_operation)
    {
    case 1:
        client_came(time, client_name);
        break;
    case 2:
        client_sat(time, client_name, atoi((*commands)[3].c_str()));
        break;
    case 3:

        break;
    case 4:

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
    {
        std::cout << "неизвестный клиент" << std::endl;
        return;
    }
    tables[num_table].set_client(client);
}

Client* find_client(std::string client_name)
{
    for (int i = 0; i < clients.size(); i++)
    {
        std::cout << clients[i].get_name() << std::endl;
        if  (clients[i].get_name() == client_name)
            return& clients[i];
    }
    return nullptr;
}
