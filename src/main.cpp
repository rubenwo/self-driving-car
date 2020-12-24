#include <Arduino.h>
#include <memory>
#include <array>

#define LOGGING 0

#include "logic/car_controller.hpp"

#include "conn/rc.hpp"
#include "conn/wifi.hpp"
#include "drivers/motor.hpp"

std::array<Motor, 4> motors = {
    Motor(26, 27, 12),  // Front-left
    Motor(25, 33, 13),  // Front-right
    Motor(32, 5, 14),   // Back-right
    Motor(18, 19, 15)}; // Back-left

std::unique_ptr<RC> rc;
//std::unique_ptr<WifiController> rc;
CarController *controller = new CarController(motors);

void setup()
{
  Serial.begin(115200);
  //rc.reset(new WifiController("",""));
  rc.reset(new RC());
}

void loop()
{
  auto input = rc->get_input();
#if LOGGING
  Serial.println(input.to_string().c_str());
#endif
  controller->loop(input);
#if LOGGING
  for (auto i = 0; i < 4; i++)
    Serial.printf("Motor: %d, Speed: %d, Direction: %d\n", i, (int)(motors[i].get_current_speed()), (int)(motors[i].get_direction()));
  Serial.println(controller->get_mode());
  delay(500);
#endif
}