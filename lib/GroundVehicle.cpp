#include "GroundVehicle.h"

GroundVehicle::GroundVehicle(std::string n, double s, double mt, double* rt, int rc)
    : Vehicle(n, s, GROUND), moveTime(mt), restCount(rc)
{
    restTimes = new double[restCount];
    for (int i = 0; i < restCount; i++){
        restTimes[i] = rt[i];
    }
}

GroundVehicle::~GroundVehicle() {
    delete[] restTimes;
}

double GroundVehicle::getRaceTime(double distance) const {
    double time{};
    double traveled{};
    int restIndex{};

    while (traveled < distance) {
        double canTravel = speed * moveTime;

        if (traveled + canTravel >= distance) {
            time += (distance - traveled) / speed;
            break;
        }

        time += moveTime;
        traveled += canTravel;

        if (restIndex < restCount){
            time += restTimes[restIndex];
        }
        else{
            time += restTimes[restCount - 1];
        }
        restIndex++;
    }

    return time;
}
