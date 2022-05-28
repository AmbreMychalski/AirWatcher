/*************************************************************************
                           Database  -  description
                             -------------------
    début                : 10/05/2022
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Database> (fichier Database.h) ----------------
#if !defined(DATABASE_H)
#define DATABASE_H

//--------------------------------------------------- Interfaces utilisées
#include <iostream>
#include "User.h"
#include "Sensor.h"
#include "Cleaner.h"
#include "Provider.h"
#include "Attribute.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Database>
//
//
//------------------------------------------------------------------------

class Database
{
    //----------------------------------------------------------------- PUBLIC

public:
    //----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //
    void initialiseDB(string fattribute, string fmeasure, string fsensor, string fcleaner, string fprovider, string fuser);
    void initialiseAttribute(string fattribute);
    void initialiseMeasure(string fmeasure);
    void initialiseSensor(string fsensor);
    void initialiseCleaner(string fcleaner);
    void initialiseProvider(string fprovider);
    void initialiseUser(string fuser);
    vector<Sensor *> getSensorList();
    vector<Cleaner *> getCleanerList();
    vector<Provider *> getProviderList();
    vector<User *> getUserList();
    Cleaner *getCleanerById(string cleanerId);
    Sensor *getSensorById(string sensorId);
    User *getUserById(string userId);
    Provider *getProviderById(string providerId);

    //------------------------------------------------- Surcharge d'opérateurs

    Database();
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Database();
    // Mode d'emploi :
    //
    // Contrat :
    //

    //------------------------------------------------------------------ PRIVE

protected:
    //----------------------------------------------------- Méthodes protégées

    //----------------------------------------------------- Attributs protégés
    vector<User*> userList;
    vector<Sensor*> sensorList;
    vector<Cleaner*> cleanerList;
    vector<Provider*> providerList;
    vector<Attribute*> attributeList;
};

//-------------------------------- Autres définitions dépendantes de <Database>

#endif
