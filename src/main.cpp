#include <iostream>
#include <string>
#include "Service.h"
using namespace std;

// Dashboard company
const int C_AIR_CLEANERS = 1;
const int C_AIR_QUALITY_IMPROVEMENT = 2;
const int C_DISCONNECT = 3;

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
const int G_AIR_CLEANERS = 4;
const int G_AIR_CLEANER = 5;
const int G_DISCONNECT = 6;

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
        string id = "";
        while (!service.isUserIdValid(id))
        {
            cout << "Quel est votre identifiant ?" << endl;
            cin >> id;
        }

        cout << "Connecté en tant que citoyen." << endl;
        while (choice != P_DISCONNECT)
        {
            cout << P_AIR_COIN << ") Voir mes points" << endl;
            cout << P_SENSORS << ") Voir mes capteurs" << endl;
            cout << P_SENSOR << ") Selectionner un capteur" << endl;
            cout << P_MEASURES << ") Voir mes mesures" << endl;
            cout << P_STATUS << ") Voir mon statut" << endl;
            cout << P_DISCONNECT << ") Me déconnecter" << endl;

            cin >> choice;
            switch (choice)
            {
            case P_AIR_COIN:
                cout << "Vous avez " << service.getUserPoints(id) << " AirCoins" << endl;
                break;
            case P_SENSORS:
            {
                std::vector<Sensor *> *sensors = service.getUserSensors(id);

                cout << "Vos capteurs sont :" << endl;
                for (Sensor *s : *sensors)
                {
                    cout << s->getId() << endl;
                }
                break;
            }
            case P_SENSOR:
            {
                string sensorId;
                cout << "Veuillez saisir l'id du sensor à sélectionner" << endl;
                bool found = false;
                cin >> sensorId;

                std::vector<Sensor *> *sensors = service.getUserSensors(id);
                for (Sensor *s : *sensors)
                {
                    if (s->getId().compare(sensorId))
                    {
                        cout << s;
                        found = true;
                        break;
                    }
                }

                if (!found)
                {
                    cout << "L'id du capteur spécifié n'existe pas.";
                }
                break;
            }
            case P_STATUS:
                break;
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
        while (!service.isProviderIdValid(id))
        {
            cout << "Quel est votre identifiant ?" << endl;
            cin >> id;
        }
        cout << "Connecté en tant qu'entreprise." << endl;
        while (choice != C_DISCONNECT)
        {
            cout << C_AIR_CLEANERS << ") Voir la liste d'Air Cleaner" << endl;
            cout << C_AIR_QUALITY_IMPROVEMENT << ") Voir l'amélioration de la qualité de l'air" << endl;
            cout << C_DISCONNECT << ") Me déconnecter" << endl;
            cin >> choice;
            switch (choice)
            {
            case C_AIR_CLEANERS:
                break;
            case C_AIR_QUALITY_IMPROVEMENT:
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
        cout << "Connecté en tant que membre du govuernement." << endl;
        while (choice != P_DISCONNECT)
        {
            cin >> choice;
            switch (choice)
            {
            case G_MEAN_POINT_TIME_PERIOD:
                break;
            case G_SIMILARITY:
                break;
            case G_SENSORS:
                break;
            case G_AIR_CLEANERS:
                break;
            case G_AIR_CLEANER:
                break;
            case G_DISCONNECT:
                // EMPTY CASE
                break;
            }
        }
        cout << "Déconnexion ..." << endl;
        break;
    }

    cout << "-----------------------------------------------------------------------------------------------" << endl;
    cout << "Merci d'avoir utilisé AirWatcher, Votre compagnon pour une qualité de l'air plus saine !" << endl;
}
