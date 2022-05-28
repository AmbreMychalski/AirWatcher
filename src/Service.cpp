/*************************************************************************
                           Service  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Service> (fichier Service.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm> // std::sort
#include <tgmath.h>
//------------------------------------------------------ Include personnel
#include "Service.h"

//------------------------------------------------------------- Constantes
const double MIN_LONGITUDE = -2;
const double MAX_LONGITUDE = 6;
const double MIN_LATITUDE = 43.5;
const double MAX_LATITUDE = 48;
const int MAX_NEAREST_SENSORS_NUMBER = 4;
const int MIN_NEAREST_SENSORS_NUMBER = 1;
const int MAX_NEAREST_SENSORS_RADIUS = 100;

const int THRESHOLD_STEP = 10;
const double PM_10[] = {80, 65, 50, 42, 35, 28, 21, 14, 7, 0};
const double NO_2[] = {400, 275, 200, 165, 135, 110, 85, 55, 30, 0};
const double SO_2[] = {500, 400, 300, 250, 200, 160, 120, 80, 40, 0};
const double O_3[] = {240, 210, 180, 150, 130, 105, 80, 55, 30, 0};

//----------------------------------------------------------------- PUBLIC

long double toRadians(const long double degree)
{
    // cmath library in C++
    // defines the constant
    // M_PI as the value of
    // pi accurate to 1e-30
    long double one_deg = (M_PI) / 180;
    return (one_deg * degree);
}

long double distance(long double lat1, long double long1,
                     long double lat2, long double long2)
{
    // Convert the latitudes
    // and longitudes
    // from degree to radians.
    lat1 = toRadians(lat1);
    long1 = toRadians(long1);
    lat2 = toRadians(lat2);
    long2 = toRadians(long2);

    // Haversine Formula
    long double dlong = long2 - long1;
    long double dlat = lat2 - lat1;

    long double ans = pow(sin(dlat / 2), 2) +
                      cos(lat1) * cos(lat2) *
                          pow(sin(dlong / 2), 2);

    ans = 2 * asin(sqrt(ans));

    // Radius of Earth in
    // Kilometers, R = 6371
    // Use R = 3956 for miles
    long double R = 6371;

    // Calculate the result
    ans = ans * R;

    return ans;
}

// Driver function to sort the vector elements
// by second element of pairs
bool sortBySec(const pair<Sensor*, double> &a,
               const pair<Sensor*, double> &b)
{
    return (a.second > b.second);
}

// Driver function to sort the sensors
// by second element of pairs
bool sortByDistance(Sensor* a,
                    Sensor* b,
                    const pair<double,double> &coords)
{
    double lat2 = coords.first;
    double long2 = coords.second;
    return (distance(a->getCoords().first, a->getCoords().second, lat2, long2) < distance(b->getCoords().first, b->getCoords().second, lat2, long2));
}

//----------------------------------------------------- Méthodes publiques
Sensor *Service::getSensorById(string id)
{
    return database->getSensorById(id);
}

Cleaner *Service::getCleanerById(string id)
{
    return database->getCleanerById(id);
}

User *Service::getUserById(string id)
{
    return database->getUserById(id);
}

Provider *Service::getProviderById(string id)
{
    return database->getProviderById(id);
}

std::vector<std::pair<Sensor *, double>> Service::computeSimilarity(string sensorId, std::vector<Sensor *> sensorList, Date startDate, Date endDate)
{
    vector<std::pair<Sensor *, double>> similarityList;
    Sensor* sensorRef = getSensorById(sensorId);
    if (sensorRef != nullptr)
    {
        similarityList = computeSimilarity(sensorRef, sensorList, startDate, endDate);
    }
    return similarityList;
}
std::vector<std::pair<Sensor *, double>> Service::computeSimilarity(Sensor *sensorRef, std::vector<Sensor *> sensorList, Date startDate, Date endDate)
{
    
    std::vector<Measure *> measureListRef = filterByPeriod(sensorRef->getId(), startDate, endDate);
    double meanRefTab[NB_ATTRIBUTES];
    double meanTab[NB_ATTRIBUTES];
    computeMean(measureListRef, meanRefTab);
    

    std::vector<std::pair<Sensor *, double>> distanceList;
    std::vector<std::pair<Sensor *, double>> similarityList;
    double distanceMax = 0;
    for (Sensor* sensor : sensorList)
    {
        // Si le capteur est bien distinct du capteur de référence
        if (sensorRef->getId() != sensor->getId())
        {
            double distance = 0;
            std::vector<Measure *> measureList = filterByPeriod(sensor->getId(), startDate, endDate);
            if (!measureList.empty())
            {
                incrUserPoints(sensor);

                computeMean(measureList, meanTab);

                for (int i = 0; i < NB_ATTRIBUTES; ++i)
                {

                    /// Incrémenter la distance totale par la distance
                    // entre les valeurs moyennes mesurées par ce capteur et le capteur de
                    // référence, à condition que ces valeurs existent bien
                    if (meanRefTab[i] >= 0.0 && meanTab[i] >= 0.0){
                        distance = distance + abs(meanRefTab[i] - meanTab[i]);
                    }
                }
                // delete measureList;
            }
            distanceList.push_back(make_pair(sensor, distance));
            distanceMax = max(distance, distanceMax);
        }
    }
    // Si tous les capteurs ne sont pas exactement identiques
    if (distanceMax > 0.0)
    {
        // Normaliser les distances entre 0 et 1
        for (pair<Sensor *, double>& elemDistance : distanceList)
        {
            elemDistance.second = elemDistance.second / distanceMax;
        }
    }
    for (pair<Sensor *, double>& elemNormalizedDistance : distanceList)
    {
        double similarity = 1 - elemNormalizedDistance.second;
        similarityList.push_back(make_pair(elemNormalizedDistance.first, similarity));
    }
    // Using sort() function to sort by 2nd element
    // of pair
    sort(similarityList.begin(), similarityList.end(), sortBySec);
    return similarityList;
}

int Service::computeMeanPointTimePeriod(Date startDate, Date endDate, std::pair<double, double> center, double (&returnArray)[NB_ATTRIBUTES], bool reliable)
{
    int atmoIndex;
    for (int i = 0; i < NB_ATTRIBUTES; ++i)
    {
        returnArray[i] = -1.0;
        // on initialise le tableau à -1.0 (ie pas de mesure)
    }

    std::vector<Sensor *> listSensorNeighbours = filterNeighbours(center, reliable);

    // Pour chaque type de mesure de chaque capteur, on fait leur moyenne sur
    // la période de temps, puis on pondère cette moyenne
    // par leur distance au point passé en paramètre
    const int LENGTH = listSensorNeighbours.size();
    if (LENGTH==1)
    {
        // on distingue ce cas pour ne pas faire la pondération
        Sensor *sensor = listSensorNeighbours.at(0);
        std::vector<Measure *> measuresList = filterByPeriod(sensor->getId(), startDate, endDate);
        if (!measuresList.empty())
        {
            incrUserPoints(sensor);
            double measuresMean[NB_ATTRIBUTES];
            computeMean(measuresList, measuresMean);
            for (int i = 0; i < NB_ATTRIBUTES; ++i)
            {
                returnArray[i] = measuresMean[i];
            }
        }
    }
    else
    {
        double distanceSum = 0;
        // On trouve la distance totale séparant les capteurs voisins du point
        // passé en paramètre
        vector<long double> dist(LENGTH);
        int j = 0;
        for (Sensor *sensor : listSensorNeighbours)
        {
            double lat1 = center.first;
            double long1 = center.second;
            double lat2 = sensor->getCoords().first;
            double long2 = sensor->getCoords().second;
            dist[j] = distance(lat1, long1, lat2, long2);
            distanceSum += dist[j];
            ++j;
        }
        j = 0;
        for (Sensor *sensor : listSensorNeighbours)
        {
            std::vector<Measure *> measuresList = filterByPeriod(sensor->getId(), startDate, endDate);
            if (!measuresList.empty())
            {
                incrUserPoints(sensor);
                double measuresMean[NB_ATTRIBUTES];
                computeMean(measuresList, measuresMean);
                double ponderation = (1 - dist[j] / distanceSum) / (LENGTH - 1);

                for (int i = 0; i < NB_ATTRIBUTES; ++i)
                {
                    if (measuresMean[i]>= 0)
                    {
                        if (returnArray[i] == -1.0)
                        {
                            returnArray[i] = measuresMean[i] * ponderation;
                            // on reinitialise le tableau de retour avec la première mesure
                        }
                        else
                        {
                            returnArray[i] += measuresMean[i] * ponderation;
                            // on ajoute la mesure
                        }
                    }
                    // si la valeur de la mesure est à -1.0, on ne la compte pas
                }
            }
            ++j;
        }
    }
    atmoIndex = computeATMOIndex(returnArray[0], returnArray[1], returnArray[2], returnArray[3]);

    return atmoIndex;
}

int Service::getUserPoints(string userId)
{
    int nbPoints = 0;
    for (User *user : database->getUserList())
    {
        if (user->getId().compare(userId))
        {
            nbPoints = user->getNbPoints();
        }
    }
    return nbPoints;
}

std::vector<Sensor *> *Service::getUserSensors(string userId)
{
    for (User *user : database->getUserList())
    {
        if (user->getId().compare(userId))
        {
            return user->getSensorList();
        }
    }
    return NULL;
}

vector<Cleaner *> *Service::getProviderCleaners(string providerId)
{
    Provider *provider = database->getProviderById(providerId);
    if (provider != nullptr)
    {
        return provider->getCleanerList();
    }
    return nullptr;
}

void Service::incrUserPoints(Sensor* sensor)
{
    User* user = sensor->getUser();
    if (user != NULL)
    {
        user->incrPoints();
    }
}

// https://fr.wikipedia.org/wiki/Indice_de_qualit%C3%A9_de_l%27air
int Service::computeATMOIndex(double o3, double so2, double no2, double pm10)
{
    int index = -1;
    for (int i = 0; i < THRESHOLD_STEP; ++i)
    {
        if (pm10 >= PM_10[i] || no2 >= NO_2[i] || so2 >= SO_2[i] || o3 >= O_3[i])
        {
            return THRESHOLD_STEP - i;
        }
    }
    return index;
}

void Service::computeMean(const vector<Measure *> measures, double (&returnArray)[NB_ATTRIBUTES])
{
    double o3 = 0.0;
    double so2 = 0.0;
    double no2 = 0.0;
    double pm10 = 0.0;
    double nbO3 = 0.0, nbSo2 = 0.0, nbNo2 = 0.0, nbPm10 = 0.0;
    for (Measure *measure : measures)
    {
        if (measure->getAttribute().getId() == "O3")
        {
            o3 += measure->getValue();
            nbO3++;
        }
        else if (measure->getAttribute().getId() == "SO2")
        {
            so2 += measure->getValue();
            nbSo2++;
        }
        else if (measure->getAttribute().getId() == "NO2")
        {
            no2 += measure->getValue();
            nbNo2++;
        }
        else if (measure->getAttribute().getId() == "PM10")
        {
            pm10 += measure->getValue();
            nbPm10++;
        }
    }
    returnArray[0] = nbO3 ? o3 / nbO3 : -1.0;
    returnArray[1] = nbSo2 ? so2 / nbSo2 : -1.0;
    returnArray[2] = nbNo2 ? no2 / nbNo2 : -1.0;
    returnArray[3] = nbPm10 ? pm10 / nbPm10 : -1.0;
}

vector<Sensor *> Service::filterNeighbours(pair<double, double> coords, bool reliable)
{

    std::vector<Sensor *> sensors;
    if (coords.first < MIN_LATITUDE || coords.first > MAX_LATITUDE || coords.second < MIN_LONGITUDE || coords.second > MAX_LONGITUDE)
    {
    }
    else
    {
        int i = 0;

        vector<Sensor *> sensorList = getSensorList(reliable);
        sort(sensorList.begin(), sensorList.end(), [coords](Sensor* i, Sensor* j){ return sortByDistance(i,j,coords); });
        const int LENGTH = sensorList.size();
        double lat1 = coords.first;
        double long1 = coords.second;
        
        while (i < LENGTH && sensors.size() < MAX_NEAREST_SENSORS_NUMBER)
        {
            Sensor *sensor = sensorList[i];
            double lat2 = sensor->getCoords().first;
            double long2 = sensor->getCoords().second;
            long double dist = distance(lat1, long1, lat2, long2);
            if (dist < MAX_NEAREST_SENSORS_RADIUS)
            {
                sensors.push_back(sensor);
            }
            ++i;
        }
        if (sensors.size() == 0 && sensorList.size() > 0)
        {
            sensors.push_back(sensorList[0]);
        }
    }
    return sensors;
}

vector<Measure *> Service::filterByPeriod(string sensorId, Date startDate, Date endDate)
{
    Sensor *sensor = database->getSensorById(sensorId);
    std::vector<Measure *> targetMeasures;
    if (sensor != nullptr)
    {
        const vector<Measure *> allMeasures = sensor->getMeasureList();

        for (long unsigned int i = 0; i < allMeasures.size(); ++i)
        {
            Date date = allMeasures[i]->getDate();
            if (startDate <= date && date <= endDate)
            {
                targetMeasures.push_back(allMeasures[i]);
            }
        }
    }
    return targetMeasures;
}

bool Service::isProviderIdValid(std::string id)
{
    return database->getProviderById(id) != nullptr;
}

bool Service::isUserIdValid(std::string id)
{
    return database->getUserById(id) != nullptr;
}

vector<Sensor *> Service::getSensorList(bool reliable)
{
    if (reliable)
    {
        vector<Sensor *> reliableSensors;
        for (Sensor* sensor : database->getSensorList())
        {
            if (sensor->getUser() != NULL)
            {
            if (sensor->getUser()->getReliable())
            {
                // si le capteur appartient à un utilisateur
                // et que l'utilisateur et fiable,
                // alors on ajoute le capteur à la liste
                reliableSensors.push_back(sensor);
            }
            }
            else if (sensor->getReliable())
            {
            // si le capteur n'a pas de propriétaire
            // mais qu'il est fiable,
            // alors on l'ajoute à la liste
            reliableSensors.push_back(sensor);
            }
        }
        return reliableSensors;
    }
    return database->getSensorList();
}
vector<Cleaner *> Service::getCleanerList()
{
    return database->getCleanerList();
}
vector<User *> Service::getUserList()
{
    return database->getUserList();
}
vector<Provider *> Service::getProviderList()
{
    return database->getProviderList();
}

//----- Fin de Méthode

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

Service::Service()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Service>" << endl;
#endif
    database = new Database();
} //----- Fin de Service

Service::~Service()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Service>" << endl;
#endif
    delete database;
} //----- Fin de Service

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
