#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_lcd.c>
unsigned int8 btt;
float kcs1, kcs2, dien_tich;
#define trigger pin_e2
#define echo pin_e1

void phim_up()
{
   if (!input (up))
   {
      delay_ms (20) ;
      {
         if (!input (up))
         {
            btt++;
            if(btt == 3)
               btt = 0;
            
            while (!input (up));
         }
      }
   }
}

void tao_xung_trigger()
{
   delay_ms(10);
   output_high(trigger);
   delay_ms(10);
   output_low(trigger);
   set_timer1(0);
   while(!(input(echo)));
   setup_timer_1(t1_internal|t1_div_by_4);
   while(input(echo));
   kcs1 =get_timer1();
   kcs2 =get_timer1();
   setup_timer_1(t1_disabled );
}

void giai_ma_hienthi_lcd (float tam)
{
   unsigned int16 x;
   x = (unsigned int16) tam;
   //lcd_goto_xy (0, 0) ;
   lcd_data (x + 0x30) ;
}
void main()
{
   set_up_port_ic_chot();
   setup_timer_1(t1_disabled );
   setup_lcd();
   btt = 0;
   while(true)
   {
      tao_xung_trigger();   
      phim_up();
      xuat_4led_7doan_giaima_xoa_so0 (btt);
      if(btt == 0)
      {
         kcs1=kcs1*0.8;
         kcs1 = (kcs1/58);
         delay_ms(500);
         lcd_goto_xy(0,0);
         giai_ma_hienthi_lcd (kcs1);
      }
      else if(btt == 1)
      {
         kcs2=kcs2*0.8;
         kcs2 = (kcs2/58);
         delay_ms(500);
         lcd_goto_xy(1,0);
         giai_ma_hienthi_lcd (kcs2);
      }  
      else if(btt == 2)
      {
         lcd_goto_xy(2,0);
         dien_tich = kcs1*kcs2;
         giai_ma_hienthi_lcd (dien_tich);
      }
      if(!input(bt1))
         lcd_command(0x01);
   }
}

