#ifndef COMMS_H
#define COMMS_H

#include <cstdint>
#include <RF24.h>

typedef union {
    uint16_t word;

    struct {
        uint8_t player_id :8;   /* MSByte is the player's ID */
        
        uint8_t kick :1;
        uint8_t up :1;
        uint8_t down: 1;
        uint8_t left :1;
        uint8_t right :1;
        /* remaining 3 bits unused... */
    }
} Packet;

class Comms {
public:
    /**
     * Write a data packet to the SPI.
     *
     * @param Packet
     */
    void write(Packet);

    /**
     * Read from the SPI.
     *
     * @return A data packet with the relevant bits set.
     */
    Packet read();

private:
    /**
     * 8 bit buffer.
     */
    uint8_t buffer;

    /**
     * Private constructor.
     */
    Comms();
};

Comms getInstance();

#endif
