# ADXL345 Component for ESPHome

This is a custom component for ESPHome that interfaces with the ADXL345 3-axis accelerometer.

## Features

- Supports all standard I2C configuration options including multiple I2C buses
- Configurable measurement range (2G, 4G, 8G, 16G)
- Provides raw acceleration values for X, Y, and Z axes
- Calculates off-vertical angle (useful for bed/chair position tracking)
- Calculates jitter (total movement across all axes)
- Full Home Assistant integration with proper device classes and units

## Installation

1. Create a `components` directory in your ESPHome configuration directory if it doesn't exist
2. Create an `adxl345` directory inside the `components` directory
3. Copy the following files into the `adxl345` directory:
   - `__init__.py`
   - `adxl345.h`
   - `adxl345.cpp`
   - `sensor.py`

## Dependencies

This component requires the following libraries:
- Wire
- SPI
- Adafruit BusIO
- Adafruit Unified Sensor
- Adafruit ADXL345

Add these to your ESPHome configuration:

```yaml
libraries:
  - "Wire"
  - "SPI"
  - "Adafruit BusIO"
  - "Adafruit Unified Sensor"
  - "Adafruit ADXL345"
```

## Usage

### Basic Configuration

```yaml
# Define component and sensors for accel_x, accel_y and accel_z
adxl345:
  - id: my_adxl345
    address: 0x53
    update_interval: 100ms
    accel_x:
      name: "Acceleration X"
    accel_y:
      name: "Acceleration Y"
    accel_z:
      name: "Acceleration Z"
```

### Advanced Configuration

```yaml
# Define I2C bus
i2c:
  sda: GPIO21
  scl: GPIO22
  frequency: 400kHz

# Define component with all options
adxl345:
  - id: my_adxl345
    address: 0x53
    update_interval: 100ms
    range: 4G  # Options: 2G, 4G, 8G, 16G
    accel_x:
      name: "Acceleration X"
      filters:
        - median:
            window_size: 5
            send_every: 5
            send_first_at: 1
    accel_y:
      name: "Acceleration Y"
    accel_z:
      name: "Acceleration Z"
    off_vertical:
      name: "Tilt Angle"
      filters:
        - sliding_window_moving_average:
            window_size: 10
            send_every: 5
    jitter:
      name: "Movement Detection"
      filters:
        - threshold:
            above: 10.0
            then: ON
            below: 2.0
            then: OFF
```

## Available Sensors

| Sensor | Description | Unit |
|--------|-------------|------|
| `accel_x` | Raw X-axis acceleration | m/s² |
| `accel_y` | Raw Y-axis acceleration | m/s² |
| `accel_z` | Raw Z-axis acceleration | m/s² |
| `off_vertical` | Maximum angle from vertical (derived from pitch and roll) | degrees |
| `jitter` | Sum of absolute accelerations across all axes (movement detection) | m/s² |

## Example Use Cases

- Bed/chair incline monitoring
- Movement detection
- Vibration monitoring
- Orientation sensing