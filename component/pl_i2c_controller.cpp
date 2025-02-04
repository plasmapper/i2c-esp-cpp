#include "pl_i2c_controller.h"
#include "esp_check.h"

//==============================================================================

static const char* TAG = "pl_i2c_controller";

//==============================================================================

namespace PL {

//==============================================================================

I2CController::I2CController(std::shared_ptr<I2C> i2c, uint8_t targetAddress, uint32_t sclFrequency) :
    i2c(i2c), targetAddress(targetAddress), sclFrequency(sclFrequency) { }

//==============================================================================

I2CController::~I2CController() {
  if (deviceHandle)
    i2c_master_bus_rm_device(deviceHandle);
}

//==============================================================================

esp_err_t I2CController::Lock(TickType_t timeout) {
  esp_err_t error = mutex.Lock(timeout);
  if (error == ESP_OK)
    return ESP_OK;
  if (error == ESP_ERR_TIMEOUT && timeout == 0)
    return ESP_ERR_TIMEOUT;
  ESP_RETURN_ON_ERROR(error, TAG, "mutex lock failed");
  return ESP_OK;
}

//==============================================================================

esp_err_t I2CController::Unlock() {
  ESP_RETURN_ON_ERROR(mutex.Unlock(), TAG, "mutex unlock failed");
  return ESP_OK;
}

//==============================================================================

esp_err_t I2CController::Initialize() {
  LockGuard lg(*this, *i2c);

  if (!i2c->controllerBusHandle) {
    ESP_RETURN_ON_ERROR(i2c->Initialize(), TAG, "I2C initialize failed");
  }

  if (!deviceHandle) {
    i2c_device_config_t deviceConfig = {};
    deviceConfig.dev_addr_length = I2C_ADDR_BIT_LEN_7;
    deviceConfig.device_address = targetAddress;
    deviceConfig.scl_speed_hz = sclFrequency;
    ESP_RETURN_ON_ERROR(i2c_master_bus_add_device(i2c->controllerBusHandle, &deviceConfig, &deviceHandle), TAG, "initialize I2C controller device failed");
  }

  return ESP_OK;
}

//==============================================================================

esp_err_t I2CController::Read(void* dest, size_t size) {
  LockGuard lg(*this, *i2c);
  ESP_RETURN_ON_FALSE(deviceHandle, ESP_ERR_INVALID_STATE, TAG, "I2C controller is not initialized");
  ESP_RETURN_ON_ERROR(i2c_master_receive(deviceHandle, (uint8_t*)dest, size, timeout * portTICK_PERIOD_MS), TAG, "I2C receive failed");
  return ESP_OK;
}

//==============================================================================

esp_err_t I2CController::Write(const void* src, size_t size) {
  LockGuard lg(*this, *i2c);
  ESP_RETURN_ON_FALSE(deviceHandle, ESP_ERR_INVALID_STATE, TAG, "I2C controller is not initialized");
  ESP_RETURN_ON_ERROR(i2c_master_transmit(deviceHandle, (const uint8_t*)src, size, timeout * portTICK_PERIOD_MS), TAG, "I2C transmit failed");
  return ESP_OK;
}

//==============================================================================

esp_err_t I2CController::WriteAndRead(const void* src, size_t srcSize, void* dest, size_t destSize) {
  LockGuard lg(*this, *i2c);
  ESP_RETURN_ON_FALSE(deviceHandle, ESP_ERR_INVALID_STATE, TAG, "I2C controller is not initialized");
  ESP_RETURN_ON_ERROR(i2c_master_transmit_receive(deviceHandle, (const uint8_t*)src, srcSize, (uint8_t*)dest, destSize, timeout * portTICK_PERIOD_MS), TAG, "I2C transmit and receive failed");
  return ESP_OK;
}

//==============================================================================

TickType_t I2CController::GetTimeout() {
  LockGuard lg(*this);
  return timeout;
}

//==============================================================================

esp_err_t I2CController::SetTimeout(TickType_t timeout) {
  LockGuard lg(*this);
  this->timeout = timeout;
  return ESP_OK;
}

//==============================================================================

}