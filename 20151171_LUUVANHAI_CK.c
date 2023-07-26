#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_ds18b20.c>
#include <tv_pickit2_shift_ds1307_i2c.c>
unsigned int8 j, solan=100;
unsigned int16 lm35a, ch_giay;
unsigned int16 kqadc, kc_int,tp_kc;
float k_cach,clk_cach;
signed int8 i,bdn;
int1 tt;
void phim_up()
{
   if (!input(bt2))
   {
      delay_ms(20);
      {
         if (!input(bt2))
         {
            tt =~ tt;
         }
         while(!input(bt2))
         hien_thi_8led_7doan_quet();
      }
   }
}
#int_timer1
void interrupt_timer1()
{
   bdn++;
   set_timer1 (3036);
}
void lcd_hienthi_so_z_toado_xy(signed int8 lcd_so, x1, y1)
{
   lcd_goto_xy(x1,y1);
   for (i=0;i<6;i++)
   {
      if (i==3) lcd_goto_xy(x1+1,y1);
      lcd_data(lcd_so_x[lcd_so][i]);
      hien_thi_8led_7doan_quet();
   }
}

void doc_ndo_ds18b20()
{
   if (touch_present ())
   doc_giatri_ds18b20 ();

   if (ds18al != ds18a_tam)
   {
      ds18a_tam = ds18al;
      ds18a = ds18a>>4;
      ds18a = ds18a&0x0ff;
   }
}

void GM_4led_7doan()
{
   xuat_4led_7doan_4so(ma7doan[nguyen/10],ma7doan[nguyen%10]&0x7f, ma7doan[tp/10],ma7doan[tp%10]);
}
void GM_LCD()
{
   lcd_hienthi_so_z_toado_xy(nguyen/10,0,0);
   lcd_hienthi_so_z_toado_xy(nguyen%10,0,3);
   lcd_goto_xy(1,6);
   lcd_data('.');
   lcd_data(tp/10 + 0x30);
   lcd_data(tp%10 + 0x30);
   
   // lcd
   lcd_goto_xy(0,11);
   lcd_data(giay_ds13/16 + 0x30);
   lcd_data(giay_ds13%16 + 0x30);
   lcd_data('.');
   lcd_goto_xy(1,11);
   lcd_data(0x20);
   lcd_data(0x20);
   lcd_data(0x20);
 
   lcd_hienthi_so_z_toado_xy(13,0,14);
   lcd_hienthi_so_z_toado_xy(14,0,17);
   //lcd_hienthi_so_z_toado_xy(nguyen%10,0,3);
}

void dao_gm_lcd()
{
   lcd_hienthi_so_z_toado_xy(nguyen/10,0,0);
   lcd_hienthi_so_z_toado_xy(nguyen%10,0,3);
   lcd_goto_xy(1,6);
   lcd_data('.');
   lcd_data(tp/10 + 0x30);
   lcd_data(tp%10 + 0x30);
   
   ch_giay = giay_ds13 / 16;
   lcd_goto_xy(0,18);
   lcd_data("E");
   lcd_data("L ");
   lcd_hienthi_so_z_toado_xy(ch_giay,0,11);
   lcd_hienthi_so_z_toado_xy(giay_ds13%16,0,14);
   lcd_goto_xy(0,17);
   lcd_data('.');
   lcd_goto_xy(1,17);
   lcd_data(0x20);
   lcd_data(0x20);
   lcd_data(0x20);
}

void GM_8led_quet()
{
   ch_giay = giay_ds13 /16 ;
   if(ch_giay == 0)
   led_7dq[1] = 0xff;
   
//!   tp_kc = k_cach*100;
   kc_int = (int16) (k_cach*100);
   led_7dq[0] = ma7doan[giay_ds13 % 16]&0x7f;
   led_7dq[1] = ma7doan[ch_giay]&0x7f;
  

   led_7dq[4] = ma7doan[kc_int % 10];
   led_7dq[5] = ma7doan[kc_int / 10 % 10];
   led_7dq[6] = ma7doan[kc_int / 100%10]&0x7f;
   led_7dq[7] = ma7doan[kc_int / 10000];
}

void dokhoangcach()
{
   set_adc_channel (2);
   hien_thi_8led_7doan_quet();
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

   //giai_ma_hienthi_4led (k_cach) ;
}
void ngat_lcd()
{
   if (bdn < 10)
      {
         lcd_command(lcd_shift_left);
      }
      else
      bdn = bdn - 10;
}
void main  ()
{
   set_up_port_ic_chot ();
   setup_lcd () ;
   setup_timer_1 (t1_internal|t1_div_by_8) ;
   set_timer1 (3036) ;
   enable_interrupts (global) ;
   enable_interrupts (int_timer1) ;
   bdn = 0;
   setup_adc (adc_clock_div_32);
   setup_adc_ports (an0_to_an1|vss_vdd);
   khoi_tao_ds18b20 ();
   ds18a_tam = 0;
      doc_thoi_gian_tu_realtime();
   if (ma_ds13!=ma_ds)
   {
      thiet_lap_thoi_gian_hien_tai();
      nap_thoi_gian_htai_vao_ds13b07();
   }


   giaytam=giay_ds13;
   lcd_command(0x40);
   for (i=0;i<64;i++) { lcd_data(lcd_ma_8doan[i]);
   hien_thi_8led_7doan_quet();}
//!   lcd_command(lcd_addr_line2); 
//!   lcd_data("LUU VAN HAI"); 
   tt =0;
   while(true)
   {
      doc_ndo_ds18b20();
      GM_4led_7doan();
      phim_up();
      if(tt == 0)
         GM_LCD();
      else if(tt == 1)
         dao_gm_lcd();
         
      dokhoangcach();
      //ngat_lcd();
      doc_thoi_gian_tu_realtime ();

//!      if (giaytam != giay_ds13)
//!      {
//!         giaytam = giay_ds13;
         GM_8led_quet();
         hien_thi_8led_7doan_quet();
//!      }
   }
}


