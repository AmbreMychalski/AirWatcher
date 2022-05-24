/*************************************************************************
                           Sensor  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/
#include <string>
#include <iostream>
#include <vector>
#include "Measure.h"

using namespace std;

//---------- Interface de la classe <Sensor> (fichier Sensor.h) ----------------
#if !defined(Sensor_H)
#define Sensor_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Sensor>
//
//
//------------------------------------------------------------------------

class Sensor
{
    //----------------------------------------------------------------- PUBLIC

public:
    //----------------------------------------------------- Méthodes publiques
    void setId(string id)
    {
        this->id = id;
    }

    void setReliable(bool reliable)
    {
        this->reliable = reliable;
    }

    void setCoords(double x, double y)
    {
        this->coords = make_pair(x, y);
    }

    void addMeasure(Measure *measure)
    {
        this->measureList.push_back(measure);
    }

    string getId() const
    {
        return this->id;
    }

    bool getReliable() const
    {
        return this->reliable;
    }

    pair<double, double> getCoords() const
    {
        return this->coords;
    }

    vector<Measure *> getMeasureList()
    {
        return measureList;
    }

    //-------------------------------------------- Constructeurs - destructeur
    Sensor() {
#ifdef MAP
    cout << "Appel au constructeur de <Sensor>" << endl;
#endif
    }

    Sensor(string id, bool reliable, double x, double y)
    {
#ifdef MAP
    cout << "Appel au constructeur de <Sensor>" << endl;
#endif
        this->id = id;
        this->reliable = reliable;
        // pair <double, double> coordonnees=make_pair(x, y);
        this->coords = make_pair(x, y);
    }
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Sensor() {
#ifdef MAP
    cout << "Appel au destructeur de <Sensor>" << endl;
#endif
    }
    // Mode d'emploi :
    //
    // Contrat :
    //

    bool operator<(const Sensor &s) const
    // Algorithme :
    //
    {
        return (this->id < s.getId());
    }

    //------------------------------------------------------------------ PRIVE

protected:
    //----------------------------------------------------- Méthodes protégées

    //----------------------------------------------------- Attributs protégés
    string id;
    bool reliable;
    pair<double, double> coords;
    vector<Measure *> measureList;
};

//-------------------------------- Autres définitions dépendantes de <Sensor>

#endif // Sensor_H
