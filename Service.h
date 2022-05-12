/*************************************************************************
                           Service  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Service> (fichier Service.h) ----------------
#if !defined(SERVICE_H)
#define SERVICE_H

#include <iostream>
#include <utility>
#include <vector>
#include <map>

#include "Database.h"
#include "Measure.h"
#include "Cleaner.h"
#include "Sensor.h"
#include "Date.h"

using namespace std;

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes
const int NB_ATTRIBUTES = 4;
//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Service>
//
//
//------------------------------------------------------------------------

class Service
{
    //----------------------------------------------------------------- PUBLIC

public:
    //----------------------------------------------------- Méthodes publiques

    map<Sensor, double> computeSimilarity(string sensorId) const;
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    // Renvoie la liste des capteurs de sensorList associés à leur similarité
    // par rapport au capteur de référence, sur une période donnée

    double computeMeanPointTimePeriod(Date date, Date endDate, pair<double, double> center, double radius) const;
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    // Retourne la moyenne de la qualité de l’air à un endroit donné sur une période donnée
    // (pondération sur les mesures puis renvoie de l’indice ATM

    int getUserPoints(string userId) const;
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    // Renvoie le nombre de points gagnés par l'utilisateur

    vector<Sensor> getUserSensors(string idUser) const;
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    // Renvoie les capteurs associés à un utilisateur

    vector<Cleaner> getProviderCleaners(string idProvider) const;
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    // Renvoie les cleaners associés à une entreprise

    int computeATMOIndex(double o3, double so2, double no2, double pm10) const;
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    // Retourne l'index ATMO à partir des mesures d'O3, SO2, NO2 et PM10 données

    void computeMean(vector<Measure> measures, double (&returnArray)[NB_ATTRIBUTES]);
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    // Retourne dans le tableau passé en paramètre
    // la moyenne des mesures des capteurs par attribut (type de mesure)

    vector<Sensor> filterNeighbours(pair<double, double> coords);
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    // Retourne la liste des capteurs les plus proches

    vector<Sensor> filterByPeriod(Date date, Date endDate);
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    // Retourne la liste des capteurs ayant des mesures dans la même période de temps

    //------------------------------------------------- Surcharge d'opérateurs
    Service &operator=(const Service &unService);
    // Mode d'emploi :
    //
    // Contrat :
    //

    //-------------------------------------------- Constructeurs - destructeur
    Service(const Service &unService);
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Service();
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Service();
    // Mode d'emploi :
    //
    // Contrat :
    //

    //------------------------------------------------------------------ PRIVE

private:
    Database *database;
    //----------------------------------------------------- Méthodes privées

    //----------------------------------------------------- Attributs privés
protected:
    //----------------------------------------------------- Méthodes protégées

    //----------------------------------------------------- Attributs protégés
};

//-------------------------------- Autres définitions dépendantes de <Service>

#endif // Service_H
