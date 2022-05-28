/*************************************************************************
                           Cleaner  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Cleaner> (fichier Cleaner.h) ----------------
#if !defined(CLEANER_H)
#define CLEANER_H

//--------------------------------------------------- Interfaces utilisées
#include <iostream>
#include "Date.h"
using namespace std;
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Cleaner>
//
//
//------------------------------------------------------------------------

class Cleaner
{
    //----------------------------------------------------------------- PUBLIC

public:
    //----------------------------------------------------- Méthodes publiques
    friend ostream &operator<<(ostream &stream, const Cleaner &c);

    string getId() const;

    pair<double, double> getCoords() const;

    Date& getStartDate() const;

    Date& getEndDate() const;

    void setEndDate(Date* date);

    //-------------------------------------------- Constructeurs - destructeur
    Cleaner(string id, pair<double, double> coords, Date* startDate, Date* endDate);

    virtual ~Cleaner();

    //------------------------------------------------------------------ PRIVE

protected:
    //----------------------------------------------------- Méthodes protégées

    //----------------------------------------------------- Attributs protégés
    string id;
    pair<double, double> coords;
    Date* startDate;
    Date* endDate;
};

//-------------------------------- Autres définitions dépendantes de <Cleaner>

#endif // CLEANER_H
