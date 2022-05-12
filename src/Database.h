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
#include <Sensor.h>
#include <Cleaner.h>
#include <User.h>
#include "Provider.h"
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
    void initialiseDB(string fAttribute, string fMesure, string fsensor, string fcleaner, string fprovider);
    void initialiseAttribute(string fAttribute);
    void initialiseMesure(string fMesure);
    void initialiseSensor(string fsensor);
    void initialiseCleaner(string fcleaner);
    void initialiseProvider(string fprovider);
    Cleaner getCleanerByid(string cleanerId);
    Sensor getSensorByid(string sensorId);
    vector<Sensor> getSensorList();

    //------------------------------------------------- Surcharge d'opérateurs

    //-------------------------------------------- Constructeurs - destructeur

    Database(){};
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
    vector<User> userList;
    vector<Sensor> sensorList;
    vector<Cleaner> cleanerList;
    vector<Provider> providerList;
};

//-------------------------------- Autres définitions dépendantes de <Database>

#endif
