
//!#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_lcd.c>
#include <tv_pickit2_shift_key4x4_138.c>

signed int8 mp;
unsigned int8 array[81]={};
unsigned int8 i,hang;

void GM_LCD()
{
   if (mp < 10) array[0] = mp + 0x30;
   else array[0] = mp + 0x37;
   for (i = 80; i > 0; i--)
      array[i] = array[i - 1];
}

void HT_LCD()
{
   for (hang = 0; hang < 4; hang++)
   {
      LCD_goto_XY (hang, 0) ;
      for (i = 20; i > 0; i--)
         LCD_DATA (array[i + (hang * 20)]);
   }
}

void main()
{
   set_up_port_ic_chot ();
   setup_lcd () ;

   while (true)
   {
      mp = key_4x4_dw ();

      if (mp != 0xff)
      {
         GM_LCD () ;
         HT_LCD () ;
      }
   }
}

