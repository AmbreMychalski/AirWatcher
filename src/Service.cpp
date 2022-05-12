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
#include "Provider.h"
//------------------------------------------------------ Include personnel
#include "Service.h"

//------------------------------------------------------------- Constantes
const double MIN_LONGITUDE = -2;
const double MAX_LONGITUDE = 6;
const double MIN_LATITUDE = 43.5;
const double MAX_LATITUDE = 48;
const int MAX_NEAREST_SENSORS_NUMBER = 4;
const int MIN_NEAREST_SENSORS_NUMBER = 1;
const int MAX_NEAREST_SENSORS_RADIUS = 2;

const int THRESHOLD_STEP = 10;
const double PM_10[] = {80, 65, 50, 42, 35, 28, 21, 14, 7, 0};
const double NO_2[] = {400, 275, 200, 165, 135, 110, 85, 55, 30, 0};
const double SO_2[] = {500, 400, 300, 250, 200, 160, 120, 80, 40, 0};
const double O_3[] = {240, 210, 180, 150, 130, 105, 80, 55, 30, 0};

//----------------------------------------------------------------- PUBLIC

// Driver function to sort the vector elements
// by second element of pairs
bool sortBySec(const pair<int, int> &a,
               const pair<int, int> &b)
{
    return (a.second > b.second);
}

//----------------------------------------------------- Méthodes publiques

std::map<Sensor, double> *Service::computeSimilarity(string sensorId, std::vector<Sensor> sensorList, Date startDate, Date endDate) const
{
    int i = 0;
    const int LENGTH = database->getSensorList().size();
    while (i < LENGTH && database->getSensorList()[i].getId() != sensorId)
    {
        ++i;
    }
    if (i == LENGTH)
    {
        return NULL;
    }

    const std::vector<Measure> *measureListRef = database->getSensorList()[i].getMeasureList();
    double meanRefTab[NB_ATTRIBUTES];
    double meanTab[NB_ATTRIBUTES];
    computeMean(*measureListRef, meanRefTab);

    std::vector<std::pair<Sensor, double>> distanceList;
    std::map<Sensor, double> *similarityList = new std::map<Sensor, double>;
    double distanceMax = 0;
    for (Sensor sensor : sensorList)
    {
        double distance = 0;
        // Si le capteur est bien distinct du capteur de référence
        if (sensorId != sensor.getId())
        {
            std::vector<Measure> *measureList = filterByPeriod(sensor.getId(), startDate, endDate);

            if (!measureList->empty())
            {
                computeMean(*measureList, meanTab);
                for (int i = 0; i < NB_ATTRIBUTES; ++i)
                {
                    /// Incrémenter la distance totale par la distance (au carré)
                    // entre les valeurs moyenne smesurées par ce capteur et le capteur de
                    // référence, à condition que ces valeurs existent bien
                    if (meanRefTab[i] >= 0 && meanTab[i] >= 0)
                    {
                        distance = distance + pow(meanRefTab[i] - meanTab[i], 2);
                    }
                }
            }
        }
        distanceList.push_back(make_pair(sensor, sqrt(distance)));
        distanceMax = max(distance, distanceMax);
    }

    // Si tous les capteurs ne sont pas exactement identiques
    if (distanceMax != 0)
    {
        // Normaliser les distances entre 0 et 1
        for (pair<Sensor, double> elemDistance : distanceList)
        {
            elemDistance.second < -elemDistance.second / distanceMax;
        }
    }
    for (pair<Sensor, double> elemNormalizedDistance : distanceList)
    {
        double similarity = 1 - elemNormalizedDistance.second;
        similarityList->insert(std::pair<Sensor, double>(elemNormalizedDistance.first, similarity));
    }

    // Using sort() function to sort by 2nd element
    // of pair
    sort(similarityList->begin(), similarityList->end(), sortBySec);
    return similarityList;
}

double Service::computeMeanPointTimePeriod(Date startDate, Date endDate, std::pair<double, double> center, double radius, double (&returnArray)[NB_ATTRIBUTES]) const
{
    std::vector<Sensor> *listSensorNeighbours = filterNeighbours(center);
    double distanceSum = 0;

    // On trouve la distance totale séparant les capteurs voisins du point
    // passé en paramètre
    for (Sensor sensor : *listSensorNeighbours)
    {
        double distance = sqrt(pow(center.first - sensor.getCoords().first, 2) + pow(center.second - sensor.getCoords().second, 2));
        distanceSum += distance;
    }

    // Pour chaque type de mesure de chaque capteur, on fait leur moyenne sur
    // la période de temps, puis on pondère cette moyenne
    // par leur distance au point passé en paramètre
    const int LENGTH = listSensorNeighbours->size();
    for (Sensor sensor : *listSensorNeighbours)
    {
        std::vector<Measure> *measuresList = filterByPeriod(sensor.getId(), startDate, endDate);
        double measuresMean[NB_ATTRIBUTES];
        computeMean(*measuresList, measuresMean);
        double distance = sqrt(pow(center.first - sensor.getCoords().first, 2) + pow(center.second - sensor.getCoords().second, 2));
        double ponderation = (1 - distance / distanceSum) / (LENGTH - 1);

        for (int i = 0; i < NB_ATTRIBUTES; ++i)
        {
            returnArray[i] = returnArray[i] + measuresMean[i] * ponderation;
        }
    }
    return computeATMOIndex(returnArray[0], returnArray[1], returnArray[2], returnArray[3]);
}
int Service::getUserPoints(string userId) const
{
    for (User user : database->getUserList())
    {
        if (user.getId().compare(userId))
        {
            return user.getNbPoints();
        }
    }
}

const std::vector<Sensor *> *Service::getUserSensors(string userId) const
{
    for (User user : database->getUserList())
    {
        if (user.getId().compare(userId))
        {
            return user.getSensorList();
        }
    }
}

const std::vector<Cleaner *> *Service::getProviderCleaners(string providerId) const
{
    for (Provider provider : database->getProviderList())
    {
        if (provider.getId().compare(providerId))
        {
            return provider.getCleanerList();
        }
    }
}

// https://fr.wikipedia.org/wiki/Indice_de_qualit%C3%A9_de_l%27air
int Service::computeATMOIndex(double o3, double so2, double no2, double pm10) const
{
    for (int i = 0; i < THRESHOLD_STEP; ++i)
    {
        if (pm10 >= PM_10[i] || no2 >= NO_2[i] || so2 >= SO_2[i] || o3 >= O_3[i])
        {
            return THRESHOLD_STEP - i;
        }
    }
}

void Service::computeMean(const vector<Measure> measures, double (&returnArray)[NB_ATTRIBUTES]) const
{
    double o3 = 0;
    double so2 = 0;
    double no2 = 0;
    double pm10 = 0;
    const int LENGTH = measures.size();
    for (Measure measure : measures)
    {
        if (measure.getAttribute().getUnit() == "O3")
        {
            ++o3;
        }
        else if (measure.getAttribute().getUnit() == "SO2")
        {
            ++so2;
        }
        else if (measure.getAttribute().getUnit() == "NO2")
        {
            ++no2;
        }
        else if (measure.getAttribute().getUnit() == "PM10")
        {
            ++pm10;
        }
    }
    returnArray[0] = o3 / LENGTH;
    returnArray[1] = so2 / LENGTH;
    returnArray[2] = no2 / LENGTH;
    returnArray[3] = pm10 / LENGTH;
}

vector<Sensor> *Service::filterNeighbours(pair<double, double> coords) const
{
    if (coords.first < MIN_LATITUDE || coords.first > MAX_LATITUDE || coords.second < MIN_LONGITUDE || coords.second > MAX_LONGITUDE)
    {
        return NULL;
    }
    std::vector<Sensor> *sensors = new std::vector<Sensor>;
    int i = 0;
    const int LENGTH = database->getSensorList().size();
    Sensor *sensorAtMinDistance = nullptr;
    double minDistance = 0;

    while (i < LENGTH && sensors->size() < MAX_NEAREST_SENSORS_NUMBER)
    {
        Sensor sensor = (*sensors)[i];
        double dist = sqrt(pow(coords.first - sensor.getCoords().first, 2) + pow(coords.second - sensor.getCoords().second, 2));
        if (dist < MAX_NEAREST_SENSORS_RADIUS)
        {
            sensors->push_back(sensor);
        }
        else if (sensorAtMinDistance == nullptr || dist < minDistance)
        {
            minDistance = dist;
            sensorAtMinDistance = &sensor;
        }
    }

    return sensors;
}

vector<Measure> *Service::filterByPeriod(string sensorId, Date startDate, Date endDate) const
{
    int i = 0;
    const int LENGTH = database->getSensorList().size();
    while (i < LENGTH && database->getSensorList()[i].getId() != sensorId)
    {
        ++i;
    }
    if (i == LENGTH)
    {
        return NULL;
    }
    Sensor sensor = database->getSensorList()[i];
    const vector<Measure> *allMeasures = sensor.getMeasureList();
    std::vector<Measure> *targetMeasures = new std::vector<Measure>;
    for (int i = 0; i < allMeasures->size(); ++i)
    {
        Date date = (*allMeasures)[i].getDate();
        if (startDate <= date && date <= endDate)
        {
            targetMeasures->push_back((*allMeasures)[i]);
        }
    }
    return targetMeasures;
}

//----- Fin de Méthode

//------------------------------------------------- Surcharge d'opérateurs
Service &Service::operator=(const Service &unService)
// Algorithme :
//
{
} //----- Fin de operator =

//-------------------------------------------- Constructeurs - destructeur
Service::Service(const Service &unService)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Service>" << endl;
#endif
} //----- Fin de Service (constructeur de copie)

Service::Service()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Service>" << endl;
#endif
} //----- Fin de Service

Service::~Service()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Service>" << endl;
#endif
} //----- Fin de ~Service

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées