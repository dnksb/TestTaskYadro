#ifndef TIME_HPP
#define TIME_HPP
#include <tuple>

namespace time
{
    class Time
    {
        std::tuple<int, int> time;
        public:
            Time(int hour, int minute);
            Time operator+=(const Time& other);
            const Time operator+(const Time& other) const;
            Time operator-=(const Time& other);
            const Time operator-(const Time& other) const;
            bool operator<(Time& other);
            bool operator>(Time& other);
            int get_hour() const;
            int get_minute() const;
            std::tuple<int, int> get_time() const;
            void set_hour(int hour);
            void set_minute(int minute);
            void set_time(int hour, int minute);
    };
}

#endif TIME_HPP
