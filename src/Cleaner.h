/*************************************************************************
                           Cleaner  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Cleaner> (fichier Cleaner.h) ----------------
#if ! defined ( CLEANER_H )
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
    string getId () const
    {
        return id;
    }

    pair<double, double> getCoords () const
    {
        return coords;
    }

    Date getStartDate () const
    {
        return startDate;
    }

    Date getEndDate () const
    {
        return endDate;
    }

    void setEndDate ( Date date)
    {
        endDate = date;
    }

//-------------------------------------------- Constructeurs - destructeur
    Cleaner (string id, pair<double, double> coords, Date startDate, Date endDate):
    id( id ), coords( coords ), startDate( startDate ), endDate( endDate)
    {
#ifdef MAP
    cout << "Appel au constructeur de <Cleaner>" << endl;
#endif
    }

    virtual ~Cleaner ( )
    {
#ifdef MAP
    cout << "Appel au destructeur de <Cleaner>" << endl;
#endif
    }

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    string id;
    pair<double, double> coords;
    Date startDate;
    Date endDate;

};

//-------------------------------- Autres définitions dépendantes de <Cleaner>

#endif // CLEANER_H

