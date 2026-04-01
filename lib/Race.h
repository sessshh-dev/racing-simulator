#ifndef RACE_H
#define RACE_H
#include "Vehicle.h"

class Race{
private:
    double distance;
    Vehicle** participants;
    int count;
    int capacity;

public: 
    Race(double d);
    ~Race();
    bool addVehicle(Vehicle* v);
    void start();
};


#endif