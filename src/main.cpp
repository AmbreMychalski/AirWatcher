#include <iostream>
#include <string>
#include "Service.h"
#include <chrono>
#include <iomanip>
using namespace std;

// Dashboard company
const int C_AIR_CLEANERS = 1;
const int C_DISCONNECT = 2;

// Dashboard private individual
const int P_AIR_COIN = 1;
const int P_SENSORS = 2;
const int P_SENSOR = 3;
const int P_MEASURES = 4;
const int P_STATUS = 5;
const int P_DISCONNECT = 6;

// Dashboard government agency
const int G_MEAN_POINT_TIME_PERIOD = 1;
const int G_SIMILARITY = 2;
const int G_SENSORS = 3;
const int G_SENSOR = 4;
const int G_AIR_CLEANERS = 5;
const int G_AIR_CLEANER = 6;
const int G_DISCONNECT = 7;

int main()
{
    Service service = Service();

    cout << "-----------------------------------------------------------------------------------------------" << endl;
    cout << "                                   AirWatcher" << endl;
    cout << "-----------------------------------------------------------------------------------------------" << endl;
    // Choix Menu
    int choice = 0;

    cout << "-----------------------------------Choix du Menu-----------------------------------------------" << endl;
    while (choice > 3 || choice < 1)
    {
        cout << "1. Citoyen       2. Entreprise       3. Gouvernement" << endl;
        cin >> choice;
    }
    switch (choice)
    {
    case 1:
    {
        string id;
        cout << "Quel est votre identifiant ?" << endl;
        cin >> id;
        User *user;
        while ((user = service.getUserById(id)) == nullptr)
        {
            cout << "Identifiant incorrect. Quel est votre identifiant ?" << endl;
            cin >> id;
        }

        cout << "Connecté en tant que citoyen." << endl;
        while (choice != P_DISCONNECT)
        {
            cout << endl;
            cout << P_AIR_COIN << ") Voir mes points" << endl;
            cout << P_SENSORS << ") Voir mes capteurs" << endl;
            cout << P_SENSOR << ") Sélectionner un capteur" << endl;
            cout << P_MEASURES << ") Voir mes mesures" << endl;
            cout << P_STATUS << ") Voir mon statut" << endl;
            cout << P_DISCONNECT << ") Me déconnecter" << endl;
            cout << endl;

            cin >> choice;
            switch (choice)
            {
            case P_AIR_COIN:
                cout << "Vous avez " << user->getNbPoints() << " AirCoins" << endl;
                break;
            case P_SENSORS:
            {
                cout << "Vous avez " << user->getSensorList()->size() << " capteur(s) :" << endl;
                for (Sensor *s : *user->getSensorList())
                {
                    cout << s->getId() << endl;
                }
                break;
            }
            case P_SENSOR:
            {
                string sensorId;
                cout << "Veuillez saisir l'id du capteur à sélectionner" << endl;
                bool found = false;
                cin >> sensorId;

                for (Sensor *s : *user->getSensorList())
                {
                    if (s->getId() == sensorId)
                    {
                        cout << *s << endl;
                        found = true;
                        break;
                    }
                }

                if (!found)
                {
                    cout << "Le capteur spécifié n'existe pas.";
                }
                break;
            }
            case P_MEASURES:
                for (Sensor *s : *user->getSensorList())
                {
                    cout << "Capteur " << s->getId() << " :" << endl;
                    for (Measure *m : s->getMeasureList())
                    {
                        cout << *m << endl;
                    }
                    cout << endl;
                }
                break;
            case P_STATUS:
            {
                vector<Sensor *> unreliableSensors = vector<Sensor *>();
                for (Sensor *s : *user->getSensorList())
                {
                    if (!s->getReliable())
                    {
                        unreliableSensors.push_back(s);
                    }
                }

                if (unreliableSensors.empty())
                {
                    cout << "Tous vos capteurs sont valides.";
                }
                else
                {
                    if (unreliableSensors.size() == 1)
                    {
                        cout << "1 de vos capteur est invalide :" << endl;
                    }
                    else
                    {
                        cout << unreliableSensors.size() << " de vos capteurs sont invalides :" << endl;
                    }
                    for (Sensor *s : unreliableSensors)
                    {
                        cout << s << endl;
                    }
                }
                break;
            }
            case P_DISCONNECT:
                // EMPTY CASE
                break;
            }
        }
        cout << "Déconnexion ..." << endl;
        break;
    }
    case 2:
    {
        string id = "";
        Provider *provider;
        while ((provider = service.getProviderById(id)) == nullptr)
        {
            cout << "Quel est votre identifiant ?" << endl;
            cin >> id;
        }
        cout << "Connecté en tant qu'entreprise." << endl;
        while (choice != C_DISCONNECT)
        {
            cout << endl;
            cout << C_AIR_CLEANERS << ") Voir la liste d'Air Cleaner(s)" << endl;
            // cout << C_AIR_QUALITY_IMPROVEMENT << ") Voir l'amélioration de la qualité de l'air" << endl;
            cout << C_DISCONNECT << ") Me déconnecter" << endl;
            cout << endl;

            cin >> choice;
            switch (choice)
            {
            case C_AIR_CLEANERS:
                cout << "Vous avez " << provider->getCleanerList()->size() << " Air Cleaner(s) :" << endl;
                for (Cleaner *c : *provider->getCleanerList())
                {
                    cout << *c << endl;
                }
                break;
            case C_DISCONNECT:
                // EMPTY CASE
                break;
            }
        }
        cout << "Déconnexion ..." << endl;
        break;
    }
    case 3:
        cout << "Connecté en tant que membre du gouvernement." << endl;
        while (choice != G_DISCONNECT)
        {
            cout << endl;
            cout << G_MEAN_POINT_TIME_PERIOD << ") Calculer l'indice ATMO Moyen en un point donné sur une période donnée" << endl;
            cout << G_SIMILARITY << ") Calculer le pourcentage de similarité d'un capteur avec ceux qui l'entoure" << endl;
            cout << G_SENSORS << ") Afficher les capteurs" << endl;
            cout << G_SENSOR << ") Afficher les mesures d'un capteur" << endl;
            cout << G_AIR_CLEANERS << ") Afficher les Air Cleaner(s)" << endl;
            cout << G_AIR_CLEANER << ") Afficher un Air Cleaner" << endl;
            cout << G_DISCONNECT << ") Me déconnecter" << endl;
            cout << endl;

            cin >> choice;
            switch (choice)
            {
            case G_MEAN_POINT_TIME_PERIOD:
            {
                Date startDate;
                Date endDate;
                pair<double, double> coords;
                double returnArray[NB_ATTRIBUTES];
                cout << "Calcul de l'index ATMO Moyen." << endl;

                cout << "Veuillez saisir la date de départ (dd/MM/YYYY hh:mm:ss) :" << endl;
                cin >> startDate;

                cout << "Veuillez saisir la date de fin (dd/MM/YYYY hh:mm:ss) :" << endl;
                cin >> startDate;

                cout << "Veuillez saisir la latitude du point d'analyse :" << endl;
                cin >> coords.first;

                cout << "Veuillez saisir la longitude du point d'analyse :" << endl;
                cin >> coords.second;

                auto start = std::chrono::high_resolution_clock::now();
                int atmoIndex = service.computeMeanPointTimePeriod(startDate, endDate, coords, returnArray);
                auto end = std::chrono::high_resolution_clock::now();

                std::chrono::duration<double, std::milli> float_ms = end - start;

                cout << "L'index ATMO moyen est " << atmoIndex << endl;
                cout << "Temps d'exécution de la fonction computeMeanPointTimePeriod : " << float_ms.count() << " milliseconds" << endl;

                break;
            }
            case G_SIMILARITY:
            {
                cout << "Calcul de la similarité." << endl;
                cout << "Veuillez saisir l'identifiant du capteur sur lequel se base le score de similarité :" << endl;

                string sensorId;
                bool found = false;
                cin >> sensorId;

                for (Sensor *s : service.getSensorList())
                {
                    if (s->getId() == sensorId)
                    {
                        cout << "Capteur sélectionné : " << s->getId() << endl;

                        Date startDate;
                        Date endDate;
                        cout << "Veuillez saisir la date de départ (dd/MM/YYYY hh:mm:ss) :" << endl;
                        cin >> startDate;

                        cout << "Veuillez saisir la date de fin (dd/MM/YYYY hh:mm:ss) :" << endl;
                        cin >> startDate;

                        auto start = std::chrono::high_resolution_clock::now();
                        std::vector<std::pair<Sensor *, double>> similarity = service.computeSimilarity(sensorId, service.getSensorList(), startDate, endDate);
                        auto end = std::chrono::high_resolution_clock::now();

                        std::chrono::duration<double, std::milli> float_ms = end - start;

                        cout << "Similarité des capteurs par rapport à " << sensorId << " :" << endl;
                        for (pair<Sensor *, double> elem : similarity)
                        {
                            cout << setiosflags(ios::fixed)
                                 << setw(9)
                                 << left
                                 << elem.first->getId()
                                 << " | "
                                 << setiosflags(ios::fixed)
                                 << setw(3)
                                 << left
                                 << setprecision(2)
                                 << elem.second * 100
                                 << " %"
                                 << endl;
                        }

                        /*
                        double similarityMean = 0;
                        for (pair<Sensor *, double> elem : *similarity)
                        {
                            similarityMean += elem.second;
                        }
                        similarityMean = similarityMean / similarity->size() * 100;

                        cout << "Score de similarité moyen : " << similarityMean << " %" << endl;

                        similarity = service.computeSimilarity(sensorId, *service.filterNeighbours(s->getCoords()), startDate, endDate);
                        similarityMean = 0;
                        for (pair<Sensor *, double> elem : *similarity)
                        {
                            similarityMean += elem.second;
                        }
                        similarityMean = similarityMean / similarity->size() * 100;
                        cout << "Score de similarité moyen pour les capteurs proches : " << similarityMean << " %" << endl;
                        */

                        cout << "Temps d'exécution de la fonction computeSimilarity sur tous les capteurs: " << float_ms.count() << " milliseconds" << endl;

                        found = true;
                        break;
                    }
                }

                if (!found)
                {
                    cout << "Le capteur spécifié n'existe pas.";
                }
                break;
            }
            case G_SENSORS:
                cout << "Liste des capteurs : " << endl;
                for (Sensor *s : service.getSensorList())
                {
                    cout << *s << endl;
                }
                break;
            case G_SENSOR:
            {
                string sensorId;
                cout << "Veuillez saisir l'id du capteur à sélectionner" << endl;
                cin >> sensorId;
                Sensor *sensor = service.getSensorById(sensorId);

                if (sensor == nullptr)
                {
                    cout << "Le capteur spécifié n'existe pas.";
                }
                else
                {
                    cout << sensor << endl;
                    cout << "Mesures du capteur :" << endl;
                    for (Measure *m : sensor->getMeasureList())
                    {
                        cout << *m << endl;
                    }
                }
                break;
            }
            case G_AIR_CLEANERS:
                cout << "Liste des Air Cleaners : " << endl;
                for (Cleaner *c : service.getCleanerList())
                {
                    cout << *c << endl;
                }
                break;
            case G_AIR_CLEANER:
            {

                string cleanerId;
                cout << "Veuillez saisir l'id du Air Cleaner à sélectionner" << endl;
                cin >> cleanerId;
                Cleaner *cleaner = service.getCleanerById(cleanerId);
                if (cleaner == nullptr)
                {
                    cout << "Le capteur spécifié n'existe pas.";
                }
                else
                {
                    cout << *cleaner;
                }
                break;
            }
            case G_DISCONNECT:
                // EMPTY CASE
                break;
            }
        }
        cout << "Déconnexion ..." << endl;
        break;
    }

    cout << endl
         << "-----------------------------------------------------------------------------------------------" << endl
         << endl
         << "Merci d'avoir utilisé AirWatcher,"
         << endl
         << "Votre compagnon pour une qualité de l'air plus saine !"
         << endl
         << endl
         << endl;
}
