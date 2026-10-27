#ifndef PARKINGFLOOR_H
#define PARKINGFLOOR_H

#include <vector>
#include <memory>
#include "ParkingSlot.h"

class ParkingFloor {
    int level;
    std::vector<std::unique_ptr<ParkingSlot>> slots;

public:
    ParkingFloor(int lvl);
    void addSlot(std::unique_ptr<ParkingSlot> slot);
    ParkingSlot* findAvailableSlot(const Vehicle& v);
};

#endif
