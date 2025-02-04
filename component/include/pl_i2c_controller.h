#pragma once
#include "pl_i2c_base.h"

//==============================================================================

namespace PL {

//==============================================================================

/// @brief I2C controller class
class I2CController : public Lockable {
public:
  /// @brief Default operation timeout in FreeRTOS ticks
  static const TickType_t defaultTimeout = 2;

  /// @brief Creates an I2C controller
  /// @param i2c I2C interface
  /// @param targetAddress target address
  /// @param sclFrequency SCL frequency in Hz
  I2CController(std::shared_ptr<I2C> i2c, uint8_t targetAddress, uint32_t sclFrequency);
  ~I2CController();
  I2CController(const I2CController&) = delete;
  I2CController& operator=(const I2CController&) = delete;
  
  esp_err_t Lock(TickType_t timeout = portMAX_DELAY) override;
  esp_err_t Unlock() override;

  /// @brief Initializes the controller
  /// @return error code
  esp_err_t Initialize();

  /// @brief Reads the data from the I2C target
  /// @param dest destination
  /// @param size number of bytes to read
  /// @return error code
  esp_err_t Read(void* dest, size_t size);

  /// @brief Writes the data to the I2C target
  /// @param src source
  /// @param size number of bytes to write
  /// @return error code
  esp_err_t Write(const void* src, size_t size);

  /// @brief Writes the data to the I2C target and reads the data from the I2C target in a single transaction
  /// @param src write data source
  /// @param size number of bytes to write
  /// @param src read data destination
  /// @param size number of bytes to read
  /// @return error code
  esp_err_t WriteAndRead(const void* src, size_t srcSize, void* dest, size_t destSize);

  /// @brief Gets the operation timeout 
  /// @return timeout in FreeRTOS ticks
  TickType_t GetTimeout();

  /// @brief Sets the operation timeout 
  /// @param timeout timeout in FreeRTOS ticks
  /// @return error code
  esp_err_t SetTimeout(TickType_t timeout);

private:
  Mutex mutex;
  std::shared_ptr<I2C> i2c;
  uint8_t targetAddress;
  uint32_t sclFrequency;
  i2c_master_dev_handle_t deviceHandle = NULL;
  TickType_t timeout = defaultTimeout;
};

//==============================================================================

}