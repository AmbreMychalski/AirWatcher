/*************************************************************************
                           Database  -  description
                             -------------------
    début                : 10/05/2022
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Xxx> (fichier Xxx.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

//------------------------------------------------------ Include personnel
#include "Database.h"
#include <fstream>

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
vector<Sensor *> Database::getSensorList()
{
  return sensorList;
}
vector<Cleaner *> Database::getCleanerList()
{
  return cleanerList;
}
vector<User *> Database::getUserList()
{
  return userList;
}
vector<Provider *> Database::getProviderList()
{
  return providerList;
}

Cleaner *Database::getCleanerById(string cleanerId)
{
  for (Cleaner *cleaner : cleanerList)
  {
    if (cleaner->getId() == cleanerId)
    {
      return cleaner;
    }
  }
  return nullptr;
}

Sensor *Database::getSensorById(string sensorId)
{
  for (Sensor *sensor : sensorList)
  {
    if (sensor->getId() == sensorId)
    {
      return sensor;
    }
  }
  return nullptr;
}

User *Database::getUserById(string userId)
{
  for (User *user : userList)
  {
    if (user->getId() == userId)
    {
      return user;
    }
  }
  return nullptr;
}

Provider *Database::getProviderById(string providerId)
{
  for (Provider *provider : providerList)
  {
    if (provider->getId() == providerId)
    {
      return provider;
    }
  }
  return nullptr;
}

void Database::initialiseDB(string fattribute, string fmeasure, string fsensor, string fcleaner, string fprovider, string fuser)
{
  initialiseAttribute(fattribute);

  initialiseSensor(fsensor);
  initialiseMeasure(fmeasure);
  initialiseCleaner(fcleaner);
  initialiseProvider(fprovider);
  initialiseUser(fuser);
}

void Database::initialiseAttribute(string fileName)
{
  ifstream stream;
  string temp;
  string id;
  string unit;
  string description;
  Attribute *attribute;
  stream.open(fileName.c_str());

  getline(stream, temp, '\n');
  getline(stream, id, ';');
  while (id.size() != 0)
  {
    getline(stream, unit, ';');
    getline(stream, description, ';');
    attribute = new Attribute(id, unit, description);
    attributeList.push_back(attribute);

    getline(stream, temp, '\n');
    getline(stream, id, ';');
  }
  stream.close();
}

void Database::initialiseMeasure(string fileName)
{
  ifstream stream;
  string temp;
  string value, attId, sensorId;
  string year, month, day, hour, minute, seconde;
  Attribute* att;
  Date* date;
  if (!sensorList.empty())
  {
    Sensor *lastSensor = sensorList.at(0);

    stream.open(fileName.c_str());

    getline(stream, year, '-');
    while (year.size() != 0)
    {

      getline(stream, month, '-');
      getline(stream, day, ' ');
      getline(stream, hour, ':');
      getline(stream, minute, ':');
      getline(stream, seconde, ';');
      date = new Date(stoi(year), stoi(month), stoi(day), stoi(hour), stoi(minute), stoi(seconde));

      getline(stream, sensorId, ';');
      getline(stream, attId, ';');
      for (Attribute* a : attributeList)
      {
        if (a->getId() == attId)
        {
          att = a;
        }
      }
      getline(stream, value, ';');
      if (lastSensor->getId() != sensorId)
      {
        long unsigned int index = 0;
        while (index < sensorList.size() && sensorList.at(index)->getId() != sensorId)
        {
          index++;
        }
        lastSensor = sensorList.at(index);
      }
      lastSensor->addMeasure(new Measure(stod(value), date, att, sensorId));
      getline(stream, temp, '\n');
      getline(stream, year, '-');
    }
    stream.close();
  }
}

void Database::initialiseSensor(string fileName)
{
  ifstream stream;
  string temp;
  string id;
  string lon;
  string lat;
  stream.open(fileName.c_str());

  getline(stream, id, ';');
  while (id.size() != 0)
  {
    getline(stream, lat, ';');
    getline(stream, lon, ';');
    sensorList.push_back(new Sensor(id, true, stod(lat), stod(lon)));
    getline(stream, temp, '\n');
    getline(stream, id, ';');
  }
  stream.close();
}

void Database::initialiseCleaner(string fileName)
{
  ifstream stream;
  string temp;
  string id;
  string lon;
  string lat;
  string year, month, day, hour, minute, seconde;
  Date *start, *end;
  pair<double, double> coords;

  stream.open(fileName.c_str());

  getline(stream, id, ';');

  while (id.size() != 0)
  {
    getline(stream, lat, ';');
    getline(stream, lon, ';');
    coords = make_pair(stod(lat), stod(lon));
    for (int i = 0; i < 2; ++i)
    {
      getline(stream, year, '-');
      getline(stream, month, '-');
      getline(stream, day, ' ');
      getline(stream, hour, ':');
      getline(stream, minute, ':');
      getline(stream, seconde, ';');
      if (i == 0)
      {
        start = new Date(stoi(year), stoi(month), stoi(day), stoi(hour), stoi(minute), stoi(seconde));
      }
      else
      {
        end = new Date(stoi(year), stoi(month), stoi(day), stoi(hour), stoi(minute), stoi(seconde));
      }
    }
    cleanerList.push_back(new Cleaner(id, coords, start, end));
    getline(stream, temp, '\n');
    getline(stream, id, ';');
  }
  stream.close();
}

void Database::initialiseProvider(string fileName)
{
  ifstream stream;
  string temp;
  string id;
  string cleanerId;
  stream.open(fileName.c_str());

  getline(stream, id, ';');
  while (id.size() != 0)
  {
    getline(stream, cleanerId, ';');

    providerList.push_back(new Provider(id));
    for (Cleaner *c : cleanerList)
    {
      if (c->getId() == cleanerId)
      {
        providerList.back()->addCleaner(c);
      }
    }
    getline(stream, temp, '\n');
    getline(stream, id, ';');
  }
  stream.close();
}

void Database::initialiseUser(string fileName)
{
  ifstream stream;
  string temp;
  string id;
  string sensorId;
  User* lastUser = NULL;
  stream.open(fileName.c_str());

  getline(stream, id, ';');
  while (id.size() != 0)
  {
    // si userList vide -> ajoute le User et il devient le lastUser
    // si non vide et lastUser différent du User de la ligne lue -> on parcourt userList jusqu'à le trouver
    //        si pas trouvé -> ajoute le User et il devient le lastUser
    //        si trouvé -> il devient le lastUser
    if (lastUser==NULL)
    {
      lastUser = new User(id);
      userList.push_back(lastUser);
    }
    else if (lastUser->getId() != id)
    {
      long unsigned int index = 0;
      while (index < userList.size() && userList.at(index)->getId() != id)
      {
        ++index;
      }
      if (index == userList.size())
      {
        lastUser = new User(id);
        userList.push_back(lastUser);
      }
      else
      {
        lastUser = userList.at(index);
      }
    }

    getline(stream, sensorId, ';');

    for (Sensor *s : sensorList)
    {
      if (s->getId() == sensorId)
      {
        lastUser->addSensor(s);
        s->setUser(lastUser);
      }
    }
    getline(stream, temp, '\n');
    getline(stream, id, ';');
  }
  stream.close();
}

//-------------------------------------------- Constructeurs - destructeur

Database::Database()
{
#ifdef MAP
  cout << "Appel au constructeur de <Database>" << endl;
#endif
  this->initialiseDB("./datasets/attributes.csv", "./datasets/measurements.csv", "./datasets/sensors.csv", "./datasets/cleaners.csv", "./datasets/providers.csv", "./datasets/users.csv");
}

Database::~Database(){
#ifdef MAP
  cout << "Appel au destructeur de <Database>" << endl;
#endif
  for (User * user : userList)
  {
    delete user;
  }
  for (Provider * provider : providerList)
  {
    delete provider;
  }
  for (Sensor * sensor : sensorList)
  {
    delete sensor;
  }
  for (Attribute * attribute : attributeList)
  {
    delete attribute;
  }
  for (Cleaner * cleaner : cleanerList){
    delete cleaner;
  }
}

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
