/*
 * FanPacket.hh
 *
 *  Created on: Sep 9, 2015
 *      Author: papes
 */

#ifndef LIB_FANPACKET_HH_
#define LIB_FANPACKET_HH_

#include <bitset>
#include <vector>

namespace gr {
namespace fancontrol {

/**
 * The four possible states for the fan speed
 */
enum FanState {
    FAN_LOW = 0, FAN_MED = 1, FAN_HIGH = 2, FAN_OFF = 3,
};

/**
 * Class to calculate the bits for a particular configuration set.
 */
class FanPacket {
public:
    /**
     * Create a new FanPacket.
     * Sets the preamble and the "always-on" bits in the constructor
     */
    FanPacket();
    ~FanPacket();
public:
    /**
     * Controls which ceiling fan responds to the packet.
     * The actual bits are backwards in the packet from how they're numbered.
     * I.E. switch 1 is the least significant.
     */
    void setDipSwitches(unsigned char switches);

    /**
     * @returns The current dip-switch configuration
     */
    unsigned char getDipSwitches(unsigned char switches) const;

    /**
     * Sets the light level. 0x3F (all ones) is off.
     */
    void setLight(unsigned char light);

    /**
     * @returns The light level
     */
    unsigned char getLight() const;

    /**
     * Set the fan speed using one of the four possible states
     */
    void setFan(FanState fan);

    /*
     * @returns The current fan state
     */
    FanState getFan() const;

    /**
     * @returns The calculated checksum
     */
    unsigned char getChecksum() const;

    /**
     * @returns The complete packet, as a set of bits
     */
    std::vector<bool> getPacket() const;
private:
    void computeChecksum();
private:
    static const unsigned int FAN_SHIFT;
    static const unsigned int FAN_MASK;

    static const unsigned int LIGHT_SHIFT;
    static const unsigned int LIGHT_MASK;

    static const unsigned int SWITCH_SHIFT;
    static const unsigned int SWITCH_MASK;

    static const unsigned int CSUM_SHIFT;
    static const unsigned int CSUM_MASK;
private:
    std::bitset<22> packet;
};

} /* namespace fancontrol */
} /* namespace gr */

#endif /* LIB_FANPACKET_HH_ */
