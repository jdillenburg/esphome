import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID

DEPENDENCIES = ['uart']
AUTO_LOAD = ['sensor']
CODEOWNERS = ["@jdillenburg"]  


tfmini_ns = cg.esphome_ns.namespace('tfmini')
TFMiniComponent = tfmini_ns.class_('TFMiniComponent', cg.Component)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(TFMiniComponent)
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
