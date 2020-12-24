#pragma once

#include <string>
#include <sstream>

inline bool is_between(int val, int low, int high)
{
    return val >= low && val <= high;
}

struct Driving_Input_Values
{
    int ch0, ch1, ch2, ch3, ch4, ch5;
    std::string to_string()
    {
        std::stringstream ss;
        ss << "CH0: " << ch0 << " CH1: " << ch1 << " CH2: " << ch2 << " CH3: " << ch3 << " CH4: " << ch4 << " CH5: " << ch5;
        return ss.str();
    }
};