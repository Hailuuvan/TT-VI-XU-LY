#include <tv_pickit2_shift_1_proteus.c>
//! #include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_lcd.c>
#include <tv_pickit2_shift_key4x4_138.c>

// unsigned int1 ctrinh_cau_b = 0;
signed int8 mp, bdn, bdn_nn, dem;
// signed int8 gh[5] = {0, 4, 2, 1, 1};

#int_timer1
void interrupt_timer1()
{
   bdn++;
   bdn_nn++;
   set_timer1(3036);
}

void main()
{
   set_up_port_ic_chot();
   setup_timer_1(t1_internal | t1_div_by_8);
   set_timer1(3036);
   enable_interrupts(global);
   enable_interrupts(int_timer1);
   bdn = 0;
   bdn_nn = 0;
   while (true)
   {
      if (bdn < 10)
      {
            XUAT_32LED_DON_1DW(0xffffffff);
      }
      else if (bdn <= 30)
      {
         XUAT_32LED_DON_1DW(0);
            if(bdn == 30)
               bdn = bdn - 30;
      }
      // if(bdn_nn < 30)
      //    XUAT_32LED_DON_1DW(0);
      // else
      // {
      //    bdn_nn = bdn_nn - 30;
      // }
      //delay_ms(200);
   }
}