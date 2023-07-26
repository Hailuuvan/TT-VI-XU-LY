
#include <tv_pickit2_shift_1_proteus.c>

unsigned int8 j, solan = 100;
unsigned int16 gtcdt = 35, lm35a;

#define nd_tren  60
#define nd_duoi  35

unsigned int8 ch_gtc, dv_gtc, ch_lm35, dv_lm35;
int1 ttqn; 
void doc_nd_lm35a()
{
   set_adc_channel (0) ;
   lm35a = 0;
   for (j = 0; j < solan; j++)
   {
      lm35a = lm35a + read_adc ();
      // delay_us (100);
      hien_thi_8led_7doan_quet () ;
   }

   lm35a = lm35a / 2.046;
   lm35a = lm35a / solan;
}

void so_sanh_lm35()
{
   if ((lm35a > gtcdt)&& (ttqn == 0))
   {
      ttqn = 1;
      xuat_32led_don_4byte(0,0,0,0xff);
      triac_2_off () ;
   }

   else if ((lm35a < gtcdt)&& (ttqn == 1))
   {
      ttqn = 0;
      xuat_32led_don_4byte(0,0,0,0);
   }

   else if ((lm35a < gtcdt - 5)&& (ttqn == 0)) 
   {
      triac_2_on ();
      xuat_32led_don_4byte(0xff,0,0,0);
   }
}

void giai_ma_4led_7doan()
{
   ch_lm35 = ma7doan[lm35a / 10];
   dv_lm35 = ma7doan[lm35a % 10];
   ch_gtc = ma7doan[gtcdt / 10];
   dv_gtc = ma7doan[gtcdt % 10];
}

void phim_up()
{
   if (( ! input (up)) && (gtcdt < nd_tren))
   {
      delay_ms (20) ;
      {
         if (!input (up))
         {
            gtcdt++;
            xuat_4led_7doan_4so (ch_gtc, dv_gtc, ch_lm35, dv_lm35);
            while (!input (up));
         }
      }
   }
}

void phim_dw()
{
   if (( ! input (dw)) && (gtcdt > nd_duoi))
   {
      delay_ms (20) ;
      {
         if (!input (dw))
         {
            gtcdt--;
            xuat_4led_7doan_4so (ch_gtc, dv_gtc, ch_lm35, dv_lm35);
            while (!input (dw));
         }
      }
   }
}

void main()
{
   set_up_port_ic_chot () ;
   setup_timer_0 (t0_ext_l_to_h|t0_div_1|t0_8_bit) ;
   setup_adc (adc_clock_div_32) ;
   setup_adc_ports (an0|vss_vdd) ;
   set_adc_channel (0) ;

   while (true)
   {
      so_sanh_lm35();
      phim_up () ;
      phim_dw () ;
      giai_ma_4led_7doan () ;
      doc_nd_lm35a () ;
      xuat_4led_7doan_4so (ch_gtc, dv_gtc, ch_lm35, dv_lm35);
   }
}

