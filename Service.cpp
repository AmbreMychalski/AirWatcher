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

//------------------------------------------------------ Include personnel
#include "Service.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

std::map<Sensor, double> Service::computeSimilarity(string sensorId)
{
}

double Service::computeMeanPointTimePeriod(Date date, Date endDate, std::pair<double, double> center, double radius)
{
}
int Service::getUserPoints(string userId)
{
}

std::vector<Sensor> Service::getUserSensors(string idUser)
{
}

vector<Cleaner> Service::getProviderCleaners(string idProvider)
{
}

int Service::computeATMOIndex(double o3, double so2, double no2, double pm10)
{
}

void Service::computeMean(std::vector<Measure> measures, double (&returnArray)[NB_ATTRIBUTES])
{
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
