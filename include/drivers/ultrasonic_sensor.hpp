#pragma once

#include <cstdint>
#include <Ultrasonic.h>

class UltrasonicSensor
{
public:
    UltrasonicSensor(uint8_t trigger_pin, uint8_t echo_pin) : trigger_pin(trigger_pin), echo_pin(echo_pin), ultrasonic(trigger_pin, echo_pin)
    {
    }

    void loop()
    {
        distance = ultrasonic.read();
    }

    int get_distance() { return distance; }

private:
    uint8_t trigger_pin, echo_pin;
    uint8_t distance;
    Ultrasonic ultrasonic;
};