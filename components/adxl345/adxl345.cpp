#include "adxl345.h"
#include "esphome/core/log.h"

namespace esphome {
namespace adxl345 {

static const char *const TAG = "adxl345";

void ADXL345Component::setup() {
  ESP_LOGCONFIG(TAG, "Setting up ADXL345...");
  
  if (!accel_.begin(this->address_)) {
    ESP_LOGE(TAG, "Could not find ADXL345 sensor at address 0x%02X!", this->address_);
    this->mark_failed();
    return;
  }
  
  // Map our range enum values to Adafruit library constants
  range_t adafruit_range;
  switch (this->range_) {
    case 0: // RANGE_2G
      adafruit_range = ADXL345_RANGE_2_G;
      break;
    case 1: // RANGE_4G
      adafruit_range = ADXL345_RANGE_4_G;
      break;
    case 2: // RANGE_8G
      adafruit_range = ADXL345_RANGE_8_G;
      break;
    case 3: // RANGE_16G
      adafruit_range = ADXL345_RANGE_16_G;
      break;
    default:
      adafruit_range = ADXL345_RANGE_2_G;
      break;
  }
  
  accel_.setRange(adafruit_range);
  ESP_LOGD(TAG, "ADXL345 setup complete");
}

void ADXL345Component::dump_config() {
  ESP_LOGCONFIG(TAG, "ADXL345:");
  LOG_I2C_DEVICE(this);
  LOG_UPDATE_INTERVAL(this);
  
  const char* range_str;
  switch (this->range_) {
    case 0: range_str = "2G"; break;
    case 1: range_str = "4G"; break;
    case 2: range_str = "8G"; break;
    case 3: range_str = "16G"; break;
    default: range_str = "Unknown"; break;
  }
  ESP_LOGCONFIG(TAG, "  Range: %s", range_str);
  
  if (this->off_vertical_ != nullptr) {
    LOG_SENSOR("  ", "Off Vertical", this->off_vertical_);
  }
  if (this->jitter_ != nullptr) {
    LOG_SENSOR("  ", "Jitter", this->jitter_);
  }
  if (this->accel_x_ != nullptr) {
    LOG_SENSOR("  ", "Acceleration X", this->accel_x_);
  }
  if (this->accel_y_ != nullptr) {
    LOG_SENSOR("  ", "Acceleration Y", this->accel_y_);
  }
  if (this->accel_z_ != nullptr) {
    LOG_SENSOR("  ", "Acceleration Z", this->accel_z_);
  }
}

void ADXL345Component::update() {
  sensors_event_t event;
  accel_.getEvent(&event);
  
  // Publish raw accelerometer values if sensors are configured
  if (this->accel_x_ != nullptr) {
    this->accel_x_->publish_state(event.acceleration.x);
  }
  
  if (this->accel_y_ != nullptr) {
    this->accel_y_->publish_state(event.acceleration.y);
  }
  
  if (this->accel_z_ != nullptr) {
    this->accel_z_->publish_state(event.acceleration.z);
  }
  
  // Calculate and publish off_vertical if sensor is configured
  if (this->off_vertical_ != nullptr) {
    double pitch_amount = atan(event.acceleration.y / 
      sqrt(pow(event.acceleration.x, 2) + pow(event.acceleration.z, 2))) * 180 / PI;
    double roll_amount = atan(-1 * event.acceleration.x / 
      sqrt(pow(event.acceleration.y, 2) + pow(event.acceleration.z, 2))) * 180 / PI;
    
    this->off_vertical_->publish_state(max(abs(pitch_amount), abs(roll_amount)));
  }
  
  // Calculate and publish jitter if sensor is configured
  if (this->jitter_ != nullptr) {
    float jitter_value = abs(event.acceleration.x) + abs(event.acceleration.y) + abs(event.acceleration.z);
    this->jitter_->publish_state(jitter_value);
  }
}

} // namespace adxl345
} // namespace esphome