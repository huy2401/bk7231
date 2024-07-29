#include "bk_timer_pub.h"
#include "bk_timer.h"
#include "gpio_pub.h"
#include "pwm_new.h"
#include "pwm_pub.h"

VOID pwm_callback()
{
    bk_gpio_output_reverse(GPIO7);
}

VOID app_init(VOID) 
{
    /* WiFi key, len initiation */
    gpio_config(GPIO7, GMODE_OUTPUT); 
    gpio_output(GPIO7, 1);
    pwm_param_t config;
    config.channel = PWM0; //Chọn PWM channel0, tương đương với P6 
    config.p_Int_Handler = pwm_callback; // Hàm xử lý ngắt
    config.cfg.bits.clk = 0; // PWM clock 32KHz, nếu chọn 1 thì sẽ chọn clock 26Mhz
    config.cfg.bits.en = 1; //Enable PWM
    config.cfg.bits.mode = 1; //PWM mode
    config.cfg.bits.int_en = 1;//Bật ngắt
    config.end_value = 64000; // Chu kỳ 2s
    config.duty_cycle1 = 16000; //Thay đổi xung tại 0.5s
    config.duty_cycle2 = 32000; // Thay đổi xung tại 1s
    config.duty_cycle3 = 48000; // Thay đổi xung tại 1.5s
    init_pwm_param(&config, true); // Cấu hình PWM
    pwm_init_levl_set_high(PWM0); // Bắt đầu PWM với tích cực cao
    pwm_unit_enable(PWM0); // Khởi động PWM
}