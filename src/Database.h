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
#include "User.h"
#include "Cleaner.h"
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
    void initialiseDB(string fAttribute, string fMesure, string fsensor, string fcleaner, string fprovider, string fuser);
    vector<Attribute> initialiseAttribute(string fAttribute);
    void initialiseMesure(string fMesure, vector<Attribute> attributeList);
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

    virtual ~Database(){
#ifdef MAP
    cout << "Appel au destructeur de <Database>" << endl;
#endif
    };
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
};

//-------------------------------- Autres définitions dépendantes de <Database>

#endif
