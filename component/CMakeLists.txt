cmake_minimum_required(VERSION 3.5)

idf_component_register(SRCS "pl_i2c_base.cpp" "pl_i2c_controller.cpp" INCLUDE_DIRS "include" REQUIRES "esp_driver_i2c" "pl_common")