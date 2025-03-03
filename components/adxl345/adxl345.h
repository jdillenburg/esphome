#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/i2c/i2c.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

namespace esphome {
namespace adxl345 {

class ADXL345Component : public PollingComponent, public i2c::I2CDevice {
 public:
  ADXL345Component() : PollingComponent(100) {}

  void setup() override;
  void update() override;
  void dump_config() override;

  void set_off_vertical_sensor(sensor::Sensor *off_vertical) { off_vertical_ = off_vertical; }
  void set_jitter_sensor(sensor::Sensor *jitter) { jitter_ = jitter; }
  void set_accel_x_sensor(sensor::Sensor *accel_x) { accel_x_ = accel_x; }
  void set_accel_y_sensor(sensor::Sensor *accel_y) { accel_y_ = accel_y; }
  void set_accel_z_sensor(sensor::Sensor *accel_z) { accel_z_ = accel_z; }
  
  void set_range(uint8_t range) { range_ = range; }

 protected:
  Adafruit_ADXL345_Unified accel_{12345};
  sensor::Sensor *off_vertical_{nullptr};
  sensor::Sensor *jitter_{nullptr};
  sensor::Sensor *accel_x_{nullptr};
  sensor::Sensor *accel_y_{nullptr};
  sensor::Sensor *accel_z_{nullptr};
  uint8_t range_{0}; // Default to 2G range (0)
};

} // namespace adxl345
} // namespace esphome