#include <tv_pickit2_shift_1_proteus.c>
//!#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_dc_motor.c>
int1 tt_onoff, tt_offinv;
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
void phim_off()
{
   if(!input(off))
      {
         delay_ms(20);
         if(!input(off))
         {
            tt_onoff =~ tt_onoff;
            dc_motor_stop();
         }
      }  
}  
void main()
{
   set_up_port_ic_chot();
   dc_motor_enable();
   dc_motor_stop();
   tt_onoff = 0;
   tt_offinv = 0;
   while(true)
   { 
      if(tt_onoff == 0)
      {
         if(!input(on))
         {
            delay_ms(20);
            if(!input(on))
            {
               dcmotor_onoff=1;
               dc_motor_control(); 
               tt_offinv =~ tt_offinv;
            }
         }
      }
      if( tt_offinv == 1)
      {
         phim_inv();
         phim_off();
      }
      
   }
}

