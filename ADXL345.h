#include "esphome.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
  
class ADXL345Sensor : public PollingComponent {
 public:
  Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);
  Sensor *off_vertical = new Sensor();
  Sensor *jitter = new Sensor();

  ADXL345Sensor() : PollingComponent(100) { }

  void setup() override {
    accel.begin();
    /* Set the range to whatever is appropriate for your project */
    // accel.setRange(ADXL345_RANGE_16_G);
    // accel.setRange(ADXL345_RANGE_8_G);
    // accel.setRange(ADXL345_RANGE_4_G);
    accel.setRange(ADXL345_RANGE_2_G);
    //
  }

  void update() override {
    sensors_event_t event;
    accel.getEvent(&event);
    double pitch_amount = atan(event.acceleration.y / 
      sqrt(pow(event.acceleration.x, 2) + pow(event.acceleration.z, 2))) * 180 / PI;
    double roll_amount = atan(-1 * event.acceleration.x / 
      sqrt(pow(event.acceleration.y, 2) + pow(event.acceleration.z, 2))) * 180 / PI;
    // double pitch_amount = atan2(event.acceleration.y, 
    //   sqrt(pow(event.acceleration.x, 2) + pow(event.acceleration.z, 2))) * 180 / PI;
    // double roll_amount = atan2(-1 * event.acceleration.x, 
    //   sqrt(pow(event.acceleration.y, 2) + pow(event.acceleration.z, 2))) * 180 / PI;
    off_vertical -> publish_state(max(abs(pitch_amount), abs(roll_amount)));
    jitter -> publish_state(abs(event.acceleration.x) + abs(event.acceleration.y) +
      abs(event.acceleration.z));
  }
};
