/*************************************************************************
                           User  -  description
                             -------------------
    début                : 10/05/2022
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <User> (fichier User.h) ----------------
#if !defined(USER_H)
#define USER_H

//--------------------------------------------------- Interfaces utilisées
#include "Sensor.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <User>
//
//
//------------------------------------------------------------------------

class User
{
    //----------------------------------------------------------------- PUBLIC

public:
    //----------------------------------------------------- Méthodes publiques
    string getId() const
    {
        return id;
    }

    string getEmail() const
    {
        return email;
    }

    string getPassword() const
    {
        return password;
    }

    int getNbPoints() const
    {
        return nbPoints;
    }

    int getNbSensor() const
    {
        return sensorList.size();
    }

    vector<Sensor *> *getSensorList()
    {
        return &(sensorList);
    }

    void setId(string id_)
    {
        this->id = id_;
    }

    void setPassword(string password_)
    {
        this->password = password_;
    }

    void setNbPoints(int nbPoints_)
    {
        this->nbPoints = nbPoints_;
    }

    void addSensor(Sensor *sensor)
    {
        this->sensorList.push_back(sensor);
    }

    bool isReliable()
    {
        return (*sensorList.begin())->getReliable();
    }

    //------------------------------------------------- Surcharge d'opérateurs

    //-------------------------------------------- Constructeurs - destructeur

    User(string id_) : id(id_)
    {
        nbPoints = 0;
    }
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~User(){};
    // Mode d'emploi :
    //
    // Contrat :
    //

    //------------------------------------------------------------------ PRIVE

protected:
    //----------------------------------------------------- Méthodes protégées

    //----------------------------------------------------- Attributs protégés
    string id;
    string email;
    string password;
    int nbPoints;
    vector<Sensor *> sensorList;
};

//-------------------------------- Autres définitions dépendantes de <Xxx>

#endif // USER_H
