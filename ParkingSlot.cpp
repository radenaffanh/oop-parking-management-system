#include "ParkingSlot.h"

ParkingSlot::ParkingSlot(std::string i, int lvl)
    : id(i), level(lvl), occupied(false) {}

bool ParkingSlot::isOccupied() const {
    return occupied;
}

void ParkingSlot::setOccupied(bool status) {
    occupied = status;
}

std::string ParkingSlot::getId() const {
    return id;
}

RegularSlot::RegularSlot(std::string id, int lvl)
    : ParkingSlot(id, lvl) {}

bool RegularSlot::canPark(const Vehicle& v) const {
    return v.getType() != VehicleType::EV;
}

EVSlot::EVSlot(std::string id, int lvl)
    : ParkingSlot(id, lvl) {}

bool EVSlot::canPark(const Vehicle& v) const {
    return v.getType() == VehicleType::EV;
}

VIPSlot::VIPSlot(std::string id, int lvl)
    : ParkingSlot(id, lvl), reserved(false) {}

bool VIPSlot::canPark(const Vehicle&) const {
    return !reserved;
}

bool VIPSlot::isReserved() const {
    return reserved;
}

void VIPSlot::reserve() {
    reserved = true;
}
