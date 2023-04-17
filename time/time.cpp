#include "time.hpp"

Time::Time()
{
    this->time = std::tuple<int, int>{0, 0};
}

Time::Time(int hour, int minute)
{
    this->time = std::tuple<int, int>{0, 0};
    this->set_time(hour, minute);
}

Time::Time(std::string time)
{
    this->time = std::tuple<int, int>{0, 0};
    this->set_time(time);
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
    if(hour < 0 || hour > 24)
        this->time = std::tuple<int, int>{0, this->get_minute()};
    else
        this->time = std::tuple<int, int>{hour, this->get_minute()};
}

void Time::set_minute(int minute)
{
    if(minute < 0 || minute >= 60)
        this->time = std::tuple<int, int>{this->get_hour(), 0};
    else
        this->time = std::tuple<int, int>{this->get_hour(), minute};
}

void Time::set_time(int hour, int minute)
{
    this->set_hour(hour);
    this->set_minute(minute);
}

void Time::set_time(std::string time)
{
    int hours = (int(time[0]) - '0') * 10 + (int(time[1]) - '0');
    int minutes = (int(time[3]) - '0') * 10 + (int(time[4]) - '0');
    this->set_time(hours, minutes);
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

bool Time::operator<(const Time& other) const
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

bool Time::operator>(const Time& other) const
{
    return !(*this < other);
}

std::string Time::output() const
{
    return std::to_string(this->get_hour()) + ":" + std::to_string(this->get_minute());
}

int Time::floor()
{
    if(this->get_minute() > 0)
        return this->get_hour() + 1;
    else
        return this->get_hour();
}
