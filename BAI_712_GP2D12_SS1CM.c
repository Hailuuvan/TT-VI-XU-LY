
//!#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_1_proteus.c>

unsigned int8 j; 

unsigned int16 kqadc, tam;
float k_cach,clk_cach;

// void giai_ma_hienthi_4led (float tam)
// {
//    unsigned int16 x;
//    x = (unsigned int16) tam;
//    xuat_4led_7doan_giaima_xoa_so0 (x);
// }

void main()
{
   set_up_port_ic_chot () ;
   setup_adc (adc_clock_div_32);
   setup_adc_ports (an0_to_an2|vss_vdd);
   set_adc_channel (2);

   while (true)
   {
      tam = k_cach;
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

      else if (kqadc==124) k_cach=50;

      else if ((kqadc > 124) && (kqadc < 150))
      {
         clk_cach = kqadc - 124;
         k_cach = 50 - clk_cach / 2.88;
      }

      else if (kqadc==150) k_cach=40;

      else if ((kqadc > 150) && (kqadc < 196))
      {
         clk_cach = kqadc - 150;
         k_cach = 40 - clk_cach / 5.11;
      }

      else if (kqadc == 196) k_cach = 30;

      else if ((kqadc > 196) && (kqadc < 276))
      {
         clk_cach = kqadc - 196;
         k_cach = 30 - clk_cach / 8.88;
      }

      else if (kqadc == 276) k_cach = 20;

      else if ((kqadc > 276) && (kqadc < 490))
      {
         clk_cach = kqadc - 276;
         k_cach=20 - clk_cach/23.77;
      }

      else if (kqadc == 490) k_cach = 10;
      //giai_ma_hienthi_4led (k_cach);
      xuat_4led_7doan_giaima_xoa_so0 (tam);
   }
}

