#pragma once
#include "Vehicle.h"

class AirVehicle : public Vehicle {
public:
    AirVehicle(const std::string& n, double s);

    double getRaceTime(double distance) const override;
};