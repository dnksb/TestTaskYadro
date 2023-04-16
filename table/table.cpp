#include "table.hpp"

    Table::Table()
    {
        status = true;
        time_use = Time();
        client = Client();
    }

    bool Table::get_status() const
    {
        return status;
    }
