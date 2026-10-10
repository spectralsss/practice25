#include <iostream>

class Time {
private:
    int hours;
    int minutes;
    int seconds;

    void normalize() {
        minutes += seconds / 60;
        seconds %= 60;
        if (seconds < 0) {
            seconds += 60;
            minutes -= 1;
        }
        hours += minutes / 60;
        minutes %= 60;
        if (minutes < 0) {
            minutes += 60;
            hours -= 1;
        }
        if (hours < 0) {
            hours = 0;
            minutes = 0;
            seconds = 0;
        }
    }

public:
    Time(int h = 0, int m = 0, int s = 0) : hours(h), minutes(m), seconds(s) {
        normalize();
    }

    friend std::ostream& operator<<(std::ostream& os, const Time& t) {
        if (t.hours < 10) os << "0";
        os << t.hours << ":";
        if (t.minutes < 10) os << "0";
        os << t.minutes << ":";
        if (t.seconds < 10) os << "0";
        os << t.seconds;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Time& t) {
        char c1, c2;
        is >> t.hours;
        if (is >> c1) {
            if (c1 == ':' || c1 == ' ') {
                is >> t.minutes;
                if (is >> c2) {
                    if (c2 == ':' || c2 == ' ') {
                        is >> t.seconds;
                    }
                    else {
                        is.putback(c2);
                    }
                }
            }
            else {
                is.putback(c1);
            }
        }
        t.normalize();
        return is;
    }

    Time operator+(const Time& other) const {
        return Time(hours + other.hours, minutes + other.minutes, seconds + other.seconds);
    }

    Time operator-(const Time& other) const {
        int total1 = hours * 3600 + minutes * 60 + seconds;
        int total2 = other.hours * 3600 + other.minutes * 60 + other.seconds;
        int diff = total1 - total2;
        if (diff < 0) diff = 0;
        return Time(0, 0, diff);
    }
};