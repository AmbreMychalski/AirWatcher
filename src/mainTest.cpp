#include <iostream>
#include <string>
#include "Database.h"
#include "Sensor.h"
#include "Service.h"

using namespace std;

int main () {
    Database *base = new Database();
    Service  s(base);

    vector<Sensor> sensorsList = base->getSensorList();
    cout<<"sensors : \n";
    for(Sensor sensors: sensorsList){
        cout<<sensors.getId()<<"\n";
    }

    vector<Cleaner> cleanersList = base->getCleanerList();
    cout<<"cleaners : \n";
    for(Cleaner cleaner: cleanersList){
        cout<<cleaner.getId()<<"\n";
    }

    vector<Provider> providersList = base->getProviderList();
    cout<<"providers : \n";
    for(Provider provider: providersList){
        cout<<provider.getId()<<"\n";
    }

    vector<User> usersList = base->getUserList();
    cout<<"users : \n";
    for(User user: usersList){
        cout<<user.getId()<<"\n";
    }
    
    Date d1(2019,1,3,0,0,0);
    Date d2(2019,1,7,0,0,0);
    vector<Measure> * listM = s.filterByPeriod("Sensor1",d1,d2);
    for(Measure m: *listM){
        cout<<m.getAttribute().getId()<<" :"<<m.getValue()<<"\n";
    }

    pair<double, double> coords = make_pair(44.4,3.2);
    vector<Sensor> * listS = s.filterNeighbours(coords);
    for(Sensor s: *listS){
        cout<<s.getId()<<"\n";
    }

    double res[4] {0};
    s.computeMean(*listM,res);
    for(int i=0;i<4;i++){
        cout<<res[i]<<"\n";
    }

    cout<<s.computeATMOIndex(res[0], res[1], res[2], res[3])<<"\n";
}