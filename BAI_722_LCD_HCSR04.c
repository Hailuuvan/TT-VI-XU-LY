
#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_lcd.c>

#define trigger pin_e2
#define echo pin_e1
unsigned int8 i;
float kcs;

void lcd_hienthi_so_z_toado_xy(signed int8 lcd_so, x1, y1)
{
   lcd_goto_xy (x1, y1);
   for (i = 0; i < 6; i++)
   {
      if (i == 3)
         lcd_goto_xy (x1 + 1, y1);

      lcd_data (lcd_so_x[lcd_so][i]) ;
   }
}

void giai_ma_hienthi_lcd (float tam)
{
   unsigned int16 x;
   x = (unsigned int16) tam;
   lcd_goto_xy (0, 0) ;
   lcd_data (x) ;
}

void tao_xung_trigger()
{
   delay_ms (10) ;
   output_high (trigger) ;
   delay_ms (10) ;
   output_low (trigger) ;
   set_timer1 (0) ;
   while ( ! (input (echo)));
   setup_timer_1 (t1_internal|t1_div_by_4) ;
   while (input (echo)) ;
   kcs = get_timer1 ();
   setup_timer_1 (t1_disabled) ;
}


void main()
{
   set_up_port_ic_chot () ;
   setup_timer_1 (t1_disabled) ;
   giai_ma_hienthi_lcd (kcs) ;
   //setup_adc (adc_clock_div_32) ;
   //setup_adc_ports (an0|vss_vdd) ;
   set_adc_channel (0) ;
   SETUP_LCD () ;
   //ttqn = 0;
   lcd_command (0x40) ;
   for (i = 0; i < 64; i++)
   {
      lcd_data (lcd_ma_8doan[i]) ;
   }

   while (true)
   {
      tao_xung_trigger () ;
      kcs = kcs * 0.8;
      kcs = (kcs / 58);
      giai_ma_hienthi_lcd (kcs) ;
      delay_ms (500) ;
   }
}

