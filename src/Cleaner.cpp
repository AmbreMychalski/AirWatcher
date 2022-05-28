/*************************************************************************
                           Cleaner  -  description
                             -------------------
    début                : $CLEANER$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Cleaner> (fichier Cleaner.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <iomanip>

//------------------------------------------------------ Include personnel
#include "Cleaner.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
string Cleaner::getId() const
{
    return id;
}

pair<double, double> Cleaner::getCoords() const
{
    return coords;
}

Date& Cleaner::getStartDate() const
{
    return *(startDate);
}

Date& Cleaner::getEndDate() const
{
    return *(endDate);
}

void Cleaner::setEndDate(Date* date)
{
    delete endDate;
    endDate = date;
}

Cleaner::Cleaner(string id, pair<double, double> coords, Date* startDate, Date* endDate) : id(id), coords(coords), startDate(startDate), endDate(endDate)
{
#ifdef MAP
    cout << "Appel au constructeur de <Cleaner>" << endl;
#endif
}

Cleaner::~Cleaner()
{
#ifdef MAP
    cout << "Appel au destructeur de <Cleaner>" << endl;
#endif
    delete startDate;
    delete endDate;
}
//------------------------------------------------- Surcharge d'opérateurs

// Fonction ordinaire
ostream &operator<<(ostream &stream, const Cleaner &c)
{
    // ostream désigne la classe flux en sortie
    stream << "Id: ";
    stream << setiosflags(ios::fixed) << setw(10) << left << c.id;
    stream << " | Latitude: ";
    stream << setiosflags(ios::fixed) << setw(6) << left << setprecision(1) << c.coords.first;
    stream << " | Longitude: ";
    stream << setiosflags(ios::fixed) << setw(6) << left << setprecision(1) << c.coords.second;
    stream << " | Date de mise en place: ";
    stream << *(c.startDate);
    stream << " | Date de fin: ";
    stream << *(c.endDate);

    return stream;
}