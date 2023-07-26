#include <tv_pickit2_shift_1_proteus.c>
//!#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_dc_motor.c>

void phim_inv()
{
   if (!input(inv))
   {
      delay_ms(20);
      {
         if (!input(inv))
         {
            dc_motor_stop();
            delay_ms(1000);
            dcmotor_tn=~dcmotor_tn;
            dc_motor_control();
            while(!input(inv));
         }
      }
   }
}

void main()
{
   set_up_port_ic_chot();
   dc_motor_enable();
   dc_motor_stop();

   while(true)
   {
      while(input(on)); //cho nhan stop
      dcmotor_onoff=1;
      dc_motor_control();

      do
      {
         phim_inv();
      }while(input(off));

      dc_motor_stop();
   }
}

