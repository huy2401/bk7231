#include "gpio_pub.h"
#include "gpio.h"

VOID GPIO_callback_7()
{
    bk_gpio_output_reverse(GPIO6); // Đảo ngược P6 mỗi khi có ngắt cạnh lên ở P7
}

VOID app_init(VOID) 
{
    /* WiFi key, len initiation */
    gpio_config(GPIO6, GMODE_OUTPUT); //Cấu hình chân 6 chế độ ngõ ra
    gpio_output(GPIO6, 1); // Chân P6 tích cực cao
    gpio_config(GPIO7, GMODE_INPUT_PULLDOWN); //Cấu hình chân 7 trở kéo lên
    gpio_input(GPIO7);// Đọc giá trị của chân 7
    gpio_int_enable(GPIO7, GPIO_INT_LEVEL_RISING, GPIO_callback_7); // Cấu hình chân 7 ngắt cạnh lên
    return;
}