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
    

    adc_init();

    adc_gpio_init(PIN::PIN_CURRENT_SENSE);
    adc_gpio_init(PIN::PIN_VOLTAGE_SENSE);

    init_out(PIN::PIN_HEATER, 0);


    ircam = std::make_unique<MLX90614>(INTERFACE::I2C_IR, PIN::PIN_IR_SDA, PIN::PIN_IR_SCL, 50000, 0);
    sleep_ms(10);

    ircam->SetMustSwitchFromPWM(true);
    

    // ircam->SetTOMin(27315); // 0°C
    // ircam->SetTOMax(65315); // 380°C

    // printf("TOMax %i\n", (int)ircam->GetTOMax());
    // printf("TOMin %i\n", (int)ircam->GetTOMin());

    // uint16_t max = ircam->GetTOMax();
    // uint16_t min = ircam->GetTOMin();
    // printf("max: %i, min: %i\n", max, min);

    // volatile MLX90614::config conf;
    // volatile MLX90614::pwmctrl pwm;
    // conf.value = ircam->ReadCTRLReg1();
    // pwm.value = ircam->ReadPWMCTRLReg();

    // printf("config: 0x%x\n", conf.value);
    // printf("pwmctrl: 0x%x\n", pwm.value);

    // pwm.value |= 0b10;
    // ircam->WritePWMCTRLReg(pwm.value);

    // conf.value = ircam->ReadCTRLReg1();
    // pwm.value = ircam->ReadPWMCTRLReg();

    // printf("config: 0x%x\n", conf.value);
    // printf("pwmctrl: 0x%x\n", pwm.value);

    ircam->StartReadingPWM(380.0f, 0.0f);

    float val = 0.0f;
    bool hasread = false;

    ircam->SetOnPWMMeasurement([&](float v)
    {
        val = v;
        hasread = true;
    });



    while(true)
    {

        bool heaton = (val < 50.0f) && val != 0.0f;
        printf("HEATER: %s\n", (heaton)?"ON":"OFF");
        printf("Temperature: %.3fC\n", val);
        
        gpio_put(PIN::PIN_HEATER, heaton);

        adc_select_input(INTERFACE::ADC_INPUT_CURRENT_SENSE);

        uint16_t current_raw = adc_read();
        float current_sense_v = float(current_raw)*ADC_CONVERSION_FACTOR;
        float voltage_drop = (current_sense_v)/-AMPLIFER_GAIN;
        float current = voltage_drop/R_HEATER;
        printf("current sense measured: %.3f\n", current_sense_v);
        printf("voltage drop: %.4f\n", voltage_drop);
        printf("current: %.3f\n", current);

        adc_select_input(INTERFACE::ADC_INPUT_VOLTAGE_SENSE);
        uint16_t voltage_raw = adc_read();
        float voltage_v = float(voltage_raw)*ADC_CONVERSION_FACTOR;
        float input_voltage = (voltage_v)*VOLTAGE_DIVISON;
        printf("input voltage sense: %.4f\n", voltage_v);
        printf("input voltage: %.3f\n", input_voltage);

        sleep_ms(400);
        clear_console();
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
