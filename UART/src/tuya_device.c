#include "gpio_pub.h"
#include "uart.h"

VOID UART_Receiver()
{
    static char buf[20];
    static char len[20];
    for (int i = 0; i < 20; i++) {
        buf[i] = uart_read_byte(UART1_PORT);
        if (buf[i] == 13) break;
    }
    bk_send_string(UART1_PORT, buf);
}

    /* WiFi key, len initiation */
void app_init(void) 
{
    /* Cấu hình GPIO và PWM */
    gpio_config(GPIO7, GMODE_OUTPUT);
    gpio_output(GPIO7, 1);
    uart_config_t uart_config;
    uart1_init(); //Cấu hình uart1 theo mặc định
    uart_config.baud_rate = UART_BAUDRATE_115200;
    uart_config.data_width = DATA_WIDTH_8BIT;
    uart_config.flags =  false; //if set, UART can wake up MCU from stop mode
    uart_config.flow_control = FLOW_CTRL_DISABLED;
    uart_config.parity = BK_PARITY_NO;
    uart_config.stop_bits = BK_STOP_BITS_1;
    uart1_ctrl(CMD_UART_INIT, &uart_config);
    uart_rx_callback_set(UART1_PORT, UART_Receiver, NULL);
}