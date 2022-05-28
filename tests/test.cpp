#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/Service.h"
#include "../src/Sensor.h"
#include "../src/Measure.h"
#include "../src/Date.h"
using namespace std;

Service service;
vector<Sensor *> sensorsList;

TEST_CASE( "getSensorById", "[service]" ) {
    SECTION( "with correct id" ) {
        sensorsList.push_back(service.getSensorById("Sensor1"));
        REQUIRE( sensorsList.back()->getId() == "Sensor1" );
        sensorsList.push_back(service.getSensorById("Sensor2"));
        REQUIRE( sensorsList.back()->getId() == "Sensor2" );
        sensorsList.push_back(service.getSensorById("Sensor3"));
        REQUIRE( sensorsList.back()->getId() == "Sensor3" );
        sensorsList.push_back(service.getSensorById("Sensor4"));
        REQUIRE( sensorsList.back()->getId() == "Sensor4" );
    }
    SECTION( "with wrong id" ) {
        Sensor * sensor = service.getSensorById("Sensor1_");

        REQUIRE( sensor == NULL );
    }
}

// vector<Measure *> filterByPeriod(std::string sensorId, Date startdate, Date endDate);
TEST_CASE( "filterByPeriod", "[service]" ) {
    SECTION( "wrong id" ) {
        REQUIRE( service.filterByPeriod("Sensor1_", Date(), Date()).size() == 0 );
    }
    SECTION( "correct id, but no measure during the period" ) {
        REQUIRE( service.filterByPeriod("Sensor1", Date(), Date()).size() == 0 );
    }
    SECTION( "correct id and one measure taken at the startDate" ) {
        REQUIRE( service.filterByPeriod("Sensor1", Date(2020,01,01,12,00,00), Date(2020,01,01,12,01,00)).front()->getValue() == 50 );
    }
    SECTION( "correct id and one measure taken at the endDate" ) {
        REQUIRE( service.filterByPeriod("Sensor1", Date(2020,01,01,11,59,00), Date(2020,01,01,12,00,00)).front()->getValue() == 50 );
    }
}

// void computeMean(vector<Measure *> measures, double (&returnArray)[NB_ATTRIBUTES]);
TEST_CASE( "computeMean", "[service]" ) {
    double means[4];
    vector<Measure*> measures;
    SECTION( "empty list of measures" ) {
        measures = service.filterByPeriod("Sensor1", Date(), Date());
        service.computeMean(measures, means);
        THEN( "measure O3" ) {
            REQUIRE( means[0] == -1.0 );
        }
        THEN( "measure So2" ) {
            REQUIRE( means[1] == -1.0 );
        }
        THEN( "measure No2" ) {
            REQUIRE( means[2] == -1.0 );
        }
        THEN( "measure PM10" ) {
            REQUIRE( means[3] == -1.0 );
        }
    }
    SECTION( "list with only one measure of No2" ) {
        measures = service.filterByPeriod("Sensor2", Date(2020,01,01,12,00,00), Date(2020,01,01,12,01,00));
        service.computeMean(measures, means);
        THEN( "measure O3" ) {
            REQUIRE( means[0] == -1.0 );
        }
        THEN( "measure So2" ) {
            REQUIRE( means[1] == -1.0 );
        }
        THEN( "measure No2" ) {
            REQUIRE( means[2] == 100.0 );
        }
        THEN( "measure PM10" ) {
            REQUIRE( means[3] == -1.0 );
        }
    }
    SECTION( "list with many measures" ) {
        measures = service.filterByPeriod("Sensor1", Date(2020,01,01,12,00,00), Date(2020,01,01,12,01,00));
        vector<Measure*> measures2 = service.filterByPeriod("Sensor2", Date(2020,01,01,11,30,00), Date(2020,01,01,11,31,00));
        measures.insert(measures.end(), measures2.begin(), measures2.end());
        service.computeMean(measures, means);
        THEN( "measure O3" ) {
            REQUIRE( means[0] == 50.0 );
        }
        THEN( "measure So2" ) {
            REQUIRE( means[1] == 40.0 );
        }
        THEN( "measure No2" ) {
            REQUIRE( means[2] == 65.0 );
        }
        THEN( "measure PM10" ) {
            REQUIRE( means[3] == 40.0 );
        }
    }
}

// vector<pair<Sensor *, double>> computeSimilarity(string sensorId, std::vector<Sensor *> sensorList, Date startDate, Date endDate)
TEST_CASE( "computeSimilarity", "[service]" ) {
    vector<pair<Sensor *, double>> similarity;
    // SECTION( "empty list of sensors" ) {
    //     vector<Sensor *> sensors;
    //     similarity = service.computeSimilarity("Sensor1",sensors,Date(),Date());
    // }
    SECTION( "list with only one sensor that can be compared with reference sensor" ) {
        vector<Sensor *> sensors;
        sensors.push_back(service.getSensorById("Sensor2"));
        similarity = service.computeSimilarity("Sensor1",sensors,Date(2020,01,01,11,00,00),Date(2020,01,01,15,00,00));
        REQUIRE( similarity.size() == 1 );
        THEN( "first sensor" ) {
            REQUIRE( (similarity.at(0)).first->getId() == "Sensor2" );
        }
        THEN( "first similarity" ) {
            REQUIRE( (similarity.at(0)).second == 0.0 );
        }
    }
    SECTION( "list with only one sensor that can't be compared to reference sensor" ) {
        vector<Sensor *> sensors;
        sensors.push_back(service.getSensorById("Sensor3"));
        similarity = service.computeSimilarity("Sensor1",sensors,Date(2020,01,01,11,00,00),Date(2020,01,01,15,00,00));
        REQUIRE( similarity.size() == 1 );
        THEN( "first sensor" ) {
            REQUIRE( (similarity.at(0)).first->getId() == "Sensor3" );
        }
        THEN( "first similarity" ) {
            REQUIRE( (similarity.at(0)).second == 1.0 );
        }
    }
    SECTION( "list with two sensors : one that can be compared to reference sensor, and one that can't" ) {
        vector<Sensor *> sensors;
        sensors.push_back(service.getSensorById("Sensor2"));
        sensors.push_back(service.getSensorById("Sensor3"));
        similarity = service.computeSimilarity("Sensor1",sensors,Date(2020,01,01,11,00,00),Date(2020,01,01,15,00,00));
        REQUIRE( similarity.size() == 2 );
        THEN( "first sensor" ) {
            REQUIRE( (similarity.at(0)).first->getId() == "Sensor3" );
        }
        THEN( "first similarity" ) {
            REQUIRE( (similarity.at(0)).second == 1.0 );
        }
        THEN( "second sensor" ) {
            REQUIRE( (similarity.at(1)).first->getId() == "Sensor2" );
        }
        THEN( "second similarity" ) {
            REQUIRE( (similarity.at(1)).second == 0.0 );
        }
    }
    SECTION( "list with only one sensor that has identical measures" ) {
        vector<Sensor *> sensors;
        sensors.push_back(service.getSensorById("Sensor4"));
        similarity = service.computeSimilarity("Sensor1",sensors,Date(2020,01,01,12,45,00),Date(2020,01,01,12,45,00));
        REQUIRE( similarity.size() == 1 );
        THEN( "first sensor" ) {
            REQUIRE( (similarity.at(0)).first->getId() == "Sensor4" );
        }
        THEN( "first similarity" ) {
            REQUIRE( (similarity.at(0)).second == 1.0 );
        }
    }
    SECTION( "list with two sensors, comparable to reference sensor but distinct from each other" ) {
        vector<Sensor *> sensors;
        sensors.push_back(service.getSensorById("Sensor2"));
        sensors.push_back(service.getSensorById("Sensor4"));
        similarity = service.computeSimilarity("Sensor1",sensors,Date(2020,01,01,11,30,00),Date(2020,01,01,12,00,00));
        REQUIRE( similarity.size() == 2 );
        THEN( "first sensor" ) {
            REQUIRE( (similarity.at(0)).first->getId() == "Sensor2" );
        }
        THEN( "first similarity" ) {
            REQUIRE( (similarity.at(0)).second == 0.8 );
        }
        THEN( "second sensor" ) {
            REQUIRE( (similarity.at(1)).first->getId() == "Sensor4" );
        }
        THEN( "second similarity" ) {
            REQUIRE( (similarity.at(1)).second == 0.0 );
        }
    }
    SECTION( "list with three sensors, including the reference sensor itself" ) {
        vector<Sensor *> sensors;
        sensors.push_back(service.getSensorById("Sensor1"));
        sensors.push_back(service.getSensorById("Sensor2"));
        sensors.push_back(service.getSensorById("Sensor4"));
        similarity = service.computeSimilarity("Sensor1",sensors,Date(2020,01,01,11,30,00),Date(2020,01,01,12,00,00));
        REQUIRE( similarity.size() == 2 );
        THEN( "first sensor" ) {
            REQUIRE( (similarity.at(0)).first->getId() == "Sensor2" );
        }
        THEN( "first similarity" ) {
            REQUIRE( (similarity.at(0)).second == 0.8 );
        }
        THEN( "second sensor" ) {
            REQUIRE( (similarity.at(1)).first->getId() == "Sensor4" );
        }
        THEN( "second similarity" ) {
            REQUIRE( (similarity.at(1)).second == 0.0 );
        }
    }
    SECTION( "list with three sensors, none comparable to reference" ) {
        vector<Sensor *> sensors;
        sensors.push_back(service.getSensorById("Sensor2"));
        sensors.push_back(service.getSensorById("Sensor3"));
        sensors.push_back(service.getSensorById("Sensor4"));
        similarity = service.computeSimilarity("Sensor1",sensors,Date(2020,01,02,11,30,00),Date(2020,01,02,12,00,00));
        REQUIRE( similarity.size() == 3 );
        THEN( "first sensor" ) {
            REQUIRE( (similarity.at(0)).first->getId() == "Sensor2" );
        }
        THEN( "first similarity" ) {
            REQUIRE( (similarity.at(0)).second == 1.0 );
        }
        THEN( "second sensor" ) {
            REQUIRE( (similarity.at(1)).first->getId() == "Sensor3" );
        }
        THEN( "second similarity" ) {
            REQUIRE( (similarity.at(1)).second == 1.0 );
        }
        THEN( "third sensor" ) {
            REQUIRE( (similarity.at(2)).first->getId() == "Sensor4" );
        }
        THEN( "third similarity" ) {
            REQUIRE( (similarity.at(2)).second == 1.0 );
        }
    }
}

// int computeATMOIndex(double o3, double so2, double no2, double pm10);
TEST_CASE( "computeATMOIndex", "[service]" ) {
    SECTION( "O3 measure gives the index" ) {
        REQUIRE(service.computeATMOIndex(240.0,0.0,0.0,0.0) == 10 );
    }
    SECTION( "SO2 measure gives the index" ) {
        REQUIRE(service.computeATMOIndex(0.0,500.0,0.0,0.0) == 10 );
    }
    SECTION( "NO2 measure gives the index" ) {
        REQUIRE(service.computeATMOIndex(0.0,0.0,400.0,0.0) == 10 );
    }
    SECTION( "PM10 measure gives the index" ) {
        REQUIRE(service.computeATMOIndex(0.0,0.0,0.0,80.0) == 10 );
    }
    SECTION( "very low measures") {
        REQUIRE(service.computeATMOIndex(0.0,0.0,0.0,0.0) == 1 );
    }
    SECTION( "some invalid measures") {
        REQUIRE(service.computeATMOIndex(-1.0,42.0,-1.0,8.0) == 2 );
    }
    SECTION( "only invalid measures") {
        REQUIRE(service.computeATMOIndex(-1.0,-1.0,-1.0,-1.0) == -1 );
    }
}

// vector<Sensor *> *filterNeighbours(pair<double, double> coords);
TEST_CASE( "filterNeighbours", "[service]" ) {
    vector<Sensor *> neighbours;
    SECTION( "out of range" ) {
        REQUIRE(service.filterNeighbours(make_pair(0.0,0.0)).size() == 0 );
    }
    SECTION( "same coords, 4 neighbours" ) {
        neighbours = service.filterNeighbours(make_pair(44.0,5.0));
        REQUIRE(neighbours.size() == 4 );
        THEN( "first sensor" ){
            REQUIRE(neighbours.at(0)->getId() == "Sensor5" );
        }
        THEN( "second sensor" ){
            REQUIRE(neighbours.at(1)->getId() == "Sensor6" );
        }
        THEN( "third sensor" ){
            REQUIRE(neighbours.at(2)->getId() == "Sensor7" );
        }
        THEN( "fourth sensor" ){
            REQUIRE(neighbours.at(3)->getId() == "Sensor8" );
        }
    }
    SECTION( "far from any sensor, west" ) {
        neighbours = service.filterNeighbours(make_pair(43.5,-2.0));
        REQUIRE(neighbours.size() == 1 );
        THEN( "first sensor" ){
            REQUIRE(neighbours.at(0)->getId() == "Sensor5" );
        }
    }
    SECTION( "some neighbours" ) {
        neighbours = service.filterNeighbours(make_pair(46.5,5.0));
        REQUIRE(neighbours.size() == 3 );
        THEN( "first sensor" ){
            REQUIRE(neighbours.at(0)->getId() == "Sensor2" );
        }
        THEN( "second sensor" ){
            REQUIRE(neighbours.at(1)->getId() == "Sensor1" );
        }
        THEN( "third sensor" ){
            REQUIRE(neighbours.at(2)->getId() == "Sensor3" );
        }
    }
    SECTION( "distinct coords, 4 neighbours" ) {
        neighbours = service.filterNeighbours(make_pair(45.70,4.99));
        REQUIRE(neighbours.size() == 4 );
        THEN( "first sensor" ){
            REQUIRE(neighbours.at(0)->getId() == "Sensor3" );
        }
        THEN( "second sensor" ){
            REQUIRE(neighbours.at(1)->getId() == "Sensor2" );
        }
        THEN( "third sensor" ){
            REQUIRE(neighbours.at(2)->getId() == "Sensor1" );
        }
        THEN( "fourth sensor" ){
            REQUIRE(neighbours.at(3)->getId() == "Sensor4" );
        }
    }
}

// int computeMeanPointTimePeriod(Date startDate, Date endDate, std::pair<double, double> center, double (&returnArray)[NB_ATTRIBUTES]);
TEST_CASE( "computeMeanPointTimePeriod", "[service]" ) {
    int atmo;
    double means[4];
    SECTION( "out of range" ) {
        REQUIRE(service.computeMeanPointTimePeriod(Date(),Date(),make_pair(0.0,0.0),means) == -1 );
        THEN( "measure o3" ){
            REQUIRE(means[0] == -1.0 );
        }
        THEN( "measure so2" ){
            REQUIRE(means[1] == -1.0 );
        }
        THEN( "measure no2" ){
            REQUIRE(means[2] == -1.0 );
        }
        THEN( "measure pm10" ){
            REQUIRE(means[3] == -1.0 );
        }
    }
    SECTION( "no measure found during the period" ) {
        REQUIRE(service.computeMeanPointTimePeriod(Date(),Date(),make_pair(44.0,5.0),means) == -1 );
        THEN( "measure o3" ){
            REQUIRE(means[0] == -1.0 );
        }
        THEN( "measure so2" ){
            REQUIRE(means[1] == -1.0 );
        }
        THEN( "measure no2" ){
            REQUIRE(means[2] == -1.0 );
        }
        THEN( "measure pm10" ){
            REQUIRE(means[3] == -1.0 );
        }
    }
    SECTION( "only one neighbour found" ) {
        REQUIRE(service.computeMeanPointTimePeriod(Date(2010,01,01,12,00,00),Date(2010,01,01,12,00,00),make_pair(48.0,6.0),means) == 4 );
        THEN( "measure o3" ){
            REQUIRE(means[0] == 100.0 );
        }
        THEN( "measure so2" ){
            REQUIRE(means[1] == 100.0 );
        }
        THEN( "measure no2" ){
            REQUIRE(means[2] == 100.0 );
        }
        THEN( "measure pm10" ){
            REQUIRE(means[3] == 10.0 );
        }
    }
    SECTION( "four neighbours around" ) {
        atmo = service.computeMeanPointTimePeriod(Date(2010,01,01,12,00,00),Date(2010,01,01,12,00,00),make_pair(45.77805,4.82793),means);
        THEN( "atmo index" ){
            REQUIRE( atmo == 6 );
        }
        THEN( "measure o3" ){
            REQUIRE(round(means[0]) == round(138.9) );
        }
        THEN( "measure so2" ){
            REQUIRE(round(means[1]) == round(138.9) );
        }
        THEN( "measure no2" ){
            REQUIRE(round(means[2]) == round(138.9) );
        }
        THEN( "measure pm10" ){
            REQUIRE(round(means[3]) == round(23.81) );
        }
        // round(value) because it's not accurate enough
    }
}

/*SCENARIO( "computeATMOIndex2", "[service]" ) {

    GIVEN( "A vector with some items" ) {
        std::vector<int> v( 5 );

        REQUIRE( v.size() == 5 );
        REQUIRE( v.capacity() >= 5 );

        WHEN( "the size is increased" ) {
            v.resize( 10 );

            THEN( "the size and capacity change" ) {
                REQUIRE( v.size() == 10 );
                REQUIRE( v.capacity() >= 10 );
            }
        }
        WHEN( "the size is reduced" ) {
            v.resize( 0 );

            THEN( "the size changes but not capacity" ) {
                REQUIRE( v.size() == 0 );
                REQUIRE( v.capacity() >= 5 );
            }
        }
        WHEN( "more capacity is reserved" ) {
            v.reserve( 10 );

            THEN( "the capacity changes but not the size" ) {
                REQUIRE( v.size() == 5 );
                REQUIRE( v.capacity() >= 10 );
            }
        }
        WHEN( "less capacity is reserved" ) {
            v.reserve( 0 );

            THEN( "neither size nor capacity are changed" ) {
                REQUIRE( v.size() == 8 );
                REQUIRE( v.capacity() >= 5 );
            }
        }
    }
}*/