#include <Arduino.h>
#include <memory>
#include <array>

#include <drivers/motor.hpp>
#include <conn/rc.hpp>
#include "driving.hpp"

#define LOGGING 0

// template <typename T, typename... Args>
// std::unique_ptr<T> make_unique(Args &&... args)
// {
//   return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
// }

std::array<Motor, 4> motors = {
    Motor(26, 27, 12),  // Front-left
    Motor(25, 33, 13),  // Front-right
    Motor(32, 5, 14),   // Back-right
    Motor(18, 19, 15)}; // Back-left

std::unique_ptr<RC> rc;
//std::unique_ptr<Driving> driving = make_unique<Driving>(motors);
Driving *driving = new Driving(motors);
void setup()
{
  Serial.begin(115200);
  rc.reset(new RC());
}

void loop()
{
  auto input = rc->get_input();
#if LOGGING
  Serial.println(input.to_string().c_str());
#endif
  driving->loop(input);
#if LOGGING
  for (auto i = 0; i < 4; i++)
    Serial.printf("Motor: %d, Speed: %d, Direction: %d\n", i, (int)(motors[i].get_current_speed()), (int)(motors[i].get_direction()));

  delay(500);
#endif
}