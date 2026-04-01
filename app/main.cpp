#include <iostream>
#include <string>
#include "GroundVehicle.h"
#include "AirVehicle.h"
#include "Race.h"

Vehicle* allVehicles[] = {
    new GroundVehicle("Верблюд", 10, 30, new double[2]{5, 8}, 2),
    new GroundVehicle("Верблюд-быстроход", 40, 10, new double[3]{5, 6.5, 8}, 3),
    new GroundVehicle("Кентавр", 15, 8, new double[1]{2}, 1),
    new GroundVehicle("Ботинки-вездеходы", 6, 60, new double[2]{10, 5}, 2),
    new AirVehicle("Ковёр-самолёт", 10),
    new AirVehicle("Орёл", 8),
    new AirVehicle("Метла", 20)
};

const int VEHICLE_COUNT = 7;

bool isRegistered(Vehicle** registered, int regCount, const std::string& name) {
    for (int i = 0; i < regCount; i++) {
        if (registered[i]->getName() == name) {
            return true;
        }
    }
    return false;
}

void printRegistered(Vehicle** registered, int regCount) {
    if (regCount == 0) {
        std::cout << "отсутствуют";
    } else {
        for (int i = 0; i < regCount; i++) {
            if (i > 0) std::cout << ", ";
            std::cout << registered[i]->getName();
        }
    }
}

int getFilteredCount(int raceType) {
    int count = 0;
    for (int i = 0; i < VEHICLE_COUNT; i++) {
        if (raceType == 1 && allVehicles[i]->getType() == GROUND) count++;
        else if (raceType == 2 && allVehicles[i]->getType() == AIR) count++;
        else if (raceType == 3) count++;
    }
    return count;
}

void printFilteredMenu(int raceType) {
    int number = 1;
    for (int i = 0; i < VEHICLE_COUNT; i++) {
        Vehicle* v = allVehicles[i];
        bool show = false;
        
        if (raceType == 1 && v->getType() == GROUND) show = true;
        else if (raceType == 2 && v->getType() == AIR) show = true;
        else if (raceType == 3) show = true;
        
        if (show) {
            std::cout << number << ". " << v->getName() << "\n";
            number++;
        }
    }
}

Vehicle* getVehicleByFilteredIndex(int raceType, int menuIndex) {
    int current = 1;
    for (int i = 0; i < VEHICLE_COUNT; i++) {
        Vehicle* v = allVehicles[i];
        bool show = false;
        
        if (raceType == 1 && v->getType() == GROUND) show = true;
        else if (raceType == 2 && v->getType() == AIR) show = true;
        else if (raceType == 3) show = true;
        
        if (show) {
            if (current == menuIndex) {
                return v;
            }
            current++;
        }
    }
    return nullptr;
}

int main() {
    while (true) {
        int type;
        std::cout << "Добро пожаловать в гоночный симулятор!\n"
                  << "1. Гонка для наземного транспорта\n"
                  << "2. Гонка для воздушного транспорта\n"
                  << "3. Гонка для наземного и воздушного транспорта\n"
                  << "Выберите тип гонки: ";
        std::cin >> type;

        double distance;
        std::cout << "Укажите длину дистанции (должна быть положительна): ";
        std::cin >> distance;

        Race race(distance);
        
        Vehicle** registered = new Vehicle*[VEHICLE_COUNT];
        int regCount = 0;

        bool raceStarted = false;
        
        while (!raceStarted) {
            std::cout << "\nДолжно быть зарегистрировано хотя бы 2 транспортных средства\n";
            std::cout << "1. Зарегистрировать транспорт\n";
            std::cout << "2. Начать гонку\n";
            std::cout << "Выберите действие: ";

            int action;
            std::cin >> action;

            if (action == 1) {
                bool backToMenu = false;
                while (!backToMenu) {
                    std::string typeStr;
                    if (type == 1) typeStr = "наземного транспорта";
                    else if (type == 2) typeStr = "воздушного транспорта";
                    else typeStr = "наземного и воздушного транспорта";

                    std::cout << "\nГонка для " << typeStr << ". Расстояние: " << distance << "\n";
                    std::cout << "Зарегистрированные транспортные средства: ";
                    printRegistered(registered, regCount);
                    std::cout << "\n";

                    printFilteredMenu(type);
                    
                    int filteredCount = getFilteredCount(type);
                    std::cout << filteredCount + 1 << ". Закончить регистрацию\n";
                    std::cout << "Выберите транспорт или 0 для окончания процесса регистрации: ";

                    int choice;
                    std::cin >> choice;

                    if (choice == 0 || choice == filteredCount + 1) {
                        backToMenu = true;
                        break;
                    }

                    if (choice < 1 || choice > filteredCount) {
                        std::cout << "Неверный выбор\n";
                        continue;
                    }

                    Vehicle* v = getVehicleByFilteredIndex(type, choice);

                    if (v == nullptr) {
                        std::cout << "Неверный выбор\n";
                        continue;
                    }

                    if (isRegistered(registered, regCount, v->getName())) {
                        std::cout << v->getName() << " уже зарегистрирован!\n";
                    } else {
                        if (race.addVehicle(v)) {
                            registered[regCount++] = v;
                            std::cout << v->getName() << " успешно зарегистрирован!\n";
                        } else {
                            std::cout << "Не удалось зарегистрировать\n";
                        }
                    }
                }
            } 
            else if (action == 2) {
                if (regCount >= 2) {
                    raceStarted = true;
                } else {
                    std::cout << "Должно быть зарегистрировано хотя бы 2 транспортных средства\n";
                }
            }
        }

        race.start();

        delete[] registered;

        std::cout << "\n1. Провести ещё одну гонку\n";
        std::cout << "2. Выйти\n";
        std::cout << "Выберите действие: ";
        int choice;
        std::cin >> choice;
        if (choice == 2) break;
    }

    for (int i = 0; i < VEHICLE_COUNT; i++) {
        delete allVehicles[i];
    }

    return EXIT_SUCCESS;
}