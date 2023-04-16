#include "time.hpp"

namespace time
{
    Time::Time(int hour, int minute)
    {
        time = std::tuple<int, int>{hour, minute};
    }

    int Time::get_hour() const
    {
        return std::get<0>(this->time);
    }

    int Time::get_minute() const
    {
        return std::get<1>(this->time);
    }

    std::tuple<int, int> Time::get_time() const
    {
        return this->time;
    }

    void Time::set_hour(int hour)
    {
        this->time = std::tuple<int, int>{hour, this->get_minute()};
    }

    void Time::set_minute(int minute)
    {
        this->time = std::tuple<int, int>{this->get_hour(), minute};
    }

    void Time::set_time(int hour, int minute)
    {
        this->time = std::tuple<int, int>{hour, minute};
    }

    Time Time::operator+=(const Time& other)
    {
        int hours = other.get_hour() + this->get_hour();
        int minutes = other.get_minute() + this->get_minute();
        if (minutes < 60 )
            this->set_time(hours, minutes);
        else
            this->set_time(hours + 1, minutes - 60);
    }

    const Time Time::operator+( const Time& other) const
    {
        Time result = *this;
        result += other;
        return result;
    }

    Time Time::operator-=(const Time& other)
    {
        int hours = this->get_hour() - other.get_hour();
        int minutes = this->get_minute() - other.get_minute();
        if (minutes < 0)
            this->set_time(hours - 1, minutes + 60);
        else
            this->set_time(hours, minutes);
    }

    const Time Time::operator-( const Time& other) const
    {
        Time result = *this;
        result -= other;
        return result;
    }

    bool Time::operator<(Time& other)
    {
        bool result = true;
        if(this->get_hour() == other.get_hour())
            if(this->get_minute() < other.get_minute())
                result = true;
            else
                result = false;
        else if(this->get_hour() < other.get_hour())
            result = true;
        else
            result = false;
        return result;
    }

    bool Time::operator>(Time& other)
    {
        return !(*this < other);
    }
}
