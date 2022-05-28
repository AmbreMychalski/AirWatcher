/*************************************************************************
                           Date  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Date> (fichier Date.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <iomanip>

//------------------------------------------------------ Include personnel
#include "Date.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

//------------------------------------------------- Surcharge d'opérateurs
bool Date::operator==(const Date &date)
{
    return year == date.getYear() && month == date.getMonth() && day == date.getDay() && hour == date.getHour() && minute == date.getMinute() && second == date.getSecond();
}

bool Date::operator<(const Date &date)
{
    bool res = false;
    if (year < date.getYear())
    {
        res = true;
    }
    else if (year == date.getYear())
    {
        if (month < date.getMonth())
        {
            res = true;
        }
        else if (month == date.getMonth())
        {
            if (day < date.getDay())
            {
                res = true;
            }
            else if (day == date.getDay())
            {
                if (hour < date.getHour())
                {
                    res = true;
                }
                else if (hour == date.getHour())
                {
                    if (minute < date.getMinute())
                    {
                        res = true;
                    }
                    else if (minute == date.getMinute())
                    {
                        if (second < date.getSecond())
                        {
                            res = true;
                        }
                    }
                }
            }
        }
    }

    return res;
}

bool Date::operator<=(const Date &date)
{
    return *this == date || *this < date;
}

bool Date::operator!=(const Date &date)
{
    return !(*this == date);
}

bool Date::operator>(const Date &date)
{
    return !(*this <= date);
}

bool Date::operator>=(const Date &date)
{
    return !(*this < date);
}

// Fonction ordinaire
ostream &operator<<(ostream &stream, const Date &d)
{
    stream << setfill('0') << right << setw(2) << d.day << "/" << setw(2) << d.month << "/" << setw(4) << d.year << " " << setw(2) << d.hour << ":" << setw(2) << d.minute << ":" << setw(2) << d.second << setfill(' ') << left;
    return stream;
}

istream &operator>>(istream &stream, Date &d)
{
    stream >> d.day;
    stream.ignore(1, '/');
    stream >> d.month;
    stream.ignore(1, '/');
    stream >> d.year;
    stream.ignore(1, ' ');
    stream >> d.hour;
    stream.ignore(1, ':');
    stream >> d.minute;
    stream.ignore(1, ':');
    stream >> d.second;
    return stream;
}

Date::Date(const Date& date) : year(date.getYear()), month(date.getMonth()), day(date.getDay()), hour(date.getHour()), minute(date.getMinute()), second(date.getSecond())
{
#ifdef MAP
    cout << "Appel au constructeur par copie de <Date>" << endl;
#endif
}

Date::Date(int y, int M, int d, int h, int m, int s) : year(y), month(M), day(d), hour(h), minute(m), second(s)
{
#ifdef MAP
    cout << "Appel au constructeur de <Date>" << endl;
#endif
}

Date::Date()
{
#ifdef MAP
    cout << "Appel au constructeur de <Date>" << endl;
#endif
}

Date::~Date()
{
#ifdef MAP
    cout << "Appel au destructeur de <Date>" << endl;
#endif
}