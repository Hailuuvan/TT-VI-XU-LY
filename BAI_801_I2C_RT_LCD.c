
 #include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_ds1307_i2c.c>

void main()
{
   set_up_port_ic_chot();
   setup_lcd();
   lcd_command(lcd_addr_line1);
   lcd_data("clock:");
   doc_thoi_gian_tu_realtime();

   if (ma_ds13!=ma_ds)
   {
      thiet_lap_thoi_gian_hien_tai();
      nap_thoi_gian_htai_vao_ds13b07();
   }

   //thiet_lap_thoi_gian_hien_tai();
   //nap_thoi_gian_htai_vao_ds1307();
   doc_thoi_gian_tu_realtime();
   giaytam=giay_ds13;

   while(true)
   {
      doc_thoi_gian_tu_realtime();

      if (giaytam!=giay_ds13)
      {
         giaytam=giay_ds13;
         hien_thi_thoi_gian_ds13b07();
      }

      delay_ms(500);
   }
}

