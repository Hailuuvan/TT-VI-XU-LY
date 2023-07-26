
#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_ds18b20.c>
unsigned int16 ch_ds, dv_ds, ch_a, dv_a, lm35a;
unsigned int8 j, solan = 100 ;
void do_nhietdo_ds18b20()
{
   if (touch_present () )
      doc_giatri_ds18b20 ();
   if (ds18al != ds18a_tam)
   {
      ds18a_tam = ds18al;
      ds18a = ds18a >> 4;
      ds18a = ds18a&0x0ff;
      ch_ds = ma7doan[ds18a/10];  //phai giai ma ngay khi do ra nhiet do
      dv_ds = ma7doan[ds18a%10];
      xuat_4led_7doan_4so(ch_ds, dv_ds, ch_a, dv_a);
   }
}

void doc_nd_lm35a()
{
   set_adc_channel (0) ;
   lm35a = 0;
   for (j = 0; j < solan; j++)
   {
      lm35a = lm35a + read_adc ();
      delay_us (100) ;
      //hien_thi_8led_7doan_quet();
   }

   lm35a = lm35a / 2.046;
   lm35a = lm35a / solan;
  
}

void gm_hien_thi_nhiet_do()
{
   
   
   ch_a = ma7doan[lm35a/10];
   dv_a = ma7doan[lm35a%10];
   xuat_4led_7doan_4so(ch_ds, dv_ds, ch_a, dv_a);
}
void main()
{
   set_up_port_ic_chot ();
   khoi_tao_ds18b20 ();
   ds18a_tam = 0;
   setup_adc (adc_clock_div_32) ;
   setup_adc_ports (an0_to_an1|vss_vdd) ;
   while (true)
   {
      do_nhietdo_ds18b20();
      doc_nd_lm35a();
      gm_hien_thi_nhiet_do();
      
   }
}

