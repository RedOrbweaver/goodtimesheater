#include "hmain.hpp"


std::unique_ptr<MLX90614> ircam;


int main()
{
    stdio_init_all();


    // Set up our UART
    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    printf("starting goodtimesheater...\n");

    StartupLEDEffect();
    
    ircam = std::make_unique<MLX90614>(I2C_PORT, I2C_SDA, I2C_SCL);
    sleep_ms(10);

    volatile MLX90614::config conf;

    conf.value = ircam->ReadCTRLReg1();

    printf("config: %i\n", conf.value);

    while(true)
    {
        // MLX90614::sensor_data data = ircam->GetData();
        // //__breakpoint();
        // float to0 = ircam->GetRelativeTemperatureSensor0();
        // //__breakpoint();
        // float to1 = ircam->GetRelativeTemperatureSensor1();
        // float ta = ircam->GetTemperatureInternal();
        // float ttrue = ircam->GetTrueTemperatureAveraged();
        // float emiss = ircam->GetEmissivity();

        // printf("emiss: %.3f\n", emiss);
        // printf("data -> (ta: %i, to0: %i, to1 %i)\n", data.ta, data.t0, data.t1);
        // printf("to0 -> %.2f\n", to0);
        // printf("to1 -> %.2f\n", to1);
        // printf("ta -> %.2f\n", ta);
        // printf("ttrue -> %.2f\n", ttrue);
        uint16_t v = ircam->ReadTO0();
        float f = ircam->ConvertTO(v);
        printf("%i 0x%x %.3f", v, v, f);
        //float to0 = ircam->GetRelativeTemperatureSensor0();
        sleep_ms(1500); 
        clear_console();
    }
    while(true);
}
