
#include <tv_pickit2_shift_1_proteus.c>
// #include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_lcd.c>
#include <tv_pickit2_shift_key4x4_138.c>

signed int8 mp;

unsigned int8 tg;

void hien_thi_ban_dau()
{
   LCD_goto_XY(0, 0);
   lcd_data("DIEU KHIEN BUZZER");
   lcd_goto_xy(1, 0);
   delay_us(20);
   lcd_data("BUZZER: OFF");
   lcd_goto_xy(1, 11);
   delay_us(20);

   lcd_data(" , TG:");
}

void HT_LCD()
{
   lcd_goto_xy(1, 17);
   lcd_data(tg + 0x30);
}

void main()
{
   tg = 1;
   set_up_port_ic_chot();
   setup_lcd();
   hien_thi_ban_dau();
   set_tris_b(0x3c);
   while (true)
   {
      mp = key_4x4_dw();
      HT_LCD();
      if (mp != 0xff)
      {
         if (mp < 10)
         {
            tg = mp;
            HT_LCD();
         }
         if (mp == 10)
         {
            buzzer_on();
            lcd_goto_xy(1, 8);
            delay_us(20);
            lcd_data("ON ");
            //XUAT_32LED_DON_4BYTE(0xff,0xff,0xff,0xff);
            delay_ms(1000 * tg);
            buzzer_off();
            lcd_goto_xy(1, 8);
            delay_us(20);
            lcd_data("OFF");
            //XUAT_32LED_DON_4BYTE(0,0,0,0);
         }
      }
   }
}
