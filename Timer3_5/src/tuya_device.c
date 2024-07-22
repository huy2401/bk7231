#include "bk_timer_pub.h"
#include "bk_timer.h"
#include "gpio_pub.h"

VOID timer_callback()
{ 
    static bool FLAG = false;
    gpio_output(GPIO6, FLAG); // Đảo chân GPIO6
    FLAG = !FLAG; 
}

VOID app_init(VOID) 
{
    /* WiFi key, len initiation */
    timer_param_t config = {
    .channel = BKTIMER3,    // Timer_3     
    .div = 16,       //        
    .period = 1000,    // Chu kỳ 1s         
    .t_Int_Handler = timer_callback // hàm ngắt
    };
    // Giá trị ghi vào thanh ghi được tính là value = period * 32 / div = 2000
    
    gpio_config(GPIO6, GMODE_OUTPUT);
    gpio_output(GPIO6, 1); 
    bk_timer_ctrl(CMD_TIMER_INIT_PARAM, &config); // Cấu hình Timer3
    bk_timer_ctrl(CMD_TIMER_UNIT_ENABLE, BKTIMER3); // Khởi động Timer3
    return;
}