# TFMini-S Time of Flight Distance Sensor for ESPHome

This is an external component for ESPHome that supports the TFMini-S time of flight distance sensor.

## Installation

You can install this component in two ways:

### 1. Using ESPHome external components

```yaml
external_components:
  - source: github://your-username/esphome-tfmini@main
    components: [ tfmini ]
```

### 2. Manual installation

Clone this repository into your ESPHome `custom_components` directory:

```bash
cd <your config directory>/custom_components
git clone https://github.com/your-username/esphome-tfmini.git
```

## Configuration

Add the following to your ESPHome configuration file:

```yaml
# Example configuration
uart:
  tx_pin: GPIO17
  rx_pin: GPIO16
  baud_rate: 115200

sensor:
  - platform: tfmini
    name: "Distance Sensor"
    update_interval: 1s
```

## Features

- Measures distance in meters
- Automatic configuration of the TFMini-S sensor
- Signal strength validation
- Temperature monitoring (internal, not exposed yet)

## Notes

- The sensor is configured to use the standard 9-byte output format
- Refresh rate is set to 100Hz
- Data is provided in meters with 2 decimal precision

## License

This component is licensed under the MIT License.