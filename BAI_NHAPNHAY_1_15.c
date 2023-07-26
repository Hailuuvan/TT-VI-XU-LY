
//!#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_1.c>

signed int8 giay,bdn,bdn_nn;

#int_timer1

void interrupt_timer1()
{
   bdn++;
   bdn_nn++;
   set_timer1 (3036);
}

void giai_ma_gan_cho_8led_quet()
{
   led_7dq[3] = ma7doan [giay % 10];
   led_7dq[4] = ma7doan [giay / 10];
}

void main()
{
   set_up_port_ic_chot ();
   setup_timer_1 (t1_internal|t1_div_by_8);
   set_timer1 (3036);
   enable_interrupts (global);
   enable_interrupts (int_timer1);
   giay = 5;
   bdn = bdn_nn = 0;

   while (true)
   {
      if (bdn < 10) hien_thi_8led_7doan_quet () ;

      else
      {
         bdn = bdn - 10;
         giay++;
         if (giay == 21) giay = 5;
      }

      if (bdn_nn >= 25) bdn_nn = bdn_nn - 25;

      if (giay > 10)
      {
         if (bdn_nn < 10) {led_7dq[4] = 0xff; led_7dq[3] = 0xff; }
         else giai_ma_gan_cho_8led_quet ();
      }

      else giai_ma_gan_cho_8led_quet ();
   }
}

