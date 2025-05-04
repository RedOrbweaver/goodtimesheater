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

    

    sleep_ms(10);
    ircam = std::make_unique<MLX90614>(I2C_PORT, I2C_SDA, I2C_SCL);
    sleep_ms(10);
    printf("123\n");
    printf("emiss: %f\n", ircam->GetEmissivity());
    ircam->SetEmissivity(0.5);
    printf("emisschange: %f\n", ircam->GetEmissivity());
    while(true)
    {
        MLX90614::sensor_data data = ircam->GetData();
        float to0 = ircam->GetRelativeTemperatureSensor0();
        float to1 = ircam->GetRelativeTemperatureSensor1();
        float ta = ircam->GetTemperatureInternal();
        float ttrue = ircam->GetTrueTemperatureAveraged();

        printf("data -> (ta: %i, to0: %i, to1 %i)\n", data.ta, data.t0, data.t1);
        printf("to0 -> %.2f\n", to0);
        printf("to1 -> %.2f\n", to1);
        printf("ta -> %.2f\n", ta);
        printf("ttrue -> %.2f\n", ttrue);
        sleep_ms(500); 
        clear_console();
    }    
    while(true)
    {
        printf("dumpign ram:\n");
        for(int i = 0; i < 0x1F; i++)
        {
            printf("%i -> %i\n", i, ircam->read_register(i));
        }
        printf("done\n");
        sleep_ms(1000);
        //clear_console();
    }
    while(true);
}
