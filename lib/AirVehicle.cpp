#include "AirVehicle.h"

AirVehicle::AirVehicle(const std::string& n, double s)
    : Vehicle(n, s, AIR) {}

double AirVehicle::getRaceTime(double distance) const {
    
    if (speed == 0){
        return 0;
    }
    double percent = 0;

    if (name == "Ковёр-самолёт") {
        if (distance < 1000) percent = 0;
        else if (distance < 5000) percent = 3;
        else if (distance < 10000) percent = 10;
        else percent = 5;
    }
    else if (name == "Орёл") percent = 6;
    else if (name == "Метла") percent = (int)(distance / 1000);

    double newDistance = distance * (1 - percent / 100.0);
    return newDistance / speed;
}