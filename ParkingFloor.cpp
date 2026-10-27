#include "ParkingFloor.h"

ParkingFloor::ParkingFloor(int lvl) : level(lvl) {}

void ParkingFloor::addSlot(std::unique_ptr<ParkingSlot> slot) {
    slots.push_back(std::move(slot));
}

ParkingSlot* ParkingFloor::findAvailableSlot(const Vehicle& v) {
    for (auto& s : slots) {
        if (!s->isOccupied() && s->canPark(v)) {
            return s.get();
        }
    }
    return nullptr;
}
