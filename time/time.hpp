#ifndef TIME_HPP
#define TIME_HPP
#include <tuple>
#include <iostream>

class Time
{
    std::tuple<int, int> time;
    public:
        Time();
        Time(int hour, int minute);
        Time(std::string time);

        Time operator+=(const Time& other);
        const Time operator+(const Time& other) const;

        Time operator-=(const Time& other);
        const Time operator-(const Time& other) const;

        bool operator<(const Time& other) const;
        bool operator>(const Time& other) const;

        int get_hour() const;
        int get_minute() const;
        std::tuple<int, int> get_time() const;

        void set_hour(int hour);
        void set_minute(int minute);
        void set_time(int hour, int minute);
        void set_time(std::string time);

        int floor();

        std::string output() const;
};

#endif TIME_HPP
