#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_lcd.c>
signed int8 gio, phut, giay, bdn, gia_tri_mod, dem_tg_exit = 0;
signed int8 ch_gio, dv_gio, ch_phut, dv_phut, ch_giay, dv_giay;
#int_timer1
void interrupt_timer1()
{
   bdn++;
   set_timer1(3036);
}
void giai_ma_lcd()
{
   dv_gio = gio % 10 + 0x30;
   ch_gio = gio / 10 + 0x30;

   dv_phut = phut % 10 + 0x30;
   ch_phut = phut / 10 + 0x30;

   dv_giay = giay % 10 + 0x30;
   ch_giay = giay / 10 + 0x30;
   
}
void hien_thi_lcd()
{
   LCD_GOTO_XY(0,0);
   delay_us(20);
   lcd_data(ch_gio);
   lcd_data(dv_gio);
   lcd_data(' ');
   lcd_data(ch_phut);
   lcd_data(dv_phut);
   lcd_data(' ');
   lcd_data(ch_giay);
   lcd_data(dv_giay);

}
void giai_ma_gan_cho_8led_quet()
{
   led_7dq[0] = ma7doan[giay % 10];
   led_7dq[1] = ma7doan[giay / 10];
   led_7dq[3] = ma7doan[phut % 10];
   led_7dq[4] = ma7doan[phut / 10];
   led_7dq[6] = ma7doan[gio % 10];
   led_7dq[7] = ma7doan[gio / 10];
   if (gia_tri_mod == 1)
      led_7dq[6] = led_7dq[6] & 0x7f;
   else if (gia_tri_mod == 2)
      led_7dq[3] = led_7dq[3] & 0x7f;
   else if (gia_tri_mod == 3)
      led_7dq[0] = led_7dq[0] & 0x7f;
}
void tat_2led_chinh()
{
   if (gia_tri_mod == 1)
   {
      led_7dq[7] = 0xff;
      led_7dq[6] = 0xff;
   }
   else if (gia_tri_mod == 2)
   {
      led_7dq[4] = 0xff;
      led_7dq[3] = 0xff;
   }
   else if (gia_tri_mod == 3)
   {
      led_7dq[1] = 0xff;
      led_7dq[0] = 0xff;
   }
}
void tat_2led_chinh_lcd()
{
   if (gia_tri_mod == 1)
   {
      dv_gio = ' ';
      ch_gio = ' ';
      hien_thi_lcd();
   }
   else if (gia_tri_mod == 2)
   {
      dv_phut = ' ';
      ch_phut = ' ';
      hien_thi_lcd();
   }
   else if (gia_tri_mod == 3)
   {
      dv_giay = ' ';
      ch_giay = ' ';
      hien_thi_lcd();
   }
}
// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void phim_mod()
{
   if (phim_bt1(200))
   {
      gia_tri_mod++;
      if (gia_tri_mod >= 4)
         gia_tri_mod = 0;
      dem_tg_exit = 0;
   }
   XUAT_4LED_7DOAN_GIAIMA_XOA_SO0(gia_tri_mod);
}
// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void phim_up()
{
   if (phim_bt0(200))
   {
      dem_tg_exit = 0;
      switch (gia_tri_mod)
      {
      case 1:
         if (gio == 23)
            gio = 0;
         else
            gio++;
         break;
      case 2:
         if (phut == 59)
            phut = 0;
         else
            phut++;
         break;
      case 3:
         if (giay == 59)
            giay = 0;
         else
            giay++;
         break;
      default:
         break;
      }
      giai_ma_gan_cho_8led_quet();
      giai_ma_lcd();
   }
}
// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void phim_dw()
{
   if (phim_bt2(200))
   {
      dem_tg_exit = 0;
      switch (gia_tri_mod)
      {
      case 1:
         if (gio == 0)
            gio = 23;
         else
            gio--;
         break;
      case 2:
         if (phut == 0)
            phut = 59;
         else
            phut--;
         break;
      case 3:
         if (giay == 0)
            giay = 59;
         else
            giay--;
         break;
      default:
         break;
      }
      giai_ma_gan_cho_8led_quet();
      giai_ma_lcd();
   }
}
// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void main()
{
   set_up_port_ic_chot();
   setup_timer_1(t1_internal | t1_div_by_8);
   set_timer1(3036);
   enable_interrupts(global);
   enable_interrupts(int_timer1);
   SETUP_LCD();
   giay = 0;
   phut = 0;
   gio = 0;
   gia_tri_mod = 0;
   ch_gio =0; dv_gio = 0; ch_phut= 0; dv_phut = 0; ch_giay = 0; dv_giay = 0;
   giai_ma_gan_cho_8led_quet();
   giai_ma_lcd();
   while (true)
   {
      if (bdn < 10)
      {
         if (gia_tri_mod != 0)
         {
            if ((bdn == 0) && (input(bt0)) && (input(bt2)))
            {
               tat_2led_chinh();
               tat_2led_chinh_lcd();
            }
            else if (bdn == 5)
            {
               giai_ma_gan_cho_8led_quet();
               giai_ma_lcd();
            }
         }
         hien_thi_8led_7doan_quet_all();
         hien_thi_lcd();
         phim_mod();
         phim_up();
         phim_dw();
      }
      else
      {
         bdn = bdn - 10;
         dem_tg_exit++;
         if (dem_tg_exit == 20)
            gia_tri_mod = 0;
         giay++;
         if (giay == 60)
         {
            giay = 0;
            phut++;
            if (phut == 60)
            {
               phut = 0;
               gio++;
               if (gio == 24)
                  gio = 0;
            }
         }
         giai_ma_gan_cho_8led_quet();
         giai_ma_lcd();
      }
   }
}
