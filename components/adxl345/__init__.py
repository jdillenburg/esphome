import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID, ICON_RULER, STATE_CLASS_MEASUREMENT
from esphome.components import i2c, sensor

DEPENDENCIES = ['i2c']
AUTO_LOAD = ['sensor']
MULTI_CONF = True

adxl345_ns = cg.esphome_ns.namespace('adxl345')
ADXL345Component = adxl345_ns.class_('ADXL345Component', cg.PollingComponent, i2c.I2CDevice)

CONF_RANGE = "range"
RANGE_2G = 0
RANGE_4G = 1
RANGE_8G = 2
RANGE_16G = 3

CONF_OFF_VERTICAL = "off_vertical"
CONF_JITTER = "jitter"
CONF_ACCEL_X = "accel_x"
CONF_ACCEL_Y = "accel_y"
CONF_ACCEL_Z = "accel_z"

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(ADXL345Component),
    cv.Optional(CONF_RANGE, default="2G"): cv.enum({
        "2G": RANGE_2G,
        "4G": RANGE_4G,
        "8G": RANGE_8G,
        "16G": RANGE_16G,
    }, upper=True),
    cv.Optional(CONF_OFF_VERTICAL): sensor.sensor_schema(
        unit_of_measurement="°",
        icon=ICON_RULER,
        accuracy_decimals=1,
        state_class=STATE_CLASS_MEASUREMENT,
    ),
    cv.Optional(CONF_JITTER): sensor.sensor_schema(
        unit_of_measurement="m/s²",
        icon="mdi:vibrate",
        accuracy_decimals=3,
        state_class=STATE_CLASS_MEASUREMENT,
    ),
    cv.Optional(CONF_ACCEL_X): sensor.sensor_schema(
        unit_of_measurement="m/s²",
        icon="mdi:axis-x-arrow",
        accuracy_decimals=3,
        state_class=STATE_CLASS_MEASUREMENT,
    ),
    cv.Optional(CONF_ACCEL_Y): sensor.sensor_schema(
        unit_of_measurement="m/s²",
        icon="mdi:axis-y-arrow",
        accuracy_decimals=3,
        state_class=STATE_CLASS_MEASUREMENT,
    ),
    cv.Optional(CONF_ACCEL_Z): sensor.sensor_schema(
        unit_of_measurement="m/s²",
        icon="mdi:axis-z-arrow",
        accuracy_decimals=3,
        state_class=STATE_CLASS_MEASUREMENT,
    ),
}).extend(cv.polling_component_schema("1s")).extend(i2c.i2c_device_schema(0x53))

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)
    
    cg.add(var.set_range(config[CONF_RANGE]))
    
    if CONF_OFF_VERTICAL in config:
        sens = await sensor.new_sensor(config[CONF_OFF_VERTICAL])
        cg.add(var.set_off_vertical_sensor(sens))
    
    if CONF_JITTER in config:
        sens = await sensor.new_sensor(config[CONF_JITTER])
        cg.add(var.set_jitter_sensor(sens))
        
    if CONF_ACCEL_X in config:
        sens = await sensor.new_sensor(config[CONF_ACCEL_X])
        cg.add(var.set_accel_x_sensor(sens))
        
    if CONF_ACCEL_Y in config:
        sens = await sensor.new_sensor(config[CONF_ACCEL_Y])
        cg.add(var.set_accel_y_sensor(sens))
        
    if CONF_ACCEL_Z in config:
        sens = await sensor.new_sensor(config[CONF_ACCEL_Z])
        cg.add(var.set_accel_z_sensor(sens))
