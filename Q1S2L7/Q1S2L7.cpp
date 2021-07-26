#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cassert>
#include <ctime>

using namespace std;

class Date {
protected:
    int day;
    int month;
    int year;
public:
    Date() : Date(0, 0, 0) {
    }
    Date(int day, int month, int year) : day(day), month(month), year(year) {
        assert(day > 0 || day < 32 || month > 0 || month < 13);
    }
    void setDay(int day) {
        this->day = day;
    }
    void setMonth(int month) {
        this->month = month;
    }
    void setYear(int year) {
        this->year = year;
    }
    int getDay() const {
        return day;
    }
    int getMonth() const {
        return month;
    }
    int getYear() const {
        return year;
    }
    bool operator>(Date& date) {
        if (this->year > date.year) {
            return true;
        }
        else if (this->year == date.year) {
            if (this->month > month) {
                return true;
            }
            else if (this->month == date.month) {
                if (this->day > day) {
                    return true;
                }
            }
        }
        return false;
    }
    friend ostream& operator<<(ostream& out, const Date& date);
};

ostream& operator<<(ostream& out, const Date& date) {
    out << date.day << "." << date.month << "." << date.year;
    return out;
}

template<class T>
string isNull(unique_ptr<T>& ptr) {
    return (ptr == nullptr ? "is nullptr" : "isn't nullptr");
}

Date& lateDate(unique_ptr<Date>& ptr1, unique_ptr<Date>& ptr2) {
    if (ptr1 > ptr2) {
        return *ptr1;
    }
    return *ptr2;
}

void swapPtr(unique_ptr<Date>& ptr1, unique_ptr<Date>& ptr2) {
    int day = ptr1->getDay();
    int month = ptr1->getMonth();
    int year = ptr1->getYear();
    ptr1->setDay(ptr2->getDay());
    ptr1->setMonth(ptr2->getMonth());
    ptr1->setYear(ptr2->getYear());
    ptr2->setDay(day);
    ptr2->setMonth(month);
    ptr2->setYear(year);
}

int main()
{
    // #1
    time_t now = time(0);
    tm* ltm = localtime(&now);

    unique_ptr<Date> today = make_unique<Date>();
    unique_ptr<Date> date = nullptr;

    today->setDay(ltm->tm_mday);
    today->setMonth(ltm->tm_mon);
    today->setYear(1900 + ltm->tm_year);

    cout << "today " << isNull(today) << endl;
    cout << "date " << isNull(date) << endl;
    cout << "today: " << *today << endl;

    date = move(today);

    cout << "today " << isNull(today) << endl;
    cout << "date " << isNull(date) << endl;
    cout << "date: " << *date << endl << endl;

    // #2.1
    unique_ptr<Date> date1 = make_unique<Date>(18, 9, 2002);
    unique_ptr<Date> date2 = make_unique<Date>(26, 6, 2021);
    cout << lateDate(date1, date2) << endl << endl;

    // #2.2
    cout << "date1: " << *date1 << endl;
    cout << "date2: " << *date2 << endl;
    swapPtr(date1, date2);
    cout << "Swapped..." << endl;
    cout << "date1: " << *date1 << endl;
    cout << "date2: " << *date2 << endl;
    return 0;
}