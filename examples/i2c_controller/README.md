# I2C Controller Example

1. I2C interface is initialized (port: 0, SDA pin: 5, SCL pin: 18, pull-up: enabled).
2. I2C controller is initialized (address: 1, frequency: 100 kHz).
3. 5 bytes are written to the target.
4. 5 bytes are read from the target.
4. 5 bytes are written and 5 bytes are read from the target in a single transaction.
