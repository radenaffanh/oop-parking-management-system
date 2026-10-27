#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include <ctime>

enum class VehicleType { MOTORCYCLE, CAR, EV };

class Vehicle {
protected:
    std::string plate;
    std::string owner;
    std::time_t arrivalTime;
    VehicleType type;

public:
    Vehicle(std::string p, std::string o, VehicleType t);
    virtual ~Vehicle() = default;

    void setArrivalTime(std::time_t t);
    std::time_t getArrivalTime() const;
    VehicleType getType() const;
    std::string getPlate() const;

    virtual double calculateRate(int durationHours) const = 0;
    double calculateRate(std::time_t start, std::time_t end) const;
};

class Motorcycle : public Vehicle {
public:
    Motorcycle(std::string p, std::string o);
    double calculateRate(int durationHours) const override;
};

class Car : public Vehicle {
public:
    Car(std::string p, std::string o);
    double calculateRate(int durationHours) const override;
};

class EV : public Vehicle {
    bool chargingRequired;
public:
    EV(std::string p, std::string o, bool charge);
    double calculateRate(int durationHours) const override;
};

#endif
