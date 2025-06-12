# esp32_gpio

GPIO driver reference for ESP32

## Summary

Used for development & validation of ESP32 GPIO driver

- Din

- Dout

- Dint

## Hardware

- Current: ESP32-S3

## Source

* [esp32_base](https://github.com/ErisdarDemo/esp32_base/tree/v1) 'v1'

# Project Organization

- appl\ - Application

- lbr\ - Library Content

- core\mcu - Microcontroller Access & Drivers

- core\rtos - FreeRTOS contents with calls to appl\ for application operations

- core\system - Application setup & configure

# Opens

- Integrate & capture reference demo README content

# Version History

- v0.1 - gpio read()

- v0.2 - gpio write()

- v0.3 - gpio interrupt()

- v0.4 - gpio wakeup()

- v1.0 - C GPIO driver release

- _(pending)_ v1.1 - Driver unit test support