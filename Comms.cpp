#include "Comms.h"

Comms::Comms() {
    // constructor
}

Comms Comms::getInstance() {
    static Comms instance;

    if (!instance) {
        instance = new Comms();
    }

    return instance;
}

void Comms::write(Packet packet) {
    // write to the SPI
}

Packet Comms::read() {
    // read from the buffer
}
