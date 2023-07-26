#include <tv_pickit2_shift_1.c>

signed INT8 giay, bdn, bdn_nn;

#INT_timer1
void interrupt_timer1()
{
   bdn++;
   bdn_nn++;
   set_timer1 (3036);
}

void giai_ma_gan_cho_8led_quet()
{
   led_7dq[0] = ma7doan [giay % 10];
   led_7dq[1] = ma7doan [giay / 10];
}

void giai_ma_gan_cho_8led_quet_TAT()
{
   led_7dq[0] = 0xff;
   led_7dq[1] = 0Xff;
}

void main()
{
   set_up_port_ic_chot ();
   
   //khoi tao ngat timer 1
   setup_timer_1 (t1_internal|t1_div_by_8);
   set_timer1 (3036);
   enable_interrupts (global);
   enable_interrupts (INT_timer1);
   
   giay = 5;
   bdn = 0;
   bdn_nn = 0;
   
   WHILE (true)
   {
      IF (giay > 10)
      {
         IF(bdn_nn < 10)
         {
            giai_ma_gan_cho_8led_quet_TAT();
//!            hien_thi_8led_7doan_quet ();   
         }
         ELSE if(bdn_nn < 25)
         {
            giai_ma_gan_cho_8led_quet ();
//!            hien_thi_8led_7doan_quet ();   
         }
         else
         {
               bdn_nn = bdn_nn - 25;
         }
         hien_thi_8led_7doan_quet ();   
      }

      IF (bdn < 10)
      {
         if(giay <= 10)
         {
            giai_ma_gan_cho_8led_quet ();
            hien_thi_8led_7doan_quet ();
         }
      }
      ELSE
      {
         bdn = bdn - 10;
         giay++;        
         IF (giay == 21)
            giay = 5;
      }
   }
}

  

