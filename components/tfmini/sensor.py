import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, uart
from esphome.const import (
    CONF_ID,
    DEVICE_CLASS_DISTANCE,
    DEVICE_CLASS_SIGNAL_STRENGTH,
    DEVICE_CLASS_TEMPERATURE,
    STATE_CLASS_MEASUREMENT,
    UNIT_METER,
    UNIT_CENTIMETER,
    UNIT_CELSIUS,
    ICON_RULER,
    ENTITY_CATEGORY_DIAGNOSTIC,
)

DEPENDENCIES = ['uart']

tfmini_ns = cg.esphome_ns.namespace('tfmini')
TFMiniSensor = tfmini_ns.class_('TFMiniSensor', sensor.Sensor, cg.Component,
                              uart.UARTDevice)

CONF_STRENGTH = "strength"
CONF_TEMPERATURE = "temperature"
CONF_DISTANCE_UNIT = "distance_unit"

CONFIG_SCHEMA = (
    sensor.sensor_schema(
        TFMiniSensor,
        unit_of_measurement=UNIT_CENTIMETER,  # Default to cm instead of meters
        accuracy_decimals=0,  # Integer precision for cm
        device_class=DEVICE_CLASS_DISTANCE,
        state_class=STATE_CLASS_MEASUREMENT,
        icon=ICON_RULER,
    )
    .extend({
        cv.Optional(CONF_DISTANCE_UNIT, default="cm"): cv.enum({
            "cm": "CENTIMETERS",
            "m": "METERS",
        }),
        cv.Optional(CONF_STRENGTH): sensor.sensor_schema(
            unit_of_measurement="",
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_SIGNAL_STRENGTH,
            state_class=STATE_CLASS_MEASUREMENT,
            entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
        ),
        cv.Optional(CONF_TEMPERATURE): sensor.sensor_schema(
            unit_of_measurement=UNIT_CELSIUS,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_TEMPERATURE,
            state_class=STATE_CLASS_MEASUREMENT,
            entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
        ),
    })
    .extend(uart.UART_DEVICE_SCHEMA)
)

async def to_code(config):
    var = await sensor.new_sensor(config)
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)
    
    cg.add(var.set_distance_unit(config[CONF_DISTANCE_UNIT]))
    
    if config[CONF_DISTANCE_UNIT] == "m":
        cg.add(var.set_unit_of_measurement(UNIT_METER))
        cg.add(var.set_accuracy_decimals(2))
    
    if CONF_STRENGTH in config:
        sens = await sensor.new_sensor(config[CONF_STRENGTH])
        cg.add(var.set_strength_sensor(sens))
    
    if CONF_TEMPERATURE in config:
        sens = await sensor.new_sensor(config[CONF_TEMPERATURE])
        cg.add(var.set_temperature_sensor(sens))