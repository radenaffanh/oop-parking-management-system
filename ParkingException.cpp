#include "ParkingException.h"

ParkingException::ParkingException(const std::string& m) : message(m) {}

const char* ParkingException::what() const noexcept {
    return message.c_str();
}

NoAvailableSlotException::NoAvailableSlotException()
    : ParkingException("No available parking slot!") {}

InvalidTicketException::InvalidTicketException()
    : ParkingException("Invalid parking ticket!") {}

ReservationException::ReservationException()
    : ParkingException("VIP slot is not available!") {}

PaymentException::PaymentException()
    : ParkingException("Payment processing error!") {}
