#include "pl_i2c.h"

//==============================================================================

const i2c_port_num_t port = 0;
const gpio_num_t sdaPin = GPIO_NUM_5;
const gpio_num_t sclPin = GPIO_NUM_18;
const uint32_t sclFrequency = 100000;
const uint8_t targetAddress = 1;

//==============================================================================

extern "C" void app_main(void) {
  auto i2c = std::make_shared<PL::I2C>(port, sdaPin, sclPin, true);
  PL::I2CController controller(i2c, targetAddress, sclFrequency);

  controller.Initialize();

  uint8_t writeData[5] = {1, 2, 3, 4, 5};
  printf("Writing data:");
  for (int i = 0; i < sizeof(writeData) / sizeof(writeData[0]); i++)
    printf(" %d", writeData[i]);
  printf("\n");
  controller.Write(writeData, sizeof(writeData));

  uint8_t readData[5] = {};
  printf("Reading data:");
  controller.Read(readData, sizeof(readData));
  for (int i = 0; i < sizeof(readData) / sizeof(readData[0]); i++)
    printf(" %d", readData[i]);
  printf("\n");

  printf("Writing and reading data:\nWrite:");
  for (int i = 0; i < sizeof(writeData) / sizeof(writeData[0]); i++)
    printf(" %d", writeData[i]);
  printf("\nRead:");
  controller.WriteAndRead(writeData, sizeof(writeData), readData, sizeof(readData));
  for (int i = 0; i < sizeof(readData) / sizeof(readData[0]); i++)
    printf(" %d", readData[i]);
  printf("\n");
}