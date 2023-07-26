#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_ds18b20.c>
unsigned int16 ch_ds, dv_ds, t0, ch_dem, dv_dem;

void do_nhietdo_ds18b20()
{
   if (touch_present () )
      doc_giatri_ds18b20 ();
   if (ds18al != ds18a_tam)
   {
      ds18a_tam = ds18al;
      ds18a = ds18a >> 4;
      ds18a = ds18a&0x0ff;
      ch_ds = ma7doan[ds18a/10];
      dv_ds = ma7doan[ds18a%10];
      xuat_4led_7doan_4so( ch_dem, dv_dem, ch_ds, dv_ds);
   }
}

void gm_hien_thi()
{
   ch_dem = ma7doan[t0/10];
   dv_dem = ma7doan[t0%10];
}

void main()
{
   set_up_port_ic_chot ();
   khoi_tao_ds18b20 ();
   ds18a_tam = 0;
   setup_timer_0 (t0_ext_l_to_h | t0_div_1|t0_8_bit);
   set_timer0(0);
   while (true)
   {
      t0 = get_timer0();
      if(t0 == 100)
         t0 = 1;
      do_nhietdo_ds18b20();
      gm_hien_thi();
      xuat_4led_7doan_4so( ch_dem, dv_dem, ch_ds, dv_ds);
   }
}
