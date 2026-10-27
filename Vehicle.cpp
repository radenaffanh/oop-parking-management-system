#include "Vehicle.h"

Vehicle::Vehicle(std::string p, std::string o, VehicleType t)
    : plate(p), owner(o), type(t) {}

void Vehicle::setArrivalTime(std::time_t t) {
    arrivalTime = t;
}

std::time_t Vehicle::getArrivalTime() const {
    return arrivalTime;
}

VehicleType Vehicle::getType() const {
    return type;
}

std::string Vehicle::getPlate() const {
    return plate;
}

double Vehicle::calculateRate(std::time_t start, std::time_t end) const {
    int hours = static_cast<int>(difftime(end, start) / 3600);
    if (hours < 1) hours = 1;
    return calculateRate(hours);
}

// ===== Subclasses =====
Motorcycle::Motorcycle(std::string p, std::string o)
    : Vehicle(p, o, VehicleType::MOTORCYCLE) {}

double Motorcycle::calculateRate(int h) const {
    double total = 2000 * h;
    if (h > 24) total *= 0.9;
    return total;
}

Car::Car(std::string p, std::string o)
    : Vehicle(p, o, VehicleType::CAR) {}

double Car::calculateRate(int h) const {
    double total = 5000 * h;
    if (h > 24) total *= 0.9;
    return total;
}

EV::EV(std::string p, std::string o, bool charge)
    : Vehicle(p, o, VehicleType::EV), chargingRequired(charge) {}

double EV::calculateRate(int h) const {
    double total = 4000 * h;
    if (chargingRequired) total += 3000;
    if (h > 24) total *= 0.9;
    return total;
}
