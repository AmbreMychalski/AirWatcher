/*************************************************************************
                           Attribute  -  description
                             -------------------
    début                : 10/05/2022
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/
/*************************************************************************
                           Attribute  -  description
                             -------------------
    début                : 10/05/2022
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Attribute> (fichier Attribute.h) ----------------
#if ! defined ( ATTRIBUTE_H )
#define ATTRIBUTE_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <iostream>
using namespace std;
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Attribute>
//
//
//------------------------------------------------------------------------

class Attribute 
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    string getId()const{
        return id;
    }

    string getUnit()const{
        return unit;
    }

    string getDescription()const{
        return description;
    }

    void setUnit(string unit_){
        this->unit = unit_;
    }

    void setDescription(string description_){
        this->description = description_;
    }

    void setId(string id_){
        this->id = id_;
    }

//------------------------------------------------- Surcharge d'opérateurs
    Attribute & operator = ( const Attribute & aAttribute ){
        this->id = aAttribute.getId();
        this->unit = aAttribute.getUnit();
        this->description = aAttribute.getDescription();
        
        return *this;
    }
//-------------------------------------------- Constructeurs - destructeur
    Attribute ( ){
#ifdef MAP
    cout << "Appel au constructeur de <Attribute>" << endl;
#endif
    }

    Attribute ( const Attribute & aAttribute ){
#ifdef MAP
    cout << "Appel au constructeur par copie de <Attribute>" << endl;
#endif
        this->id = aAttribute.getId();
        this->unit = aAttribute.getUnit();
        this->description = aAttribute.getDescription();
    }

    Attribute(string id_, string unit_, string description_ ):id(id_),unit(unit_),description(description_){
#ifdef MAP
    cout << "Appel au constructeur de <Attribute>" << endl;
#endif
    }
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Attribute ( ){
#ifdef MAP
    cout << "Appel au destructeur de <Attribute>" << endl;
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
    string id;
    string unit;
    string description;
};

//-------------------------------- Autres définitions dépendantes de <Xxx>

#endif // XXX_H
