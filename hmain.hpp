#pragma once

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/i2c.h"
#include "hardware/uart.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"

#include "RedPicoLib/RedPicoLib.hpp"
#include "RedPicoLib/Devices/MLX90614.hpp"
// UART defines
// By default the stdout UART is `uart0`, so we will use the second one
#define UART_ID uart1
#define BAUD_RATE 115200

// Use pins 4 and 5 for UART1
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define UART_TX_PIN 4
#define UART_RX_PIN 5


constexpr float AMPLIFER_GAIN = -0.047;
constexpr float R_HEATER = 4.0f;
constexpr float VOLTAGE_DIVISON = 11.0f;
constexpr float ADC_CONVERSION_FACTOR = 3.3f / (1 << 12);


namespace INTERFACE
{
    constexpr auto I2C_IR = i2c1;
    constexpr uint8_t ADC_INPUT_CURRENT_SENSE = 0;
    constexpr uint8_t ADC_INPUT_VOLTAGE_SENSE = 1;
}
namespace PIN
{
    constexpr uint8_t PIN_IR_SDA = 2;
    constexpr uint8_t PIN_IR_SCL = 3;

    constexpr uint8_t PIN_HEATER = 8;
    constexpr uint8_t PIN_CURRENT_SENSE = 26;
    constexpr uint8_t PIN_VOLTAGE_SENSE = 27;
}
