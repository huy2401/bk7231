#include "flash.h"
#include "gpio_pub.h"
#include "uart.h"

VOID UART_Receiver(){
    char buf[32];
    //bk_send_string(UART1_PORT,"\nsuccess\n");
    //flash_write(buf, 8,  0x1D1000);
   // for (int i = 0; i < 100; i++)
    
    flash_read(&buf, 8 , 0x00129000);
    bk_send_string(UART1_PORT, buf);
    flash_erase_sector(0x00129000);
    
}

VOID app_init(VOID) 
{
    /* WiFi key, len initiation */
    wifi_config_init();
    char data[8] = "12345678";
    uart1_init();
    uart_rx_callback_set(UART1_PORT, UART_Receiver,NULL);
    bk_send_string(UART1_PORT,"hello\n");
    flash_init();
    
    flash_write(data, 8, 0x00129000);
    gpio_config(GPIO6, GMODE_OUTPUT);
    gpio_output(GPIO6, 1);
}