#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <ctime>
#include <exception>

using namespace std;

/* =====================================================
   =============== CUSTOM EXCEPTIONS ===================
   ===================================================== */

class ParkingException : public exception {
protected:
    string message;
public:
    explicit ParkingException(const string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class NoAvailableSlotException : public ParkingException {
public:
    NoAvailableSlotException() : ParkingException("No available parking slot.") {}
};

class InvalidTicketException : public ParkingException {
public:
    InvalidTicketException() : ParkingException("Invalid parking ticket.") {}
};

class ReservationException : public ParkingException {
public:
    ReservationException() : ParkingException("VIP Slot reservation failed.") {}
};

class PaymentException : public ParkingException {
public:
    PaymentException() : ParkingException("Payment processing failed.") {}
};

/* =====================================================
   ================= VEHICLE ===========================
   ===================================================== */

enum class VehicleType { MOTORCYCLE, CAR, EV };

class Vehicle {
protected:
    string plate;
    string owner;
    time_t arrivalTime;
    VehicleType type;

public:
    Vehicle(string p, string o, VehicleType t)
        : plate(p), owner(o), type(t) {}

    virtual ~Vehicle() = default;

    void setArrivalTime(time_t t) {
        arrivalTime = t;
    }

    time_t getArrivalTime() const {
        return arrivalTime;
    }

    VehicleType getType() const {
        return type;
    }

    string getPlate() const {
        return plate;
    }

    /* Polymorphism (pure virtual) */
    virtual double calculateRate(int durationHours) const = 0;

    /* Overloading */
    double calculateRate(time_t start, time_t end) const {
        int hours = static_cast<int>(difftime(end, start) / 3600);
        if (hours < 1) hours = 1;
        return calculateRate(hours);
    }
};

/* ================= VEHICLE DERIVED ================= */

class Motorcycle : public Vehicle {
public:
    Motorcycle(string p, string o)
        : Vehicle(p, o, VehicleType::MOTORCYCLE) {}

    double calculateRate(int h) const override {
        double total = 2000 * h;
        if (h > 24) total *= 0.9;
        return total;
    }
};

class Car : public Vehicle {
public:
    Car(string p, string o)
        : Vehicle(p, o, VehicleType::CAR) {}

    double calculateRate(int h) const override {
        double total = 5000 * h;
        if (h > 24) total *= 0.9;
        return total;
    }
};

class EV : public Vehicle {
    bool chargingRequired;
public:
    EV(string p, string o, bool charge)
        : Vehicle(p, o, VehicleType::EV),
          chargingRequired(charge) {}

    double calculateRate(int h) const override {
        double total = 4000 * h;
        if (chargingRequired) total += 3000;
        if (h > 24) total *= 0.9;
        return total;
    }
};

/* =====================================================
   ================= PARKING SLOT ======================
   ===================================================== */

class ParkingSlot {
protected:
    string id;
    int level;
    bool occupied;

public:
    ParkingSlot(string i, int lvl)
        : id(i), level(lvl), occupied(false) {}

    virtual ~ParkingSlot() = default;

    bool isOccupied() const {
        return occupied;
    }

    void setOccupied(bool status) {
        occupied = status;
    }

    virtual bool canPark(const Vehicle& v) const = 0;
};

class RegularSlot : public ParkingSlot {
public:
    RegularSlot(string id, int lvl)
        : ParkingSlot(id, lvl) {}

    bool canPark(const Vehicle& v) const override {
        return v.getType() != VehicleType::EV;
    }
};

class EVSlot : public ParkingSlot {
public:
    EVSlot(string id, int lvl)
        : ParkingSlot(id, lvl) {}

    bool canPark(const Vehicle& v) const override {
        return v.getType() == VehicleType::EV;
    }
};

class VIPSlot : public ParkingSlot {
    bool reserved;
public:
    VIPSlot(string id, int lvl)
        : ParkingSlot(id, lvl), reserved(false) {}

    bool canPark(const Vehicle&) const override {
        return !reserved;
    }

    void reserve() {
        if (reserved)
            throw ReservationException();
        reserved = true;
    }
};

/* =====================================================
   ================= PARKING FLOOR =====================
   ===================================================== */

class ParkingFloor {
    int level;
    vector<unique_ptr<ParkingSlot>> slots;

public:
    ParkingFloor(int lvl) : level(lvl) {}

    void addSlot(unique_ptr<ParkingSlot> slot) {
        slots.push_back(move(slot));
    }

    ParkingSlot* findAvailableSlot(const Vehicle& v) {
        for (auto& s : slots) {
            if (!s->isOccupied() && s->canPark(v)) {
                return s.get();
            }
        }
        return nullptr;
    }
};

/* =====================================================
   ================= PARKING GARAGE ====================
   ===================================================== */

class ParkingGarage {
    vector<ParkingFloor> floors;
    map<int, unique_ptr<Vehicle>> tickets;
    int ticketCounter;

public:
    ParkingGarage() : ticketCounter(1) {}

    void addFloor(ParkingFloor&& f) {
        floors.push_back(move(f));
    }

    int parkVehicle(unique_ptr<Vehicle> v) {
        for (auto& f : floors) {
            ParkingSlot* slot = f.findAvailableSlot(*v);
            if (slot) {
                slot->setOccupied(true);
                v->setArrivalTime(time(nullptr));
                tickets[ticketCounter] = move(v);
                return ticketCounter++;
            }
        }
        throw NoAvailableSlotException();
    }

    double unparkVehicle(int ticketId) {
        if (!tickets.count(ticketId))
            throw InvalidTicketException();

        auto& v = tickets[ticketId];
        time_t now = time(nullptr);

        double cost;
        try {
            cost = v->calculateRate(v->getArrivalTime(), now);
        } catch (...) {
            throw PaymentException(); // rethrow via abstraction
        }

        tickets.erase(ticketId);
        return cost;
    }
};

/* =====================================================
   ====================== MAIN =========================
   ===================================================== */

int main() {
    ParkingGarage garage;

    ParkingFloor floor1(1);
    floor1.addSlot(make_unique<RegularSlot>("R1", 1));
    floor1.addSlot(make_unique<EVSlot>("E1", 1));
    floor1.addSlot(make_unique<VIPSlot>("V1", 1));

    garage.addFloor(move(floor1));

    try {
        cout << "=== PARKING SYSTEM ===\n";

        int ticket = garage.parkVehicle(
            make_unique<Car>("B1234CD", "Sir Radenn")
        );

        cout << "Vehicle parked successfully.\n";
        cout << "Ticket ID: " << ticket << endl;

        cout << "\n--- Simulating Unpark ---\n";
        double cost = garage.unparkVehicle(ticket);

        cout << "Total payment: Rp " << cost << endl;
    }
    catch (const ParkingException& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
