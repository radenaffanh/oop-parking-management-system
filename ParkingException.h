#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

class ParkingException : public std::exception {
protected:
    std::string message;
public:
    explicit ParkingException(const std::string& msg) : message(msg) {}
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

#endif
