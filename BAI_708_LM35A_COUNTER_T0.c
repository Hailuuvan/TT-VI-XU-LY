
//!#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_lcd.c>

unsigned int8 j, solan = 100;
unsigned int16 lm35a, t0, ch_a,  dv_a,  ch_c,  dv_c;

void doc_nd_lm35a()
{
   set_adc_channel (0);
   lm35a = 0;
   for (j = 0; j < solan; j++)
   {
      lm35a = lm35a + read_adc () ;
      //delay_us (100);
      hien_thi_8led_7doan_quet () ;
   }

   lm35a = lm35a / 2.046;
   lm35a = lm35a / solan;
}

void giai_ma_4led_7doan() 
{
   ch_a = ma7doan[lm35a / 10];
   dv_a = ma7doan[lm35a % 10];

   if (ch_a == 0xc0)
      ch_a = 0xff;

   
   ch_c = ma7doan[t0 / 10];
   dv_c = ma7doan[t0 % 10];

   if (ch_c == 0xc0)
      ch_c = 0xff;
}

void main()
{
   set_up_port_ic_chot();
   setup_timer_0 (t0_ext_l_to_h | t0_div_1|t0_8_bit);
   set_timer0(0);
   setup_adc(adc_clock_div_32);
   setup_adc_ports(an0 | vss_vdd);
   set_adc_channel(0);
   while(true)
   {
      doc_nd_lm35a();
      t0=get_timer0();
         if (t0>=101) set_timer0(1);
      giai_ma_4led_7doan() ;
      xuat_4led_7doan_4so( ch_c,dv_c & 0x7f,ch_a,dv_a);
   }
}

