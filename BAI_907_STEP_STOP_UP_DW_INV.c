
//!#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_step_motor.c>

unsigned int16 mode,so_buoc = 0;


void phim_up()
{
   if (!input (up))
   {
      delay_ms (20) ;
      {
         if (!input (up))
         {
            mode ++;
            if (mode == 10)
               mode = 1;
            while ( ! input (up)) ;
         }
      }
   }
}

void phim_dw()
{
   if (!input (dw))
   {
      delay_ms (20) ;

      if (!input (dw))
      {
         mode --;

         if (mode == - 1)
            mode = 9;

         while ( ! input (dw)) ;
      }
   }
}

void phim_inv()
{
   if (!input (inv))
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

void phim_stop()
{
   if (!input (bt3))
   {
      delay_ms (20) ;
      {
         if (!input (bt3))
         {
            mode = 0;
            so_buoc = 0;
            while ( ! input (bt3)) ;
         }
      }
   }
}

unsigned int8 step_motor_delay()
{
   if (mode == 1) stepmotor_delay = 45;
   else if (mode == 2) stepmotor_delay = 40;
   else if (mode == 3) stepmotor_delay = 35;
   else if (mode == 4) stepmotor_delay = 30;
   else if (mode == 5) stepmotor_delay = 25;
   else if (mode == 6) stepmotor_delay = 20;
   else if (mode == 7) stepmotor_delay = 15;
   else if (mode == 8) stepmotor_delay = 10;
   else if (mode == 9) stepmotor_delay = 5;
   
   return stepmotor_delay;
}

void main()
{
   set_up_port_ic_chot () ;
   stepmotor_onoff = 1; //de khoi canh bao
   stepmotor_tn = 0;

   while (true)
   {
      phim_up () ;
      phim_dw () ;
      phim_stop () ;
      phim_inv () ;
      step_motor_delay () ;

      if (stepmotor_tn == 0)
      {
         if (mode != 0)
         {
            step_motor_quay_thuan_fs () ;
            delay_ms (stepmotor_delay) ;
            so_buoc++;
            xuat_4led_7doan_4so (ma7doan[mode % 10], ma7doan[so_buoc / 100 % 10], ma7doan[so_buoc / 10 % 10], ma7doan[so_buoc % 10]) ;
         }

         else
         {}
      }

      else if (stepmotor_tn == 1)
      {
         if (mode != 0)
         {
            step_motor_quay_nghich_fs () ;
            delay_ms (stepmotor_delay) ;
            so_buoc++;
            xuat_4led_7doan_4so (ma7doan[mode % 10], ma7doan[so_buoc / 100 % 10], ma7doan[so_buoc / 10 % 10], ma7doan[so_buoc % 10]) ;
         }

         else
         {}
      }
   }

}

