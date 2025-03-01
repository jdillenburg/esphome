#pragma once

#include <esphome/core/component.h>
#include <esphome/components/sensor/sensor.h>
#include <esphome/components/uart/uart.h>

namespace esphome {
namespace tfmini {

enum DistanceUnit {
  CENTIMETERS,
  METERS
};

class TFMiniSensor : public sensor::Sensor, public Component, public uart::UARTDevice {
 public:
  void setup() override;
  void loop() override;
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::AFTER_CONNECTION; }

  void set_strength_sensor(sensor::Sensor *strength_sensor) { strength_sensor_ = strength_sensor; }
  void set_temperature_sensor(sensor::Sensor *temperature_sensor) { temperature_sensor_ = temperature_sensor; }
  void set_distance_unit(const std::string &distance_unit) {
    if (distance_unit == "METERS") {
      this->distance_unit_ = METERS;
    } else {
      this->distance_unit_ = CENTIMETERS;
    }
  }

 protected:
  void setup_internal_();
  
  sensor::Sensor *strength_sensor_{nullptr};
  sensor::Sensor *temperature_sensor_{nullptr};
  DistanceUnit distance_unit_{CENTIMETERS};
};

} // namespace tfmini
} // namespace esphome