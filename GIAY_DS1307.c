
#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_ds1307_i2c.c> 
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

void hien_thi()
{
   lcd_hienthi_so_z_toado_xy(giay_ds13 /16, 0, 0);
   lcd_hienthi_so_z_toado_xy(giay_ds13 %16, 0, 3);
}
void main()
{
   set_up_port_ic_chot ();
   setup_lcd () ;
   setup_timer_1 (t1_internal|t1_div_by_8) ;
   set_timer1 (3036) ;
   enable_interrupts (global) ;
   enable_interrupts (int_timer1) ;
//!   bdn = 0;
   setup_adc (adc_clock_div_32);
   setup_adc_ports (an0_to_an1|vss_vdd);
//!   khoi_tao_ds18b20 ();
//!   ds18a_tam = 0;
      doc_thoi_gian_tu_realtime();
   if (ma_ds13!=ma_ds)
   {
      thiet_lap_thoi_gian_hien_tai();
      nap_thoi_gian_htai_vao_ds13b07();
   }


   giaytam=giay_ds13;
   lcd_command(0x40);
   for (i=0;i<64;i++) { lcd_data(lcd_ma_8doan[i]); }
   

   while (true)
   {
      doc_thoi_gian_tu_realtime ();

      if (giaytam != giay_ds13)
      {
         giaytam = giay_ds13;
         hien_thi();
      }
      
   }
}

