#pragma once
#include <memory>
#include <IBusBM.h>
#include <HardwareSerial.h>
#include <string>
#include <sstream>

struct RC_Input_Values
{
    int ch0, ch1, ch2, ch3, ch4, ch5;
    std::string to_string()
    {
        std::stringstream ss;
        ss << "CH0: " << ch0 << " CH1: " << ch1 << " CH2: " << ch2 << " CH3: " << ch3 << " CH4: " << ch4 << " CH5: " << ch5;
        return ss.str();
    }
};

class RC
{
private:
    IBusBM IBus;

    RC_Input_Values values;

public:
    RC()
    {
        IBus.begin(Serial2, 1);
    }

    ~RC() {}

    RC_Input_Values get_input()
    {
        values.ch0 = IBus.readChannel(0);
        values.ch1 = IBus.readChannel(1);
        values.ch2 = IBus.readChannel(2);
        values.ch3 = IBus.readChannel(3);
        values.ch4 = IBus.readChannel(4);
        values.ch5 = IBus.readChannel(5);
        return values;
    }
};
