
#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_lcd.c>

const unsigned char hang2[]=
{
         //trai tim                          thoi                                            
   0x0a,0x15,0x11,0x11,0x0a,0x04,0,0,  0x04,0x0a,0x11,0x11,0x0a,0x04,0,0,  0x1f,0x11
      //vuong
   0x11,0x11,0x11,0x1f,0,0

};

signed int8 i;

void main()
{
   set_up_port_ic_chot ();
   setup_lcd ();
   lcd_goto_xy (0, 0) ;
   lcd_data (" HIEN THI 3 KY TU ");
   lcd_command (0x40);
   for (i = 0; i < 32; i++) { lcd_data (hang2[i]); }
   
   lcd_goto_xy (1, 0) ;
   lcd_data (0);
   lcd_data (1) ;
   lcd_data (2) ;
   while (true);
}

