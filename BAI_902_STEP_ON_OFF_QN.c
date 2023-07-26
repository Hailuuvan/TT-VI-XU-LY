
#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_step_motor.c>

int1 tt_quay;

void main()
{
   set_up_port_ic_chot () ;
   stepmotor_delay = 20;
   stepmotor_onoff = 1;

   //de khoi canh bao
   tt_quay = 0;

   while (true)
   {
         if ( ! input (on)) 
         {
            delay_ms (20) ;
            if ( ! input (on) )
            {
               tt_quay =1;
            }
            while ( ! input (on)) ;
         }
         if ( ! input (off)) 
         {
            delay_ms (20) ;
            if ( ! input (off) )
            {
               tt_quay = 0;
            }
            while ( ! input (off)) ;
         }
            if (tt_quay == 1)
            {
               STEP_MOTOR_QUAY_NGHICH_FS () ;
               delay_ms (stepmotor_delay) ;
            }
         }
      }
   


