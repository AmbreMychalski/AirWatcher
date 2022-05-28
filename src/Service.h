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

#include <string>
#include <iostream>
#include <utility>
#include <vector>
#include <map>

#include "Database.h"
#include "Measure.h"
#include "Cleaner.h"
#include "Sensor.h"
#include "Date.h"
#include "Provider.h"

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

    std::vector<std::pair<Sensor *, double>> computeSimilarity(Sensor *sensor, std::vector<Sensor *> sensorList, Date startDate, Date endDate);
    std::vector<std::pair<Sensor *, double>> computeSimilarity(string sensorId, std::vector<Sensor *> sensorList, Date startDate, Date endDate);
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    // Renvoie la liste des capteurs de sensorList associés à leur similarité
    // par rapport au capteur de référence, sur une période donnée

    int computeMeanPointTimePeriod(Date startDate, Date endDate, std::pair<double, double> center, double (&returnArray)[NB_ATTRIBUTES], bool reliable = false);
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    // Retourne la moyenne de la qualité de l’air à un endroit donné sur une période donnée
    // (pondération sur les mesures puis renvoie de l’indice ATMO)
    // -1 si aucune donnée disponible, ou hors de la zone étudiée (ici hors de la France)

    int getUserPoints(string userId);
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    // Renvoie le nombre de points gagnés par l'utilisateur

    std::vector<Sensor *> *getUserSensors(string userId);
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    // Renvoie les capteurs associés à un utilisateur

    std::vector<Cleaner *> *getProviderCleaners(string providerId);
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    // Renvoie les cleaners associés à une entreprise

    void incrUserPoints(Sensor* sensor);
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    // Incrémente le nombre de points de l'utilisateur
    // possédant le capteur

    int computeATMOIndex(double o3, double so2, double no2, double pm10);
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    // Retourne l'index ATMO à partir des mesures d'O3, SO2, NO2 et PM10 données
    //    -> -1 si aucune donnée

    bool isProviderIdValid(string id);
    // Mode d'emploi :
    // id est l'identifiant de l'entreprise
    // Contrat :
    // Retourne vrai si l'entreprise existe dans la base de données.
    // Sinon, retourne faux.

    bool isUserIdValid(string id);
    // Mode d'emploi :
    // id est l'identifiant de l'individu privé
    // Contrat :
    // Retourne vrai si l'individu privé existe dans la base de données.
    // Sinon, retourne faux.

    Service();
    virtual ~Service();
    // Constructeur

    vector<Sensor *> getSensorList(bool reliable = false);
    vector<Cleaner *> getCleanerList();
    vector<Provider *> getProviderList();
    vector<User *> getUserList();

    User *getUserById(string id);

    Provider *getProviderById(string id);

    Sensor *getSensorById(string id);

    Cleaner *getCleanerById(string id);

    void computeMean(vector<Measure *> measures, double (&returnArray)[NB_ATTRIBUTES]);
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    // Retourne dans le tableau passé en paramètre
    // la moyenne des mesures des capteurs par attribut (type de mesure)

    vector<Sensor *> filterNeighbours(pair<double, double> coords, bool reliable = false);
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    // Retourne la liste des capteurs les plus proches
    //  - vecteur contenant les capteurs les plus proches du point donné,
    //    triés par distance croissante, dans un rayon de 100(km)
    //    maximum et avec 4 capteurs au maximum
    //  - vecteur contenant le capteur le plus proche si ils sont tous
    //    trop loin (distance > 100)
    //  - vecteur vide si il n'y a aucun capteur ou si le point est
    //    en dehors de la zone étudiée (la France ici)

    vector<Measure *> filterByPeriod(std::string sensorId, Date startdate, Date endDate);
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    // Retourne la liste des mesures faites par le capteur pendant la période donnée

protected:
    //----------------------------------------------------- Méthodes protégées
    //------------------------------------------------------------------ PRIVE

private:
    Database* database;
    //----------------------------------------------------- Méthodes privées

    //----------------------------------------------------- Attributs privés
};

//-------------------------------- Autres définitions dépendantes de <Service>

#endif // Service_H
