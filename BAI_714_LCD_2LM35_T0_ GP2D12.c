
 #include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_lcd.c>
#include <math.h>

unsigned int16 kqadc;
float k_cach;
unsigned int8 j, t0, solan = 100;
unsigned int16 lm35a, lm35b, ch_a, dv_a, ch_b, dv_b,ch_lcd, dv_lcd;


#define nd_tren 40
#define nd_duoi 35

int doc_nd_lm35a()
{
   set_adc_channel (0) ;
   lm35a = 0;
   for (j = 0; j < solan; j++)
   {
      lm35a = lm35a + read_adc ();
      delay_us (100) ;
   }

   lm35a = lm35a / 2.046;
   lm35a = lm35a / solan;
   return lm35a;
}

void doc_nd_lm35b()
{
   set_adc_channel (1) ;
   lm35b = 0;
   for (j = 0; j < solan; j++)
   {
      lm35b = lm35b + read_adc ();
      delay_us (100) ;
   }

   lm35b = lm35b / 2.046;
   lm35b = lm35b / solan;
}

void do_khoang_cach()
{
   set_adc_channel (2);
   kqadc = read_adc ();
   delay_ms (40);
   k_cach = pow (4277 / kqadc, 1.106) ;
   if (k_cach > 80) k_cach = 80;
}

void hienthi_lcd()
{
   
   ch_a = lm35a / 10 ;
   dv_a = lm35a % 10;

   //xoa so 0 vn
   if (ch_a == 0)
      ch_a = 10;

   lcd_goto_xy (0, 0) ;
   lcd_data ("LM35A:") ;
   lcd_goto_xy (0, 7) ;
   lcd_data (ch_a + 0x30);
   lcd_data (dv_a + 0x30);
   
   ch_b = lm35b / 10 ;
   dv_b = lm35b % 10;

   //xoa so 0 vn
   if (ch_b == 0)
      ch_b = 10;

   lcd_goto_xy (0, 11) ;
   lcd_data ("LM35B:") ;
   lcd_data (ch_b + 0x30);
   lcd_data (dv_b + 0x30);
   
   // giai ma do khoang cach
   lcd_goto_xy (2, 0) ;
   lcd_data ("GP2D12:") ;
   lcd_data ((unsigned int16) k_cach + 0x30);
   
   //giai ma hien thi counter
   lcd_goto_xy (1, 0) ;
   lcd_data ("counter:") ;
   lcd_goto_xy (1, 10) ;
   ch_lcd = t0 /10;
   dv_lcd = t0%10;
   if(ch_lcd == 0)
      ch_lcd = -0x10; 
   lcd_data (ch_lcd + 0x30);
   lcd_data (dv_lcd + 0x30);
}

void main()
{
   set_up_port_ic_chot () ;
   setup_adc (adc_clock_div_32) ;
   setup_adc_ports (an0_to_an1|vss_vdd) ;
   setup_adc_ports (an0_to_an2|vss_vdd);
   
   SETUP_LCD () ;
   setup_timer_0 (t0_ext_l_to_h | t0_div_1|t0_8_bit); 
   set_timer0(0); 
   
   while (true)
   {
      doc_nd_lm35a () ;
      doc_nd_lm35b () ;
      hienthi_lcd () ;
      do_khoang_cach () ;
      t0=get_timer0();
      if (t0>=101) 
         set_timer0(1);
   }

}

