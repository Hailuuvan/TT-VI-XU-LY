
#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_step_motor.c>

unsigned int1 i=1, tt=0;

unsigned int16  so_buoc=0,so_vong = 0;//bdn;
//dem so buoc cua step motor
//!#int_timer1
//!void interrupt_timer1()
//!{
//!   
//!   bdn++; 
//!   set_timer1 (60536) ;
//!   if (bdn >= 20)
//!   {
//!      step_motor_quay_thuan_fs () ;
//!      //delay_ms (stepmotor_delay) ;
//!      so_buoc++;
//!   }
//!   if (bdn >= 21) 
//!      bdn = 0;
//!}
void giai_ma()
{
   led_7dq[0] = ma7doan[so_buoc % 10];
   led_7dq[1] = ma7doan[so_buoc / 10 % 10];
   led_7dq[2] = ma7doan[so_buoc / 100 % 10];
   led_7dq[3] = ma7doan[so_vong % 10];
   led_7dq[4] = ma7doan[so_vong / 10 % 10];
   hien_thi_8led_7doan_quet_all () ;
}

void kt_inv()    
{
   if ( ! input (inv))
   {
      delay_ms (20) ;

      if ( ! input (inv) )
      {
         i = ~i;
         so_buoc = 0;
         so_vong =0 ;
         while ( ! input (inv)) ;
      }
   }
}



void main()
{
   set_up_port_ic_chot () ;
   stepmotor_delay = 5;
   stepmotor_onoff = 1; //de khoi canh bao
//!   setup_timer_1 (t1_internal|t1_div_by_1) ;
//!   enable_interrupts (global) ;
//!   enable_interrupts (int_timer1) ;

   while (true)
   {
      if ( ! input (on)) 
         i = tt = 1;
      if(tt == 1)
      {
         if (i == 1)
         {
            step_motor_quay_thuan_fs () ;
            delay_ms(stepmotor_delay);
            so_buoc ++;
            if(so_buoc == 200)
            {
               so_vong++;
               so_buoc =0 ;
            }
         }
         else if( i == 0)
         {
            step_motor_quay_nghich_fs () ;
            delay_ms(stepmotor_delay);
            so_buoc++;
            if(so_buoc == 200)
            {
               so_vong++;
               so_buoc =0 ;
            }
         }
      }

      if ( !input (off)) 
         tt=0;
      if(tt == 0){}
      kt_inv () ;
      giai_ma () ;
   }
}

