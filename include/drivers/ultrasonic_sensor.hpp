#pragma once

#include <cstdint>

class UltrasonicSensor
{
public:
    UltrasonicSensor(uint8_t trigger_pin, uint8_t echo_pin) : trigger_pin(trigger_pin), echo_pin(echo_pin)
    {
    }

    int get_distance() { return -1; }

private:
    uint8_t trigger_pin, echo_pin;
};