
#include <tv_pickit2_shift_1.c>
//! #include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_ds18b20.c>

void main()
{
   set_up_port_ic_chot();
   khoi_tao_ds18b20();
   ds18a_tam = 0;
   xuat_4led_7doan_giaima_xoa_so0(0);

   while (true)
   {
      if (touch_present())
         doc_giatri_ds18b20();
      if (ds18al != ds18a_tam)
      {
         ds18a_tam = ds18al;
         ds18a = ds18a >> 4;
         ds18a = ds18a & 0x0ff;
         tp = (ds18a & 0x0ff) * 100 / 16;
         xuat_4led_7doan_4so(ma7doan[ds18a / 10], ma7doan[ds18a % 10] & 0x7f, ma7doan[tp / 100], ma7doan[tp % 100 / 10]);
      }
   }
}
