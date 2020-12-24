#pragma once

#include <array>
#include <string>
#include <sstream>
#include "drivers/motor.hpp"
#include "conn/rc.hpp"
#include "helper.hpp"
class Driving
{
public:
    enum Mode
    {
        idle,
        normal,
        tank,
    };

public:
    Driving(const std::array<Motor, 4> &motors) : motors(motors)
    {
        mode = idle;
    }

    void set_mode(Mode m) { mode = m; }
    Mode get_mode() { return mode; }

    void loop(const Driving_Input_Values &input)
    {
        // CH0 (R-stick) left-right
        // CH1 (R-stick) up-down
        // CH2 (L-stick) up-down
        // CH3 (L-stick) left-right
        // CH4 (L1-toggle) up=1000, down=2000
        // CH5 (R1-toggle) up=1000, middle=1500, down=2000

        if (input.ch4 > 1900) // Arm the engine
        {
            // Set direction

            if (is_between(input.ch5, 900, 1100))
            {
                set_mode(normal);
            }
            else if (is_between(input.ch5, 1400, 1600))
            {
                set_mode(normal);
            }
            else if (is_between(input.ch5, 1900, 2100))
            {
                set_mode(tank);
            }
            switch (mode)
            {
            case normal:
            {
                // double throttle = ((double)(input.ch2) - 1000) / 1000; // down = 0/1000 = 0, up = 1000/1000 = 1
                double steering = ((double)(input.ch0) - 1500) / 500; // left = -500/500 = -1, middle = 0/1000 = 0, right = 500/500 = 1
                double throttle = ((double)(input.ch1) - 1500) / 500;

                Motor::Direction dir = Motor::idle;
                if (throttle > 0)
                    dir = Motor::forward;
                else if (throttle < 0)
                    dir = Motor::backward;
                throttle = abs(throttle);
                for (auto &m : motors)
                    m.set_direction(dir);

                if (dir != Motor::idle)
                {
                    motors[0].set_speed(throttle * throttle_scaler - steering * steering_scaler);
                    motors[1].set_speed(throttle * throttle_scaler + steering * steering_scaler);
                    motors[2].set_speed(throttle * throttle_scaler + steering * steering_scaler);
                    motors[3].set_speed(throttle * throttle_scaler - steering * steering_scaler);
                }
                break;
            }
            case tank:
            {
                double throttle_left = ((double)(input.ch2) - 1500) / 500;
                double throttle_right = ((double)(input.ch1) - 1500) / 500;
                Motor::Direction dir_left = Motor::idle;
                Motor::Direction dir_right = Motor::idle;
                if (is_between(input.ch2, 950, 1450))
                    dir_left = Motor::backward;
                else if (is_between(input.ch2, 1550, 2050))
                    dir_left = Motor::forward;

                if (is_between(input.ch1, 950, 1450))
                    dir_right = Motor::backward;
                else if (is_between(input.ch1, 1550, 2050))
                    dir_right = Motor::forward;

                // Left motors: 0,3
                motors[0].set_direction(dir_left);
                motors[0].set_speed(abs(throttle_left) * 0.70 + 0.30);
                motors[3].set_direction(dir_left);
                motors[3].set_speed(abs(throttle_left) * 0.70 + 0.30);
                // Right motors: 1,2
                motors[1].set_direction(dir_right);
                motors[1].set_speed(abs(throttle_right) * 0.70 + 0.30);
                motors[2].set_direction(dir_right);
                motors[2].set_speed(abs(throttle_right) * 0.70 + 0.30);
                break;
            }
            case idle:
                break;
            }
        }
        else
        {
            set_mode(idle);
            for (auto &m : motors)
            {
                m.set_speed(0);
                m.set_direction(Motor::idle);
            }
        }
    }

private:
    std::array<Motor, 4> motors;
    double throttle_scaler = 0.85;
    double steering_scaler = 0.15;
    Mode mode;
};