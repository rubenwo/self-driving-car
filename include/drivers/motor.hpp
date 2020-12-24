#pragma once
#include <Arduino.h>
#include <ESP32PWM.h>

class Motor
{
public:
    enum Direction
    {
        forward,
        backward,
        idle
    };

public:
    Motor(uint8_t forward_pin, uint8_t backward_pin, uint8_t pwm_pin)
        : forward_pin(forward_pin), backward_pin(backward_pin), pwm_pin(pwm_pin)
    {
        pinMode(forward_pin, OUTPUT);
        pinMode(backward_pin, OUTPUT);
        pwm_driver.attachPin(pwm_pin, freq, resolution);
    }

    ~Motor()
    {
        pwm_driver.detachPin(pwm_pin);
    }

    /**
     * Set the speed of the motor
     * 
     * If the direction is set to either: forward or backward. This function will write a pwm signal according to the speed.
     * @param speed : A double between 0.0 and 1.0 that indicates how fast the motor should spin. Where 0.0 is no movement, and 1.0 is maximum speed.
     */
    void set_speed(double speed)
    {
        if (speed < 0)
            speed = 0;
        if (speed > 1)
            speed = 1;

        current_speed = (uint8_t)(speed * max_speed);
        if (dir != idle)
            pwm_driver.write(current_speed);
    }

    uint8_t get_current_speed() { return current_speed; }

    /**
     * Set direction of the motor
     * 
     * @param dir : A enum to indicate which direction the motor should spin. Possible values are: idle, forward and backward. Default = idle.
     */
    void set_direction(Direction dir = idle)
    {
        this->dir = dir;
        switch (dir)
        {
        case idle:
            digitalWrite(forward_pin, LOW);
            digitalWrite(backward_pin, LOW);
            break;
        case forward:
            digitalWrite(forward_pin, HIGH);
            digitalWrite(backward_pin, LOW);
            break;
        case backward:
            digitalWrite(forward_pin, LOW);
            digitalWrite(backward_pin, HIGH);
            break;
        }
    }

    Direction get_direction() { return dir; }

private:
    const int freq = 30000;
    const int resolution = 8;

    ESP32PWM pwm_driver;
    uint8_t current_speed;
    double max_speed = (double)(UINT8_MAX);
    Direction dir = idle;
    uint8_t forward_pin, backward_pin, pwm_pin;
};