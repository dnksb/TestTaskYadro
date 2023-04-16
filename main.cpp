#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
#include "./table/table.hpp"
#include "./time/time.hpp"
#include "./client/client.hpp"

std::vector<Table> tables;

void init_tables(int amount_table);
void interpreter(std::string line);
std::vector<std::string> split(std::string line);

int main(int argc, char* argv[])
{
    std::string filename = argv[1];
    std::ifstream fin = std::ifstream();

    int amount_table = 0;
    std::string time = "";
    int price = 0;

    Time time_start = Time();
    Time time_end = Time();

    try
    {
        fin.open(filename);
        if (!fin.is_open())
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
            interpreter(line, tables);
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
    auto tables = std::vector<Table>(amount_table);
    for(int i = 0; i < amount_table; i++)
    {
        tables[i] = Table();
    }
}

void interpreter(std::string line, std::vector<Table> &tables)
{
    auto commands = split(line);
}

std::vector<std::string> split(std::string line)
{
    char str[line.length() + 1];

    for (int x = 0; x < sizeof(str); x++) {
        str[x] = line[x];
    }

    auto commands = std::vector<std::string>();
    char *token = strtok(str, " ");

    while(token != NULL)
    {
        commands.insert(, std::to_string(token));
        token = strtok(NULL, " ");
    }
    return commands;
}
