#include "pl_i2c_base.h"
#include "esp_check.h"

//==============================================================================

static const char* TAG = "pl_i2c";

//==============================================================================

namespace PL {

//==============================================================================

I2C::I2C(i2c_port_num_t port, gpio_num_t sdaPin, gpio_num_t sclPin, bool enableInternalPullUp) :
    port(port), sdaPin(sdaPin), sclPin(sclPin), enableInternalPullUp(enableInternalPullUp) { }

//==============================================================================

I2C::~I2C() {
  if (controllerBusHandle)
    i2c_del_master_bus(controllerBusHandle);
}

//==============================================================================

esp_err_t I2C::Lock(TickType_t timeout) {
  esp_err_t error = mutex.Lock(timeout);
  if (error == ESP_OK)
    return ESP_OK;
  if (error == ESP_ERR_TIMEOUT && timeout == 0)
    return ESP_ERR_TIMEOUT;
  ESP_RETURN_ON_ERROR(error, TAG, "mutex lock failed");
  return ESP_OK;
}

//==============================================================================

esp_err_t I2C::Unlock() {
  ESP_RETURN_ON_ERROR(mutex.Unlock(), TAG, "mutex unlock failed");
  return ESP_OK;
}

//==============================================================================

esp_err_t I2C::Initialize() {
  LockGuard lg(*this);
  if (controllerBusHandle)
    return ESP_OK;
  i2c_master_bus_config_t controllerBusConfig = {};
  controllerBusConfig.i2c_port = port;
  controllerBusConfig.sda_io_num = sdaPin;
  controllerBusConfig.scl_io_num = sclPin;
  controllerBusConfig.clk_source = I2C_CLK_SRC_DEFAULT;
  controllerBusConfig.glitch_ignore_cnt = 7;
  controllerBusConfig.flags.enable_internal_pullup = enableInternalPullUp;
  ESP_RETURN_ON_ERROR(i2c_new_master_bus(&controllerBusConfig, &controllerBusHandle), TAG, "I2C new master bus failed");
  return ESP_OK;
}

//==============================================================================

}