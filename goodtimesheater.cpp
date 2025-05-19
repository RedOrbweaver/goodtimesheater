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
    
    ircam = std::make_unique<MLX90614>(I2C_PORT, I2C_SDA, I2C_SCL, 50000, 0);
    sleep_ms(10);

    ircam->SetMustSwitchFromPWM(true);
    // uint16_t max = ircam->GetTOMax();
    // uint16_t min = ircam->GetTOMin();
    // printf("max: %i, min: %i\n", max, min);

    // volatile MLX90614::config conf;
    // volatile MLX90614::pwmctrl pwm;
    // conf.value = ircam->ReadCTRLReg1();
    // pwm.value = ircam->ReadPWMCTRLReg();

    // printf("config: 0x%x\n", conf.value);
    // printf("pwmctrl: 0x%x\n", pwm.value);

    ircam->StartReadingPWM(380.0f, 0.0f);

    float val;
    bool hasread = false;

    ircam->SetOnPWMMeasurement([&](float v)
    {
        val = v;
        hasread = true;
    });

    while(true)
    {
        if(hasread)
        {
            printf("Reading: %.3fC\n", val);
            hasread = false;
        }
        sleep_ms(10);
    }

    init_in(I2C_SDA);
    init_out(I2C_SCL, true);

    while(true)
    {
        printf("%i\n", gpio_get(I2C_SDA));
        sleep_ms(10);
    }

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
        // conf.value = ircam->ReadCTRLReg1();
        // pwm.value = ircam->ReadPWMCTRLReg();
        // printf("config: 0x%x\n", conf.value);
        // printf("pwmctrl: 0x%x\n", pwm.value);
        // printf("max: %i, min: %i\n", ircam->GetTOMax(), ircam->GetTOMin());

        // uint16_t t0 = ircam->ReadTO0();
        // uint16_t t1 = ircam->ReadTO1();
        // uint16_t ta = ircam->ReadTO1();
        // float ft0 = ircam->ConvertTO(t0);
        // float ft1 = ircam->ConvertTO(t1);
        // float fta = ircam->ConvertTA(ta);
        // //ircam->IncAddr();
        // printf("t0: %i 0x%x %.3f\n", t0, t0, ft0);
        // printf("t1: %i 0x%x %.3f\n", t1, t1, ft1);
        // printf("ta: %i 0x%x %.3f\n", ta, ta, fta);
        // printf("%i\n", ircam->GetAddress());
        // if(t0 != 25)
        // {
        //     __breakpoint();
        //     while(true);
        // }
        sleep_ms(1500); 
        clear_console();
    }
    while(true);
}
