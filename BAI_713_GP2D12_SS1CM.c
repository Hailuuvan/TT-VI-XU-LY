
#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
#include <math.h>

unsigned int16 kqadc;
float k_cach;

void giai_ma_hienthi_4led (float tam)
{
   unsigned int16 x;
   x = (unsigned int16) tam;
   xuat_4led_7doan_giaima_xoa_so0 (x);
}

void main()
{
   set_up_port_ic_chot();
   setup_adc (adc_clock_div_32) ;
   setup_adc_ports (an0_to_an2|vss_vdd);
   set_adc_channel (2);

   while (true)
   {
      kqadc = read_adc () ;
      delay_ms (40) ;
      k_cach = pow (4277 / kqadc, 1.106) ;
      if (k_cach > 80) k_cach = 80;
      giai_ma_hienthi_4led (k_cach);
   }
}

