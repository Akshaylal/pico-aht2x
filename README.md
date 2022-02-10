# pico-aht2x

AHT21 sensor library for Raspberry Pi Pico and the pico-sdk.


## 1. Importing the library
* Clone this repo into your pico project
* Add this to your CMakeLists.txt

  ```cmake
    add_subdirectory(pico-aht2x)
    target_link_libraries(your_project_name
    pico_aht2x
    hardware_i2c)
  ```
* Import library in your code

  ```c++
    #include "pico-aht2x/aht2x.h"
    #include "hardware/i2c.h"
  ```
## 2. Basic usage
  ```c++
    i2c_init(i2c0, 1000000);
    
    gpio_set_function(16, GPIO_FUNC_I2C);
    gpio_set_function(17, GPIO_FUNC_I2C);
    gpio_pull_up(16);
    gpio_pull_up(17);

    AHT2x aht = AHT2x(I2C_PORT, 0x38);
    float t = aht.temperature();
    float h = aht.humidity();
  ```
