
#include <tv_pickit2_shift_1.c>
//! #include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_lcd.c>
#include <tv_pickit2_shift_key4x4_138.c>

//TIMER 
setup_timer_0(t0_ext_l_to_h | t0_div_1 | t0_8_bit);
set_timer0(0);

//NGAT TIMER
#int_timer1

void interrupt_timer1()
{
   bdn++;
   set_timer1 (3036) ;
}

    setup_timer_1 (t1_internal|t1_div_by_8) ;
    set_timer1 (3036) ;
    enable_interrupts (global) ;
    enable_interrupts (int_timer1) ;

//HIEN THI SO LON TREN LCD
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

//GHI SO LON 
    lcd_command (0x40) ;
    for (i = 0; i < 64; i++)
    {
       lcd_data (lcd_ma_8doan[i]) ;
    }
// DEM NGUOC 
// NHAN PHIM NGUOC
set_timer0(99 - get_timer0()); 

