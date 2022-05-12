/*************************************************************************
                           Measure  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Measure> (fichier Measure.h) ----------------
#if ! defined ( Measure_H )
#define Measure_H
#include "Attribute.h"
#include "Date.h"
//
//
//------------------------------------------------------------------------

class Measure 
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

    string getSensorId ( )const {
        return this->sensorId;
    }

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
    Measure ( ){}

    Measure ( const Measure & aMeasure ){
        this->value = aMeasure.getValue();
        this->date = aMeasure.getDate();
        this->attribute = aMeasure.getAttribute();
    }
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Measure ( double value, Date &date, Attribute &attribute, string sensorId){
        this->value=value;
        this->date=date;
        this->attribute = attribute;
        this->sensorId = sensorId;
    }
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Measure ( ){}
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
    string sensorId;
};

//-------------------------------- Autres définitions dépendantes de <Xxx>

#endif // Measure_H

