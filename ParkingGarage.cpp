#include "ParkingGarage.h"
#include <ctime>

ParkingGarage::ParkingGarage() : ticketCounter(1) {}

void ParkingGarage::addFloor(const ParkingFloor& f) {
    floors.push_back(f);
}

int ParkingGarage::parkVehicle(std::unique_ptr<Vehicle> v) {
    for (auto& f : floors) {
        ParkingSlot* slot = f.findAvailableSlot(*v);
        if (slot) {
            slot->setOccupied(true);
            v->setArrivalTime(std::time(nullptr));
            tickets[ticketCounter] = std::move(v);
            return ticketCounter++;
        }
    }
    throw NoAvailableSlotException();
}

double ParkingGarage::unparkVehicle(int ticketId) {
    if (!tickets.count(ticketId))
        throw InvalidTicketException();

    auto& v = tickets[ticketId];
    std::time_t now = std::time(nullptr);
    double cost = v->calculateRate(v->getArrivalTime(), now);
    tickets.erase(ticketId);
    return cost;
}

void ParkingGarage::reserveVIP() {
    throw ReservationException();
}
