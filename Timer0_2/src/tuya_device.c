#include "bk_timer_pub.h"
#include "bk_timer.h"
#include "gpio_pub.h"

VOID timer_callback()
{ 
    bk_gpio_output_reverse(GPIO6);
    //Chệ độ auto_preload là mặc định
}

VOID app_init(VOID) 
{
    /* WiFi key, len initiation */
    timer_param_t config = {
    .channel = BKTIMER0,    // Timer_3     
    .div = 13,       //        
    .period = 1000000,    // Chu kỳ 1s         
    .t_Int_Handler = timer_callback // hàm ngắt
    };
    // Giá trị ghi vào thanh ghi được tính là value = period * 26 / div = 2000000
    
    gpio_config(GPIO6, GMODE_OUTPUT);
    gpio_output(GPIO6, 1); 
    bk_timer_ctrl(CMD_TIMER_INIT_PARAM_US, &config); // Cấu hình Timer3, chế độ us
    bk_timer_ctrl(CMD_TIMER_UNIT_ENABLE, BKTIMER0); // Khởi động Timer3
    return;
}