/*************************************************************************
                           User  -  description
                             -------------------
    début                : 10/05/2022
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <User> (fichier User.h) ----------------
#if ! defined ( USER_H )
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
    string getId(){
        return id;
    }

    string getEmail(){
        return email;
    }

    string getPassword(){
        return password;
    }

    

    int getNbPoints(){
        return nbPoints;
    }

    vector<Sensor *>* getListSensor(){
        return &(listSensors);
    }

    void setId(string id_){
        this->id = id_;
    }

    void setPassword(string password_){
        this->password = password_;
    }

    void setNbPoints(int nbPoints_){
        this->nbPoints = nbPoints_;
    }

    void addSensors(Sensor *sensor){
        this->listSensors.push_back(sensor);
    }
    
    bool isReliable(){
       return (*listSensors.begin())->getReliable();
    }

//------------------------------------------------- Surcharge d'opérateurs
  
//-------------------------------------------- Constructeurs - destructeur
  
    User(string id_, string email_, string password_, int nbPoints_):
    id(id_),email(email_),password(password_),nbPoints(nbPoints_){

    }
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~User ( ){};
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
    vector <Sensor *> listSensors;


};

//-------------------------------- Autres définitions dépendantes de <Xxx>

#endif // USER_H

