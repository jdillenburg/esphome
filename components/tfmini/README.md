# TFMini-S Time of Flight Distance Sensor for ESPHome

This is an external component for ESPHome that supports the TFMini-S time of flight distance sensor. It provides distance measurements along with signal strength and temperature readings from the sensor.

## Features

- Distance measurement in centimeters or meters (configurable)
- Signal strength monitoring for reliability assessment
- Internal temperature monitoring
- Automatic configuration of the TFMini-S sensor
- Configurable at 100Hz refresh rate

## Installation

You can install this component in two ways:

### 1. Using ESPHome external components

```yaml
external_components:
  - source: github://jdillenburg/esphome@master
    components: [ tfmini ]
```

### 2. Manual installation

Clone this repository into your ESPHome external components directory:

```bash
cd <your config directory>/esphome/external_components
git clone https://github.com/jdillenburg/esphome.git
```

Or copy the component files directly:

```bash
mkdir -p <your config directory>/esphome/components/tfmini
cd <your config directory>/esphome/components/tfmini
wget https://raw.githubusercontent.com/jdillenburg/esphome/main/components/tfmini/__init__.py
wget https://raw.githubusercontent.com/jdillenburg/esphome/main/components/tfmini/sensor.py
wget https://raw.githubusercontent.com/jdillenburg/esphome/main/components/tfmini/tfmini.cpp
wget https://raw.githubusercontent.com/jdillenburg/esphome/main/components/tfmini/tfmini.h
```

Then reference it in your configuration:

```yaml
external_components:
  - source: <your config directory>/esphome/components
    components: [ tfmini ]
```

## Configuration

Add the following to your ESPHome configuration file:

### Basic Configuration

```yaml
# UART configuration for the TFMini-S
uart:
  tx_pin: GPIO17
  rx_pin: GPIO16
  baud_rate: 115200

# TFMini-S sensor configuration
sensor:
  - platform: tfmini
    name: "Distance"
    id: tfmini_distance
```

### Full Configuration with All Options

```yaml
# UART configuration for the TFMini-S
uart:
  tx_pin: GPIO17
  rx_pin: GPIO16
  baud_rate: 115200

# TFMini-S sensor configuration with all sensors
sensor:
  - platform: tfmini
    name: "Distance"
    id: tfmini_distance
    distance_unit: cm  # Options: cm (default) or m
    strength:
      name: "TFMini Signal Strength"
      id: tfmini_strength
    temperature:
      name: "TFMini Temperature"
      id: tfmini_temperature
```

## Configuration Options

| Option | Default | Description |
|--------|---------|-------------|
| `name` | Required | Name of the distance sensor |
| `distance_unit` | `cm` | Unit for distance measurement. Options: `cm` or `m` |
| `strength` | Optional | Configuration for signal strength sensor |
| `temperature` | Optional | Configuration for temperature sensor |

## Technical Notes

- The sensor is configured to use the standard 9-byte output format
- Refresh rate is set to 100Hz
- The component validates signal strength to ensure reliable readings (minimum 100)
- Default unit is centimeters as that's the native output of the TFMini-S

## Wiring

Connect your TFMini-S to your ESP device as follows:

| TFMini-S | ESP |
|----------|-----|
| 5V       | 5V  |
| GND      | GND |
| TX       | RX (GPIO16 in example) |
| RX       | TX (GPIO17 in example) |

## Troubleshooting

If you're having issues:

1. Check the wiring connections
2. Ensure the UART pins are correctly defined
3. Set the logger to DEBUG level to see detailed messages
4. Verify the sensor has a clear line of sight to the target
5. Check signal strength values to ensure reliable readings

## License

This component is licensed under the MIT License.
