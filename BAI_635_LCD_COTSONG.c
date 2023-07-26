
//! #include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_lcd.c>
const unsigned char hang2[] = {0, 0, 0, 0, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F};
unsigned INT8 I;
void main()
{
   set_up_port_ic_chot();
   setup_lcd();
   lcd_command(0x40);
   for (i = 0; i < 16; i++)
      lcd_data(hang2[i]);
   lcd_goto_xy(0, 4);
   lcd_data(' ');
   lcd_data(' ');
   lcd_data(0);
   lcd_data(1);

   lcd_goto_xy(1, 4);
   lcd_data(0);
   lcd_data(1);
   lcd_data(1);
   lcd_data(1);
}
