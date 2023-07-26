#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_lcd.c>
unsigned int8 t0, tr, ch, dv;
void hienthi_lcd()
{
   tr = t0/100 +0x30;
   ch = t0/10%10 +0x30;
   dv = t0 % 10 +0x30;
   if (tr == 0x30)
   {
      tr = 0x20;
      
      if(ch == 0x30)
         ch = 0x20;
   }
   lcd_goto_xy(0,15);
   lcd_data(tr);
   lcd_data(ch);
   lcd_data(dv);
}
void main()
{
    set_up_port_ic_chot();
    setup_lcd();
    setup_timer_0(t0_ext_l_to_h | t0_div_1 | t0_8_bit);
    set_timer0(0);
    while (true)
    {
        t0 = get_timer0();
        xuat_4led_7doan_3so(ma7doan[t0 / 100],ma7doan[t0 / 10 % 10], ma7doan[t0 % 10]);
        lcd_goto_xy(0, 0);
        lcd_data("dem san pham");
        delay_us(20);
        hienthi_lcd();
        
        if (t0 >= 101)
            set_timer0(1);
    }
}
