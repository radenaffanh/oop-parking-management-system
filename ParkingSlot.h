#ifndef PARKINGSLOT_H
#define PARKINGSLOT_H

#include "Vehicle.h"

class ParkingSlot {
protected:
    std::string id;
    int level;
    bool occupied;

public:
    ParkingSlot(std::string id, int lvl);
    virtual ~ParkingSlot() = default;

    bool isOccupied() const;
    void setOccupied(bool status);
    std::string getId() const;

    virtual bool canPark(const Vehicle& v) const = 0;
};

class RegularSlot : public ParkingSlot {
public:
    RegularSlot(std::string id, int lvl);
    bool canPark(const Vehicle& v) const override;
};

class EVSlot : public ParkingSlot {
public:
    EVSlot(std::string id, int lvl);
    bool canPark(const Vehicle& v) const override;
};

class VIPSlot : public ParkingSlot {
    bool reserved;
public:
    VIPSlot(std::string id, int lvl);
    bool canPark(const Vehicle& v) const override;
    bool isReserved() const;
    void reserve();
};

#endif
