
//!#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_ds18b20.c>
#include <tv_pickit2_shift_ds1307_i2c.c>

unsigned int8 j, solan=100;

unsigned int16 lm35a;
unsigned int16 kqadc, ch_nguyen, kc_int;
float k_cach,clk_cach;
signed int8 i;

void lcd_hienthi_so_z_toado_xy(signed int8 lcd_so, x1, y1)
{
   lcd_goto_xy(x1,y1);
   for (i=0;i<6;i++)
   {
      if (i==3) lcd_goto_xy(x1+1,y1);
      lcd_data(lcd_so_x[lcd_so][i]);
   }
}
void giai_ma_hienthi_4led (float tam)
{
   unsigned int16 x;
   x = (unsigned int16) tam;
   xuat_4led_7doan_4so (ma7doan[lm35a / 10], ma7doan[lm35a % 10]&0x7f, ma7doan[x / 10], ma7doan[x % 10]);
   
}
void giai_ma_gan_cho_8led_quet()
{
   led_7dq[0] = ma7doan[giay_ds13 % 10];
   led_7dq[1] = ma7doan[giay_ds13 / 10];
   led_7dq[2] = 0xb9;
   led_7dq[3] = 0xc1;
   led_7dq[4] = ma7doan[tp%10];
   led_7dq[5] = ma7doan[tp/10 ];
   led_7dq[6] = ma7doan[nguyen % 10]&0x7f;
   led_7dq[7] = ma7doan[ch_nguyen];
   ch_nguyen=nguyen / 10; 
   if(ch_nguyen == 0)
   led_7dq[7] = 0xff;
}
void GM_hien_thi_lcd()
{
   kc_int = k_cach;
   lcd_goto_xy (0, 0) ;
   lcd_data (lm35a / 10 + 0x30);
   lcd_data (lm35a % 10 + 0x30);
   lcd_data (".") ;
   lcd_hienthi_so_z_toado_xy(kc_int/10,2,0);
   lcd_hienthi_so_z_toado_xy(kc_int%10,2,3);
   
   lcd_hienthi_so_z_toado_xy(giay_ds13/16,2,14);
   lcd_hienthi_so_z_toado_xy(giay_ds13%16,2,17);
   ch_nguyen = nguyen/10;
   if(ch_nguyen == 0)
   ch_nguyen = 10;
   lcd_hienthi_so_z_toado_xy(ch_nguyen,0,11);
   lcd_hienthi_so_z_toado_xy(nguyen%10,0,14);

   lcd_data(".");
   lcd_data(tp/ 10 + 0x30);
   lcd_data(tp%10 + 0x30);
   
}

void dokhoangcach()
{
   set_adc_channel (2);
   kqadc = 0;
   for (j = 0; j < 20; j++)
   {
      kqadc = kqadc + read_adc () ;
      //delay_ms (10);
      hien_thi_8led_7doan_quet();
     
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

void doc_nd_lm35a  ()
{
   set_adc_channel (0);
   lm35a = 0;
   for (j = 0; j < solan; j++)
   {
      lm35a = lm35a + read_adc () ;
      //delay_us (100);
      hien_thi_8led_7doan_quet();
   }

   lm35a = lm35a / 2.046;
   lm35a = lm35a / solan;
}

void GM_4led_7doan  ()
   {
   kc_int = k_cach;
   xuat_4led_7doan_4so (ma7doan[lm35a / 10], ma7doan[lm35a % 10]&0x7f, ma7doan[kc_int / 10], ma7doan[kc_int % 10]);
   }



void doc_ndo_ds18b20()
{
   if (touch_present () )
   doc_giatri_ds18b20 ();

   if (ds18al != ds18a_tam)
   {
      ds18a_tam = ds18al;
      ds18a = ds18a>>4;
      ds18a = ds18a&0x0ff;
   }
}




void main  ()
{
   set_up_port_ic_chot ();
   setup_lcd () ;
   setup_adc (adc_clock_div_32);
   setup_adc_ports (an0_to_an1|vss_vdd);
   khoi_tao_ds18b20 ();
   ds18a_tam = 0;
   doc_thoi_gian_tu_realtime ();

   if (ma_ds13 != ma_ds)
   {
      thiet_lap_thoi_gian_hien_tai () ;
      nap_thoi_gian_htai_vao_ds13b07 () ;
   }

   doc_thoi_gian_tu_realtime () ;
   giaytam = giay_ds13;
   lcd_command(0x40);
   for (i=0;i<64;i++) { lcd_data(lcd_ma_8doan[i]); }
   while (true)
   {
      //doc_thoi_gian_tu_realtime () ;
      DOC_GIAY_TU_REALTIME();
      dokhoangcach ();
      doc_nd_lm35a ();
      GM_4led_7doan ();
      doc_ndo_ds18b20 ();
      giai_ma_gan_cho_8led_quet ();
      hien_thi_8led_7doan_quet_all ();
      GM_hien_thi_lcd () ;
   }
}

