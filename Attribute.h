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
    string getId(){
        return id;
    }

    string getUnit(){
        return unit;
    }

    string getDescription(){
        return description;
    }

    void setUnit(string unit_){
        this->id = id;
    }

    void setDescription(string Description_){
        this->id = id;
    }

    void setId(string id_){
        this->id = id;
    }

//------------------------------------------------- Surcharge d'opérateurs
  
//-------------------------------------------- Constructeurs - destructeur
  
    Attribute(string id_, string unit_, string description_ ):id(id_),unit(unit_),description(description_){}
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Attribute ( ){};
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

