#pragma once

#include <memory>
#include <IBusBM.h>
#include <HardwareSerial.h>

#include "helper.hpp"

class RC
{

public:
    RC()
    {
        IBus.begin(Serial2, 1);
    }

    ~RC() {}

    Driving_Input_Values get_input()
    {
        values.ch0 = IBus.readChannel(0);
        values.ch1 = IBus.readChannel(1);
        values.ch2 = IBus.readChannel(2);
        values.ch3 = IBus.readChannel(3);
        values.ch4 = IBus.readChannel(4);
        values.ch5 = IBus.readChannel(5);
        return values;
    }

private:
    IBusBM IBus;

    Driving_Input_Values values;
};
