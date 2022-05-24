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

    void setId(string id);

    void setReliable(bool reliable);

    void setCoords(double x, double y);

    void addMeasure(Measure *measure);

    string getId() const;

    bool getReliable() const;

    pair<double, double> getCoords() const;

    vector<Measure *> getMeasureList() const;

    vector<Measure *> getMeasureList();

    friend ostream &operator<<(ostream &stream, const Sensor &s);

    //-------------------------------------------- Constructeurs - destructeur
    Sensor();

    Sensor(string id, bool reliable, double x, double y);
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Sensor();
    // Mode d'emploi :
    //
    // Contrat :
    //

    bool operator<(const Sensor &s) const;

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
