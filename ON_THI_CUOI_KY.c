
#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_ds18b20.c>
//#include <tv_pickit2_shift_lcd.c>
#include <tv_pickit2_shift_ds1307_i2c.c>

signed int8 bdn, j;
unsigned int16 kqadc;
float k_cach,clk_cach;
unsigned int16 lm35a, solan = 100;
signed int8 i;

#int_timer1
void interrupt_timer1()
{
   bdn++;
   set_timer1 (3036);
}

void lcd_hienthi_so_z_toado_xy(signed int8 lcd_so, x1, y1)
{
   lcd_goto_xy (x1, y1) ;
   for (i = 0; i < 6; i++)
   {
      if (i == 3) lcd_goto_xy (x1 + 1, y1);
      lcd_data (lcd_so_x[lcd_so][i]);
   }
}

void hien_thi_lcd()
{
   lcd_hienthi_so_z_toado_xy (nguyen / 10, 0, 11);
   lcd_hienthi_so_z_toado_xy (nguyen % 10, 0, 14);
   lcd_hienthi_so_z_toado_xy (tp, 0, 17) ;
   lcd_goto_xy (0, 0) ;
   lcd_data (lm35a % 10 + 0x30);
   lcd_goto_xy (1, 0) ;
   lcd_data (lm35a / 10 + 0x30);
}

void doc_ndo_ds18b20()
{
   if (touch_present () )
   doc_giatri_ds18b20 ();

   if (ds18al != ds18a_tam)
   {
      ds18a_tam = ds18al;
      ds18a = ds18a >> 4;
      tp = (nguyen&0x000f) * 10 / 16;
      ds18a = ds18a&0x0ff;
      nguyen = ds18a;
   }
}

unsigned int8 hieu_chinh_so_bcd_tang(unsigned int8 x)
{
   unsigned int8 y;
   y = x;
   x = x&0x0f;

   if (x == 0x0a)
      y = y + 6;

   return (y);
}

unsigned int8 hieu_chinh_so_bcd_giam(unsigned int8 x)
{
   unsigned int8 y;
   y = x;
   x = x&0x0f;

   if (x == 0x0f)
      y = y - 6;

   return (y);
}

void luu_giai_ma_hien_thi_sau_khi_chinh()
{
   nap_thoi_gian_htai_vao_ds13b07 ();
}

void phim_up()
{
   if (!input (up))
   {
      delay_ms (20);

      if (!input (up))
      {
         if (thu_ds13 == 0x07)
            thu_ds13 = 0;

         else
         {
            thu_ds13++;
            thu_ds13 = hieu_chinh_so_bcd_tang (thu_ds13);
         }
         luu_giai_ma_hien_thi_sau_khi_chinh ();
      }
   }
}

void phim_dw()
{
   if (!input (dw))
   {
      delay_ms (20);

      if (!input (dw))
      {
         if (thu_ds13 == 0x07)
            thu_ds13 = 0;

         else
         {
            thu_ds13--;
            thu_ds13 = hieu_chinh_so_bcd_tang (thu_ds13);
         }

         luu_giai_ma_hien_thi_sau_khi_chinh ();
      }
   }
}

void giai_ma_gan_cho_8led_quet()
{
   led_7dq[0] = ma7doan[giay_ds13 % 10];
   led_7dq[1] = ma7doan[giay_ds13 / 10];
   led_7dq[2] = ma7doan[thu_ds13 % 10];
   led_7dq[3] = ma7doan[tp];
   led_7dq[4] = ma7doan[nguyen % 10]&0x7f;
   led_7dq[5] = ma7doan[nguyen / 10];
   led_7dq[6] = ma7doan[lm35a % 10];
   led_7dq[7] = ma7doan[lm35a / 10];
}

void doc_nd_lm35a()
{
   set_adc_channel (0);
   lm35a = 0;
   for (j = 0; j < solan; j++)
   {
      lm35a = lm35a + read_adc () ;
      delay_us (100);
   }

   lm35a = lm35a / 2.046;
   lm35a = lm35a / solan;
}

void giai_ma_hienthi_4led (float tam)
{
   unsigned int16 x;
   x = (unsigned int16) tam;
   xuat_4led_7doan_giaima_xoa_so0 (x) ;
   
   lcd_goto_xy(2,0);
   lcd_data(x/10 + 0x30);
   lcd_data(x%10 + 0x30);
   lcd_data(' ');
   lcd_data(giay_ds13/10 + 0x30);
   lcd_data(giay_ds13%10 + 0x30);
}

void dokhoangcach()
{
   set_adc_channel (2);
   kqadc = 0;
   for (j = 0; j < 20; j++)
   {
      kqadc = kqadc + read_adc () ;
      delay_ms (10);
   }

   kqadc = kqadc / 20;
   if (kqadc <= 80) k_cach = 80;

   else if ((kqadc > 80) && (kqadc < 87))
   {
      clk_cach = kqadc - 80;
      k_cach = 80 - clk_cach / 0.77;
   }

   else if (kqadc == 87) k_cach = 70;

   else if ((kqadc > 87) && (kqadc < 106))
   {
      clk_cach = kqadc - 87;
      k_cach = 70 - clk_cach / 2.11;
   }

   else if (kqadc == 106) k_cach = 60;

   else if ((kqadc > 106) && (kqadc < 124))
   {
      clk_cach = kqadc - 106;
      k_cach = 60 - clk_cach / 2;
   }

   else if (kqadc == 124) k_cach = 50;

   else if ((kqadc>124) &&(kqadc<150))
   {
      clk_cach = kqadc-124;
      k_cach=50 - clk_cach/2.88;
   }

   else if (kqadc==150) k_cach=40;

   else if ((kqadc>150) &&(kqadc<196))
   {
      clk_cach = kqadc-150;
      k_cach=40 - clk_cach/5.11;
   }

   else if (kqadc==196) k_cach=30;

   else if ((kqadc>196) &&(kqadc<276))
   {
      clk_cach = kqadc-196;
      k_cach=30 - clk_cach/8.88;
   }

   else if (kqadc==276) k_cach=20;

   else if ((kqadc>276) &&(kqadc<490))
   {
      clk_cach = kqadc-276;
      k_cach=20 - clk_cach/23.77;
   }

   else if (kqadc==490) k_cach=10;

   giai_ma_hienthi_4led (k_cach) ;
}
void nhapnhay()
{
   if (k_cach > 30)
   {
      if (bdn < 10)
      {
         if (bdn < 5)
            giai_ma_hienthi_4led (k_cach);

         else if (bdn < 10)
            xuat_4led_7doan_4so (0xff, 0xff, 0xff, 0xff) ;
      }

      else
      bdn = bdn - 10;
   }

   else
   giai_ma_hienthi_4led (k_cach) ;
}
void main()
{
   set_up_port_ic_chot ();
   setup_adc (adc_clock_div_32);
   setup_adc_ports (an0_to_an2|vss_vdd);
   setup_lcd ();
   setup_timer_1 (t1_internal|t1_div_by_8) ;
   set_timer1 (3036) ;
   enable_interrupts (global) ;
   enable_interrupts (int_timer1) ;
   bdn = 0;
   khoi_tao_ds18b20 ();
   doc_thoi_gian_tu_realtime ();

   lcd_command (0x40);
   for (i = 0; i < 64; i++) { lcd_data (lcd_ma_8doan[i]); }
   if (ma_ds13 != ma_ds)
   {
      thiet_lap_thoi_gian_hien_tai ();
      nap_thoi_gian_htai_vao_ds13b07 ();
   }

   ds18a_tam = 0;

   while (true)
   {
      doc_nd_lm35a ();
      doc_ndo_ds18b20 ();
      giai_ma_gan_cho_8led_quet ();
      hien_thi_8led_7doan_quet_all ();
      doc_thoi_gian_tu_realtime ();
      DOC_GIAY_TU_REALTIME();
      
      giaytam = giay_ds13;
      hien_thi_8led_7doan_quet ();
      hien_thi_lcd ();

      dokhoangcach () ;
      nhapnhay();
      
      hien_thi_lcd ();
      phim_up ();
      phim_dw ();
   }
}

