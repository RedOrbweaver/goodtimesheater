#include "hmain.hpp"


std::unique_ptr<MLX90614> ircam;


int main()
{
    stdio_init_all();
    // Set up our UART
    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    

    sleep_ms(10);
    ircam = std::make_unique<MLX90614>(I2C_PORT, I2C_SDA, I2C_SCL);
    sleep_ms(10);

    while(true)
    {
        int addr = 0x007;
        // uint8_t dt = ircam->read_register(addr);
        // printf("%i -> %i\n", addr, dt);

        const int sz = 4;
        uint8_t buf[sz] = {0};
        ircam->read_registers(addr, buf, sz);
        printf("%i (len: %i) -> (", addr, sz);
        for(int i = 0; i < sz; i++)
        {
            printf("%i", buf[i]);
            if(i != sz-1)
                printf(", ");
        }
        printf(")\n");

        sleep_ms(10);
        char ch = getchar_timeout_us(100000);
        if(ch == 's' || ch == 'S')
        {
            do
            {
                ch = getchar();
            }while(ch != 'r' && ch != 'R');
        }
    }    
    // while(true)
    // {
    //     printf("dumpign ram:\n");
    //     for(int i = 0; i < 0x1F; i++)
    //     {
    //         printf("%i -> %i\n", i, ircam->read_register(i));
    //     }
    //     printf("done\n");
    //     sleep_ms(1000);
    //     //clear_console();
    // }
    while(true);
}
