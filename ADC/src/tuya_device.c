#include "gpio_pub.h"
#include "uart.h"
#include "saradc_pub.h"
#include "arm_arch.h"
#include "/home/huy/tuya/platforms/bk7231n/bk7231n_os/beken378/driver/saradc/saradc.h"

 saradc_desc_t adc_config;

VOID callback() // Sau khi đo 32 lần, adc sẽ dừng lại và gọi hàm này
{
    char buf[16];
    bk_send_string(UART1_PORT, "SUCCESS\n");
    for (int i = 0; i < 32; i++)
    {
        sprintf(buf,"%.2f",saradc_calculate(adc_config.pData[i])); // Ghi tất cả các kết quả đo được ra màn hình
        bk_send_string(UART1_PORT, buf);
        bk_send_string(UART1_PORT, "\n");
    }
    
}

    /* WiFi key, len initiation */
void app_init(void) {
    // Các cấu hình khác ở đây...

    saradc_init();
    saradc_config_param_init(&adc_config);
    adc_config.channel = 3; // Channel 3, tương ứng chân p32
    adc_config.data_buff_size = 32; // Số lần đo mỗi lần kích hoạt

    // Khai báo một mảng data dùng cho lưu trữ dữ liệu ADC
    UINT32 data[100];
    adc_config.pData = data;  // Gán con trỏ pData của adc_config vào mảng data
    adc_config.p_Int_Handler = callback; // Gọi hàm ngắt
    char buf[17];
    sprintf(buf, "%d", saradc_open(&adc_config));  // Kích hoạt adc

    bk_send_string(UART1_PORT, buf);
    
    // Vòng lặp chính của ứng dụng
    while (1) {
        // Các hoạt động khác ở đây...
    }
}