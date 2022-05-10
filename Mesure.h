/*************************************************************************
                           Mesure  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Mesure> (fichier Mesure.h) ----------------
#if ! defined ( Mesure_H )
#define Mesure_H
#include "Attribute.h"
#include "Date.h"
//
//
//------------------------------------------------------------------------

class Mesure 
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void setValue ( double val ){
        this->value = val;
    }
    // Mode d'emploi :
    //
    // Contrat :
    //

    void setDate ( Date date ){
        this->date = date;
    }
    // Mode d'emploi :
    //
    // Contrat :
    //

    void setAttribute ( Attribute &attr ){
        this->attribute = attr;
    }
    // Mode d'emploi :
    //
    // Contrat :
    //

    double getValue ( )const {
        return this->value;
    }
    // Mode d'emploi :
    //
    // Contrat :
    //

    Date getDate ( )const{
        return this->date;
    }
    // Mode d'emploi :
    //
    // Contrat :
    //

    Attribute getAttribute ( )const{
        return this->attribute;
    }
    // Mode d'emploi :
    //
    // Contrat :
    //

//-------------------------------------------- Constructeurs - destructeur
    Mesure ( ){}

    Mesure ( const Mesure & aMesure ){
        this->value = aMesure.getValue();
        this->date = aMesure.getDate();
        this->attribute = aMesure.getAttribute();
    }
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Mesure ( double value, Date &date, Attribute &attribute){
        this->value=value;
        this->date=date;
        this->attribute = attribute;
    }
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Mesure ( ){}
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    double value;
    Date date;
    Attribute attribute;
};

//-------------------------------- Autres définitions dépendantes de <Xxx>

#endif // Mesure_H

