
#include <tv_pickit2_shift_1.c>
signed int8 pwm_capso;
unsigned int16 duty;

void phim_up()
{
   if (!input(up)&&(duty<1000))
   {
      delay_ms(20);
      if (!input(up))
      {
         duty= duty+50;
         set_pwm1_duty(duty);
         pwm_capso++;
         xuat_4led_7doan_giaima_xoa_so0(pwm_capso);
         delay_ms(200);
      }
   }
}

void phim_dw()
{
   if (!input(dw)&&(duty>0))
   {
      delay_ms(20);
      if (!input(dw))
      {
         duty= duty-50;
         pwm_capso--;
         xuat_4led_7doan_giaima_xoa_so0(pwm_capso);
         set_pwm1_duty(duty);
         delay_ms(200);
      }
   }
}

void main()
{
   set_up_port_ic_chot();
   dc_enable=1;
   output_low(pin_c1);
   xuat_buzzer_relay();
   setup_ccp1(ccp_pwm);
   setup_timer_2(t2_div_by_16,249,1);
   duty=0;
   pwm_capso=0;
   xuat_4led_7doan_giaima_xoa_so0(pwm_capso);
   set_pwm1_duty(duty);

   while(true)
   {
      phim_dw();
      phim_up();

      if(!input(stop))
      {
         duty=0;
         pwm_capso=0;
         xuat_4led_7doan_giaima_xoa_so0(pwm_capso);
         set_pwm1_duty(duty);
      }
   }
}

