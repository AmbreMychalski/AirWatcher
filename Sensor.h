/*************************************************************************
                           Sensor  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/
#include<string>
#include<iostream>
#include<vector>
#include "Mesure.h"

using namespace std;

//---------- Interface de la classe <Sensor> (fichier Sensor.h) ----------------
#if ! defined ( Sensor_H )
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
    void setId(string id){
        this->id = id;
    }

    void setReliable(bool reliable){
        this->reliable = reliable;
    }

    void setCoords(double x, double y){
        this->coords = make_pair(x, y);
    }

    void addListMesures(Mesure mes){
        this->listMesures.push_back(mes);
    }

    string getId( ){
        return this->id;
    }

    bool getReliable( ){
        return this->reliable;
    }

    pair<double,double> getCoords( ){
        return this->coords;
    }

    vector <Mesure>* getListMesures( ){
        return &(this->listMesures);
    }

//-------------------------------------------- Constructeurs - destructeur
    Sensor ( ){}

    Sensor ( string id, bool reliable, double x, double y){
        this->id=id;
        this->reliable=reliable;
        //pair <double, double> coordonnees=make_pair(x, y);
        this->coords =make_pair(x, y);
    }
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Sensor ( ){}
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    string id;
    bool reliable;
    std::pair<double,double> coords;
    std::vector<Mesure> listMesures;
};

//-------------------------------- Autres définitions dépendantes de <Sensor>

#endif // Sensor_H

