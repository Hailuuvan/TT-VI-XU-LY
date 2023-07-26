
#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_step_motor.c>

void phim_inv()
{
   if (!input(inv))
   {
      delay_ms(20);
      {
         if (!input(inv))
         {
            stepmotor_tn=~stepmotor_tn;

            do
            {
               motor_step_run_fs();
               delay_ms(stepmotor_delay);
            }

            while(!input(inv));
         }
      }
   }
}

void main()
{
   set_up_port_ic_chot();
   stepmotor_delay=5;
   stepmotor_onoff=1; //de khoi canh bao
   while(true)
   {
      while(input(on)); //cho nhan on
      do
      {
         motor_step_run_fs();
         delay_ms(stepmotor_delay);
         phim_inv();
         
      }
      while (input(off));
      
   }
}

