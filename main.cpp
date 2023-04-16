#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include "table.hpp"
#include "time.hpp"
#include "client.hpp"

int main(int argc, char* argv[])
{
    std::string filename = argv[1];
    std::ifstream fin = std::ifstream();

    int amount_table = 0;

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
        std::cout << amount_table << std::endl;
        fin >> filename;
        std::cout << filename << std::endl;
    }
    catch (std::exception ex)
    {
        std::cout << ex.what() << std::endl;
        return 1;
    }
    return 0;
}
