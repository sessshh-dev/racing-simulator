#ifndef VEHICLE_H
#define VEHICLE_H
#include <iostream>

enum VehicleType{
    GROUND, AIR
},

class Vehicle {
protected:
    std::string name;
    double speed;
    VehicleType type;

public:
    Vehicle(std::string n, double s, VehicleType t) : name(n), speed(s), type(t)
    {}
    virtual ~Vehicle() = default;

    std::string getName() const { return name; }
    VehicleType getType() const { return type; }
    virtual double getRace(double dictance) const = 0;
};

#endif