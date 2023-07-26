
 #include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>

unsigned int8 j, solan = 100;

unsigned int16 lm35a, lm35b, ch_a,  dv_a,  ch_b,  dv_b;
unsigned int16 kqadc;
float k_cach,clk_cach;

int doc_nd_lm35a()
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
   return lm35a;
}

int doc_nd_lm35b()
{
   set_adc_channel (1);
   lm35b = 0;
   for (j = 0; j < solan; j++)
   {
      lm35b = lm35b + read_adc () ;
      //delay_us (100);
      hien_thi_8led_7doan_quet();
   }

   lm35b = lm35b / 2.046;
   lm35b = lm35b / solan;
   return lm35b;
}

void giai_ma_hienthi_8led_quet()
{
   //giai_ma_4led_7doan ();
   led_7dq[1] = dv_b;
   led_7dq[2] = ch_b;
   
   led_7dq[3] = dv_a;
   led_7dq[4] = ch_a;
   
   led_7dq[5] = ma7doan[(unsigned int16)k_cach%10];
   led_7dq[6] = ma7doan[(unsigned int16)k_cach/10];
}

void giai_ma_4led_7doan() 
{
   ch_a = ma7doan[lm35a / 10];
   dv_a = ma7doan[lm35a % 10];

   if (ch_a == 0xc0)
      ch_a = 0xff;

   ch_b = ma7doan[lm35b / 10];
   dv_b = ma7doan[lm35b % 10];

   if (ch_b == 0xc0)
      ch_b = 0xff;
}

void do_kc()
{
   kqadc = 0;
   for (j = 0; j<20; j++)
   {
      kqadc = kqadc + read_adc () ;
      //delay_ms (10) ;
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
   giai_ma_4led_7doan();
   giai_ma_hienthi_8led_quet();
   hien_thi_8led_7doan_quet();
}

void main()
{
   set_up_port_ic_chot ();
   setup_adc (adc_clock_div_32);
   setup_adc_ports (an0_to_an1|vss_vdd);
   setup_adc (adc_clock_div_32);
   setup_adc_ports (an0_to_an2|vss_vdd);
   set_adc_channel (2);

   while (true)
   {
      doc_nd_lm35a ();
      doc_nd_lm35b ();
      giai_ma_4led_7doan ();
      xuat_4led_7doan_4so (ch_a, dv_a&0x7f, ch_b, dv_b);
      do_kc();
      giai_ma_hienthi_8led_quet();
      hien_thi_8led_7doan_quet();
   }
}

