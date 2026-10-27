#include <iostream>
#include "ParkingGarage.h"

int main() {
    ParkingGarage garage;

    ParkingFloor f1(1);
    f1.addSlot(std::make_unique<RegularSlot>("R1", 1));
    f1.addSlot(std::make_unique<EVSlot>("E1", 1));
    f1.addSlot(std::make_unique<VIPSlot>("V1", 1));

    garage.addFloor(f1);

    try {
        int ticket = garage.parkVehicle(
            std::make_unique<Car>("B1234CD", "Radenn")
        );
        std::cout << "Ticket ID: " << ticket << std::endl;

        double cost = garage.unparkVehicle(ticket);
        std::cout << "Total Cost: Rp " << cost << std::endl;
    }
    catch (const ParkingException& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}
