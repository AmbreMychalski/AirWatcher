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

//------------------------------------------------------ Include personnel
#include "Date.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques


//------------------------------------------------- Surcharge d'opérateurs
bool Date::operator == ( const Date & date )
{
    return year==date.getYear() && month==date.getMonth() && day==date.getDay() && hour==date.getHour() && minute==date.getMinute() && second==date.getSecond();
}

bool Date::operator < ( const Date & date )
{
    bool res = false;
    if (year<date.getYear())
    {
        res = true;
    }
    else if (year==date.getYear())
    {
        if (month<date.getMonth())
        {
            res = true;
        }
        else if (month==date.getMonth())
        {
            if (day<date.getDay())
            {
                res = true;
            }
            else if (day==date.getDay())
            {
                if (hour<date.getHour())
                {
                    res = true;
                }
                else if (hour==date.getHour())
                {
                    if (minute<date.getMinute())
                    {
                        res = true;
                    }
                    else if (minute==date.getMinute())
                    {
                        if (second<date.getSecond())
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

bool Date::operator <= ( const Date & date )
{
    return *this==date || *this<date;
}

bool Date::operator != ( const Date & date )
{
    return !(*this==date);
}

bool Date::operator > ( const Date & date )
{
    return !(*this<=date);
}

bool Date::operator >= ( const Date & date )
{
    return !(*this<date);
}