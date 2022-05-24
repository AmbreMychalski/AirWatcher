#include <iostream>
#include <string>
#include "Database.h"
#include "Sensor.h"
#include "Service.h"

using namespace std;

int main()
{
    Service s = Service();

    vector<Sensor *> sensorsList = s.getSensorList();
    cout << "sensors : \n";
    for (Sensor *sensors : sensorsList)
    {
        cout << sensors->getId() << " ";
        cout << sensors->getMeasureList().front()->getValue()<<"\n";
    }

    vector<Cleaner *> cleanersList = s.getCleanerList();
    cout << "cleaners : \n";
    for (Cleaner *cleaner : cleanersList)
    {
        cout << cleaner->getId() << "\n";
    }

    vector<Provider *> providersList = s.getProviderList();
    cout << "providers : \n";
    for (Provider *provider : providersList)
    {
        cout << provider->getId() << "\n";
    }

    vector<User *> usersList = s.getUserList();
    cout << "users : \n";
    for (User *user : usersList)
    {
        cout << user->getId() << "\n";
    }

    Date d1(2019, 1, 1, 0, 0, 0);
    Date d2(2019, 2, 7, 0, 0, 0);
    vector<Measure *> *listM = s.filterByPeriod("Sensor1", d1, d2);
    for (Measure *m : *listM)
    {
        cout << m->getAttribute().getId() << " :" << m->getValue() << "\n";
    }

    pair<double, double> coords = make_pair(44.4, 3.2);
    vector<Sensor *> *listS = s.filterNeighbours(coords);
    for (Sensor *s : *listS)
    {
        cout << s->getId() << "\n";
    }

    double res[4]{0};
    s.computeMean(*listM, res);
    for (int i = 0; i < 4; i++)
    {
        cout << res[i] << "\n";
    }

    cout << s.computeATMOIndex(res[0], res[1], res[2], res[3]) << "\n";


    vector<std::pair<Sensor *, double>> * listSim= s.computeSimilarity("Sensor0",sensorsList, d1, d2);
    for (pair<Sensor *, double> p : *listSim){
        cout<<p.first->getId()<<" "<<p.second<<"\n";
    }
}