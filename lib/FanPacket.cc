/*
 * FanPacket.cc
 *
 *  Created on: Sep 9, 2015
 *      Author: papes
 */

#include "FanPacket.hh"

#include <iostream>

namespace gr {
namespace fancontrol {

// Some constants
const unsigned int FanPacket::FAN_SHIFT = 5;
const unsigned int FanPacket::FAN_MASK = 0x60;

const unsigned int FanPacket::LIGHT_SHIFT = 7;
const unsigned int FanPacket::LIGHT_MASK = 0x1F80;

const unsigned int FanPacket::SWITCH_SHIFT = 14;
const unsigned int FanPacket::SWITCH_MASK = 0x3C000;

const unsigned int FanPacket::CSUM_SHIFT = 0;
const unsigned int FanPacket::CSUM_MASK = 0xF;

FanPacket::FanPacket() :
        packet(0x1C2010) {

}

FanPacket::~FanPacket() {

}

void FanPacket::setDipSwitches(unsigned char switches) {
    if (switches > 15)
        switches = 15; // There are 4 switches, so if you go higher, you're doing something dumb.

    packet &= ~SWITCH_MASK;
    packet |= (switches << SWITCH_SHIFT);

    computeChecksum();
}

/**
 * @returns The current dip-switch configuration
 */
unsigned char FanPacket::getDipSwitches(unsigned char switches) const {
    return (packet.to_ulong() & SWITCH_MASK) >> SWITCH_SHIFT;
}

/**
 * Sets the light level. 0x3F (all ones) is off.
 */
void FanPacket::setLight(unsigned char light) {
    if (light > 0x3F)
        light = 0x3F;

    packet &= ~LIGHT_MASK;
    packet |= (light << LIGHT_SHIFT);

    computeChecksum();
}
/**
 * @returns The light level
 */
unsigned char FanPacket::getLight() const {
    return (packet.to_ulong() & LIGHT_MASK) >> LIGHT_SHIFT;
}

/**
 * Set the fan speed using one of the four possible states
 */
void FanPacket::setFan(FanState fan) {
    packet &= ~FAN_MASK;
    packet |= (fan << FAN_SHIFT);

    computeChecksum();
}

/*
 *
 */
FanState FanPacket::getFan() const {
    return static_cast<FanState>((packet.to_ulong() & FAN_MASK) >> FAN_SHIFT);
}

unsigned char FanPacket::getChecksum() const {
    return (packet.to_ulong() & CSUM_MASK) >> CSUM_SHIFT;
}

std::vector<bool> FanPacket::getPacket() const {
    std::vector<bool> result;
    result.reserve(packet.size());

    // Bitset stores everything in the reverse order of what we actually need
    for (int i = packet.size(); i > 0; --i) {
        result.push_back(packet[i - 1]);
    }

    std::cout << packet << '\n';

    return result;
}

void FanPacket::computeChecksum() {
    static const unsigned int GROUP1_MASK = 0x20000;
    static const unsigned int GROUP1_SHIFT = 17;

    static const unsigned int GROUP2_MASK = 0x1E000;
    static const unsigned int GROUP2_SHIFT = 13;

    static const unsigned int GROUP3_MASK = 0x1E00;
    static const unsigned int GROUP3_SHIFT = 9;

    static const unsigned int GROUP4_MASK = 0x1E0;
    static const unsigned int GROUP4_SHIFT = 5;

    static const unsigned int GROUP5_MASK = 0x10;
    static const unsigned int GROUP5_SHIFT = 4;

    // If this bit is set, we add one to the checksum
    std::bitset<1> group1((packet.to_ulong() & GROUP1_MASK) >> GROUP1_SHIFT);
    std::bitset<4> group2((packet.to_ulong() & GROUP2_MASK) >> GROUP2_SHIFT);
    std::bitset<4> group3((packet.to_ulong() & GROUP3_MASK) >> GROUP3_SHIFT);
    std::bitset<4> group4((packet.to_ulong() & GROUP4_MASK) >> GROUP4_SHIFT);
    std::bitset<4> group5((packet.to_ulong() & GROUP5_MASK) >> GROUP5_SHIFT);

    unsigned int csum = (group1.to_ulong() + group2.to_ulong() + group3.to_ulong() + group4.to_ulong() + group5.to_ulong()) % 16u;
    packet &= ~CSUM_MASK;
    packet |= (csum << CSUM_SHIFT);
}

} /* namespace fancontrol */
} /* namespace gr */
