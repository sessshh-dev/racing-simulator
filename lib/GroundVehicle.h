#ifndef GROUNDE_VEHICLE_H
#define GROUNDE_VEHICLE_H
#include "Vehicle.h"

class GroundVehicle : public Vehicle {
private:
    double moveTime;
    double* restTimes;
    int restCount;

public:
    GroundVehicle(const std::string& n, double s, double mt, double* rt, int rc);
    ~GroundVehicle();

    double getRaceTime(double distance) const override;

};

#endif