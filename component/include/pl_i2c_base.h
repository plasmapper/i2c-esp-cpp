#pragma once
#include "pl_common.h"
#include "driver/i2c_master.h"

//==============================================================================

namespace PL {

//==============================================================================

/// @brief I2C class
class I2C : public Lockable {
  friend class I2CController;
  friend class I2CTarget;

public:
  /// @brief Creates an I2C
  /// @param port port number
  /// @param sdaPin SDA pin
  /// @param sclPin SCL pin
  /// @param enableInternalPullUp enable internal pull-up resistors (only for controller)
  I2C(i2c_port_num_t port, gpio_num_t sdaPin, gpio_num_t sclPin, bool enableInternalPullUp = false);
  ~I2C();
  I2C(const I2C&) = delete;
  I2C& operator=(const I2C&) = delete;
  
  esp_err_t Lock(TickType_t timeout = portMAX_DELAY) override;
  esp_err_t Unlock() override;

  /// @brief Initializes the I2C
  /// @return error code
  esp_err_t Initialize();

private:
  Mutex mutex;
  i2c_master_bus_handle_t controllerBusHandle = NULL;
  i2c_port_num_t port;
  gpio_num_t sdaPin, sclPin;
  bool enableInternalPullUp;
};

//==============================================================================

}