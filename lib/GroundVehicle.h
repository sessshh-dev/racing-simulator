#ifndef GROUNDE_VEHICLE_H
#define GROUNDE_VEHICLE_H
#include "Vehicle.h"

class GroundVehicle : public Vehicle {
private:
    double moveTime;
    double* restTime;
    int restCount;

public:
    GroundVehicle(std::string n, double s, double mt, double* rt, int rc);
    ~GroundVehicle();

    double getRaceTime(double distanse) const override;

};

#endif