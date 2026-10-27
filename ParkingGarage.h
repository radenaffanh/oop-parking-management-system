#ifndef PARKINGGARAGE_H
#define PARKINGGARAGE_H

#include <map>
#include <memory>
#include "ParkingFloor.h"
#include "ParkingException.h"

class ParkingGarage {
    std::vector<ParkingFloor> floors;
    std::map<int, std::unique_ptr<Vehicle>> tickets;
    int ticketCounter;

public:
    ParkingGarage();
    void addFloor(const ParkingFloor& f);

    int parkVehicle(std::unique_ptr<Vehicle> v);
    double unparkVehicle(int ticketId);
    void reserveVIP();
};

#endif
