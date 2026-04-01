#include "Race.h"
#include <iostream>

Race::Race(double d) : distance(d), count(0), capacity(10) {
    participants = new Vehicle*[capacity];
}

Race::~Race() {
    delete[] participants;
}

bool Race::addVehicle(Vehicle* v) {
    for (int i = 0; i < count; i++) {
        if (participants[i]->getName() == v->getName())
            return false;
    }

    if (count < capacity) {
        participants[count++] = v;
        return true;
    }

    return false;
}

void Race::start() {
    if (count < 2) {
        std::cout << "Нужно минимум 2 участника\n";
        return;
    }

    double* times = new double[count];

    for (int i = 0; i < count; i++) {
        times[i] = participants[i]->getRaceTime(distance);
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (times[j] > times[j + 1]) {
                std::swap(times[j], times[j + 1]);
                std::swap(participants[j], participants[j + 1]);
            }
        }
    }

    std::cout << "\nРезультаты:\n";
    for (int i = 0; i < count; i++) {
        std::cout << participants[i]->getName()
                  << " - " << times[i] << std::endl;
    }

    delete[] times;
}
