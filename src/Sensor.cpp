/*************************************************************************
                           Sensor  -  description
                             -------------------
    début                : $SENSOR$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Sensor> (fichier Sensor.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <iomanip>

//------------------------------------------------------ Include personnel
#include "Sensor.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC
void Sensor::setId(string id)
{
  this->id = id;
}

void Sensor::setReliable(bool reliable)
{
  this->reliable = reliable;
}

void Sensor::setCoords(double x, double y)
{
  this->coords = make_pair(x, y);
}

void Sensor::addMeasure(Measure *measure)
{
  this->measureList.push_back(measure);
}

string Sensor::getId() const
{
  return this->id;
}

bool Sensor::getReliable() const
{
  return this->reliable;
}

pair<double, double> Sensor::getCoords() const
{
  return this->coords;
}

vector<Measure *> Sensor::getMeasureList() const
{
  return measureList;
}

vector<Measure *> Sensor::getMeasureList()
{
  return measureList;
}

Sensor::Sensor()
{
#ifdef MAP
  cout << "Appel au constructeur de <Sensor>" << endl;
#endif
}

Sensor::Sensor(string id, bool reliable, double x, double y)
{
#ifdef MAP
  cout << "Appel au constructeur de <Sensor>" << endl;
#endif
  this->id = id;
  this->reliable = reliable;
  // pair <double, double> coordonnees=make_pair(x, y);
  this->coords = make_pair(x, y);
}

Sensor::~Sensor()
{
#ifdef MAP
  cout << "Appel au destructeur de <Sensor>" << endl;
#endif
  for (Measure* measure : measureList)
  {
    delete measure;
  }
}

bool Sensor::operator<(const Sensor &s) const
// Algorithme :
//
{
  return (this->id < s.getId());
}
//----------------------------------------------------- Méthodes publiques

//------------------------------------------------- Surcharge d'opérateurs

// Fonction ordinaire
ostream &operator<<(ostream &stream, const Sensor &s)
{
  // ostream désigne la classe flux en sortie
  stream << "Id: ";
  stream << setiosflags(ios::fixed) << setw(10) << left << s.id;
  stream << " | Latitude: ";
  stream << setiosflags(ios::fixed) << setw(6) << left << setprecision(1) << s.coords.first;
  stream << " | Longitude: ";
  stream << setiosflags(ios::fixed) << setw(6) << left << setprecision(1) << s.coords.second;
  stream << " | Nombre de mesures: ";
  stream << setiosflags(ios::fixed) << setw(6) << left << s.measureList.size();

  return stream;
}