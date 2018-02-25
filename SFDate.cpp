#include "SFDate.hpp"
#include "SFDateTime.hpp"
#include <iostream>
#include <ctime>
#include <sstream>
#include <string>
SFDate::SFDate()
{
    std::time_t t = time(0);
    const std::tm * time_out = std::gmtime(&t);
    day = time_out->tm_mday;
    month = (time_out->tm_mon)+1;
    year = (time_out->tm_year)+1900;
}

void SFDate::Parser(std::string dt)
{
    year = 0;
    month = 0;
    day = 0;
    std::stringstream iss (dt);
    std::string date;
    int flag = 0;
    while (iss >> date)
    {
        if (flag == 0)
        {
            if (isdigit(date[0]))
            {
                for (size_t j =0; j < date.length(); j++)
                {
                    month *= 10;
                    month += date[j] - '0';
                }
            }

            else
            {
                if (date == "January" || date == "Jan")
                {
                    month  = 1;
                }
                else if (date == "February" || date == "Feb")
                {
                    month = 2;
                }
                else if (date == "March" || date == "Mar")
                {
                    month = 3;
                }
                else if (date == "April" || date == "Apr")
                {
                    month = 4;
                }
                else if (date == "May" || date == "Ma")
                {
                    month = 5;
                }
                else if (date == "June" || date == "Jun")
                {
                    month = 6;
                }
                else if (date == "July" || date == "Jul")
                {
                    month = 7;
                }
                else if (date == "August" || date == "Aug")
                {
                    month = 8;
                }
                else if (date == "September" || date == "Sept")
                {
                    month = 9;
                }
                else if (date == "October" || date == "Oct")
                {
                    month = 10;
                }
                else if (date == "November" || date == "Nov")
                {
                    month = 11;
                }
                else if (date == "December" || date == "Dec")
                {
                    month = 12;
                }
            }
            flag++;
        }

        else if (flag == 1)
        {
            for (size_t i = 0; i < date.length(); i++)
            {
                if (ispunct(date[i]))
                {
                    date.erase(i--, 1);
                }
            }

            for (size_t i = 0; i < date.length(); i++)
            {
                day *= 10;
                day += date[i] - '0';
            }
            flag++;
        }

        else
        {
            for (size_t i = 0; i < date.length(); i++)
            {
                if (isdigit(date[i]))
                {
                    year *= 10;
                    year += date[i] - '0';
                }
            }
        }
    }
}

SFDate::SFDate(const char* aDateTimeString)
{
    std::string str = aDateTimeString;

    size_t i = 0;
    while (i < str.length())
    {
        if (str[i] == '/')
        {
            str[i] = ' ';
        }
        i++;
    }

    Parser(str);
}

SFDate::SFDate(int aMonth, int aDay, int aYear)
{
    month = aMonth;
    day = aDay;
    year = aYear;
}

SFDate::SFDate(const SFDate &aCopy)
{
    month = aCopy.month;
    day = aCopy.day;
    year = aCopy.year;
}

SFDate::SFDate(const SFDateTime &aCopy)
{
    month = aCopy.month;
    day = aCopy.day;
    year = aCopy.year;
}

SFDate& SFDate::operator++()
{
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10)
    {
        if (day == 31)
        {
            month = month + 1;
            day = 1;
        }

        else
        {
            day = day + 1;
        }
    }

    else if (month == 12)
    {
        month = 1;
        day = 1;
        year = year + 1;
    }

    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        if (day == 30)
        {
            day = 1;
            month = month + 1;
        }

        else
        {
            day = day + 1;
        }
    }

    else
    {
        if ((year%4 == 0 && year%100 != 0) || (year%400 == 0))
        {
            if (day == 29)
            {
                month = 3;
                day = 1;
            }
            else
            {
                day = day + 1;
            }
        }

        else
        {
            if (day == 28)
            {
                day = 1;
                month = 3;
            }

            else
            {
                day = day + 1;
            }

        }
    }
    return *this;
}

SFDate& SFDate::operator--()
{
    if (month == 1)
    {
        day = 31;
        month = 12;
        year = year - 1;
    }

    else if (month == 2 || month == 4 || month == 6 || month == 8 || month == 9 || month == 11)
    {
        if (day == 1)
        {
            month = month - 1;
            day = 31;
        }

        else
        {
            day = day - 1;
        }
    }

    else if (month == 3)
    {
        if (day == 1)
        {
            if ((year%4 == 0 && year%100 != 0) || (year%400 == 0))
            {
                day = 29;
            }

            else
            {
                day = 28;
            }

            month = 2;
        }

        else
        {
            day = day - 1;
        }

    }

    else
    {
        if (day == 1)
        {
            month = month - 1;
            day = 30;
        }

        else
        {
            day = day - 1;
        }
    }

    return *this;
}


SFInterval SFDate::operator-(const SFDate &other) const
{
    SFInterval interval;

    if (year >= other.year)
    {
        interval.years = year - other.year;
    }

    else
    {
        interval.years = other.year - year;
    }

    if (month >= other.month)
    {
        interval.months = month - other.month;
    }

    else
    {
        interval.months = other.month - month;
    }

    if (day >= other.day)
    {
        interval.days = day - other.day;
    }

    else
    {
        interval.days = other.day - day;
    }
    interval.seconds = interval.minutes = interval.hours = 0;
    return interval;
}

SFInterval SFDate::operator-(const SFDateTime &other) const
{
    SFInterval interval;
    interval.days = day - other.day;

    if (interval.days  < 0)
    {
        interval.days *= -1;
    }

    interval.months = month - other.month;

    if (interval.months  < 0)
    {
        interval.months *= -1;
    }

    interval.years = year - other.year;

    if (interval.years  < 0)
    {
        interval.years *= -1;
    }

    return interval;
}

SFDate& SFDate::adjustByDays(int n)
{

    adjustHelper(n);

    return *this;
}

SFDate& SFDate::adjustByWeeks(int n)
{
    int num_days = n*7;
    if (n < 0)
    {
        num_days = -1*n*7;
    }

    adjustHelper(num_days);

    return *this;
}

SFDate& SFDate::adjustByMonths(int n)
{
    int months = n;
    if (n < 0)
    {
        months = -1*n;
    }

    for (int i = 0; i < months; i++)
    {
        if (n < 0)
        {
            if (month == 1)
            {
                month = 12;
                year--;
            }

            else
            {
                month--;
            }
        }

        else
        {
            if (month == 12)
            {
                month = 1;
                year++;
            }

            else
            {
                month++;
            }
        }
    }

    return *this;
}

SFDate& SFDate::adjustByYears(int n)
{
    int years = n;
    if (n < 0)
    {
        years = -1*n;
    }

    for (int i = 0; i < years; i++)
    {
        if (n <0)
        {
            year--;
        }

        else
        {
            year++;
        }
    }

    return *this;
}

SFDate& SFDate::setDay(int aDay)
{

    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
    {
        if (aDay <= 0 || day > 31)
        {
            std::cout << "day is not within allowed range" << std::endl;
        }

        else
        {
            day = aDay;
        }
    }

    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        if (day <= 0 || day > 30)
        {
            std::cout << "day is not within allowed range" << std::endl;
        }

        else
        {
            day = aDay;
        }
    }

    else
    {
        if (day <= 0 || day > 29)
        {
            std::cout << "" << std::endl;
        }

        else
        {
            if (!((year%4 == 0 && year%100 != 0) || (year%400 == 0)))
            {
                if (day != 29)
                {
                    day = aDay;
                }
            }

            else
            {
                day = aDay;
            }
        }
    }

    return *this;
}

SFDate& SFDate::setMonth(int aMonth)
{
    if (aMonth >= 1 && aMonth <= 12)
    {
        month = aMonth;
    }

    return *this;
}

SFDate& SFDate::setYear(int aYear)
{
    if (aYear < 0)
    {
        std::cout << "year is not valid" << std::endl;
    }

    else
    {
        year = aYear;
    }

    return *this;
}

int SFDate::getDay() const
{
    return day;
}

int SFDate::getMonth() const
{
    return month;
}

int SFDate::getYear() const
{
    return year;
}

int SFDate::getWeekOfYear()
{
    int num_days = 0;
    for (int i = 1; i <= month; i++)
    {
        if (i == month)
        {
            num_days += day;
        }

        else
        {
            if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12)
            {
                num_days += 31;
            }

            else if (i == 4 || i == 6 || i == 9 || i == 11)
            {
                num_days += 30;
            }

            else
            {
                if ((year%4 == 0 && year%100 != 0) || (year%400 == 0))
                {
                    num_days += 29;
                }

                else
                {
                    num_days += 28;
                }
            }
        }
    }

    return (num_days/7)+1;
}

int SFDate::getDayOfYear()
{
    int num_days = 0;
    for (int i = 1; i <= month; i++)
    {
        if (i == month)
        {
            num_days += day;
        }

        else
        {
            if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12)
            {
                num_days += 31;
            }

            else if (i == 4 || i == 6 || i == 9 || i == 11)
            {
                num_days += 30;
            }

            else
            {
                if ((year%4 == 0 && year%100 != 0) || (year%400 == 0))
                {
                    num_days += 29;
                }

                else
                {
                    num_days += 28;
                }
            }
        }
    }

    return num_days;
}

int SFDate::getDayOfWeek()
{

    std::tm time_in = { 0, 0, 0, // second, minute, hour
                        day, month-1, year - 1900
                      }; // 1-based day, 0-based month, year since 1900

    std::time_t time_temp = std::mktime(&time_in);

    //Note: Return value of localtime is not threadsafe, because it might be
    // (and will be) reused in subsequent calls to std::localtime!
    const std::tm * time_out = std::localtime(&time_temp);

    return time_out->tm_wday;



}

int SFDate::daysInMonth()
{
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
    {
        return 31;
    }

    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        return 30;
    }

    else
    {
        if ((year%4 == 0 && year%100 != 0) || (year%400 == 0))
        {
            return 29;
        }

        else
        {
            return 28;
        }
    }
}

SFDate& SFDate::startOfMonth()
{
    day = 1;
    return *this;
}

SFDate& SFDate::endOfMonth()
{
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
    {
        day = 31;
        return *this;
    }

    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        day = 30;
        return *this;
    }

    else
    {
        if ((year%4 == 0 && year%100 != 0) || (year%400 == 0))
        {
            day = 29;
            return *this;
        }

        else
        {
            day = 28;
            return *this;
        }
    }
}

SFDate& SFDate::startOfYear()
{
    day = 1;
    month = 1;
    return *this;
}

SFDate& SFDate::endOfYear()
{
    day = 31;
    month = 12;
    return *this;
}

std::string SFDate::toDateString()
{
    std::string date;
    std::ostringstream c1;
    std::ostringstream c2;
    std::ostringstream c3;
    c1 << month;

    if (month < 10)
    {
        date = "0"+c1.str()+"/";

    }

    else
    {
        date = c1.str()+"/";
    }
    c2 << day;

    if (day < 10)
    {
        date += "0"+c2.str()+"/";
    }
    else
    {
        date += (c2.str() + "/");
    }

    c3 << year;
    date += c3.str();

    return date;

}

void SFDate::adjustHelper(int days)
{
    int i = 0;
    int n = days;

    if (days < 0)
    {
        n = -1*days;
    }

    while (i < n)
    {
        if (days < 0)
        {
            if (day == 1)
            {
                if (month == 1)
                {
                    year = year - 1;
                    month = 12;
                    day = 31;
                }

                else if (month == 5 || month == 7 || month == 10 || month == 12)
                {
                    month = month - 1;
                    day = 30;
                }

                else if(month == 2 || month == 4 || month == 6 || month == 8 || month == 9 || month == 11)
                {
                    day = 31;
                    month = month - 1;
                }

                else
                {
                    if ((year%4 == 0 && year%100 != 0) || (year%400 == 0))
                    {
                        day = 29;
                        month = 2;
                    }

                    else
                    {
                        month = 2;
                        day = 28;
                    }
                }
            }

            else
            {
                day = day - 1;
            }
            i = i + 1;
        }

        else
        {
            if (month == 12)
            {
                if (day == 31)
                {
                    year = year + 1;
                    month = 1;
                    day = 1;
                }

                else
                {
                    day++;
                }
            }

            else if (month == 1 || month == 3 || month == 5 || month == 7  || month == 8 || month == 10)
            {
                if (day == 31)
                {
                    month = month + 1;
                    day = 1;
                }

                else
                {
                    day++;
                }
            }

            else if(month == 4 || month == 6 || month == 9 || month == 11)
            {
                if (day == 30)
                {
                    day = 1;
                    month = month + 1;
                }

                else
                {
                    day++;
                }
            }

            else
            {
                if ((year%4 == 0 && year%100 != 0) || (year%400 == 0))
                {
                    if (day == 29)
                    {
                        day = 1;
                        month = 3;
                    }

                    else
                    {
                        day++;
                    }
                }

                else
                {
                    if (day == 28)
                    {
                        month = 3;
                        day = 1;
                    }

                    else
                    {
                        day++;
                    }
                }
            }
            i = i + 1;
        }
    }
}




