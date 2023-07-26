
#include <tv_pickit2_shift_1_proteus.c>
// #include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_lcd.c>

const unsigned char cotsong[] = {0, 0, 0, 0, 0x1F, 0x1F, 0x1F, 0x1F,0x1F,
                                 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F};

signed int8 i, j, k;

void giaima_cotsong()
{
   lcd_command(0x40);
   for (i = 0; i < 16; i++)
      lcd_data(cotsong[i]);
}

void hienthi_cotsong()
{
   lcd_goto_xy(0, j);
   lcd_data(0x20);
   lcd_data(0x20);
   lcd_data(0);
   lcd_data(1);
   lcd_goto_xy(1, j);
   lcd_data(0);
   lcd_data(1);
   lcd_data(1);
   lcd_data(1);
}

void main()
{
   set_up_port_ic_chot();
   setup_lcd();
   giaima_cotsong();
   while (true)
   {
      for (j = 0; j < 17; j++)
      {
         hienthi_cotsong();
         delay_ms(200);
         lcd_goto_xy(0, j);
         for (k = j; k < (j + 4); k++)
            lcd_data(0X20);
         lcd_goto_xy(1, j);
         for (k = j; k < (j + 4); k++)
            lcd_data(0X20);
      }

      for (j = 16; j > -1; j--)
      {
         hienthi_cotsong();
         delay_ms(200);
         lcd_goto_xy(0, j);
         for (k = j; k < (j + 4); k++)
            lcd_data(0X20);
         lcd_goto_xy(1, j);
         for (k = j; k < (j + 4); k++)
            lcd_data(0X20);
      }
   }
}
