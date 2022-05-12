/*************************************************************************
                           Provider  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Provider> (fichier Provider.h) ----------------
#if !defined(PROVIDER_H)
#define PROVIDER_H

//--------------------------------------------------- Interfaces utilisées
#include <iostream>
#include <vector>
#include "Cleaner.h"
using namespace std;
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Provider>
//
//
//------------------------------------------------------------------------

class Provider
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

    int getNbCleaner() const
    {
        return cleanerList.size();
    }

    const vector<Cleaner *> *getCleanerList() const
    {
        return &(cleanerList);
    }

    void addCleaner(Cleaner *cleaner)
    {
        cleanerList.push_back(cleaner);
    }

    //-------------------------------------------- Constructeurs - destructeur
    Provider(string id, string email, string password) : id(id), email(email), password(password)
    {
#ifdef MAP
        cout << "Appel au constructeur de <Provider>" << endl;
#endif
    }

    Provider()
    {
#ifdef MAP
        cout << "Appel au constructeur de <Provider>" << endl;
#endif
    }

    virtual ~Provider()
    {
#ifdef MAP
        cout << "Appel au destructeur de <Provider>" << endl;
#endif
    }

    //------------------------------------------------------------------ PRIVE

protected:
    //----------------------------------------------------- Méthodes protégées

    //----------------------------------------------------- Attributs protégés
    string id;
    string email;
    string password;
    vector<Cleaner *> cleanerList;
};

//-------------------------------- Autres définitions dépendantes de <Provider>

#endif // PROVIDER_H
