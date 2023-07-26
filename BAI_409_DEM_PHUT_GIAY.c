
//!#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_1.c>
unsigned INT8 g,p;

void main()
{
   set_up_port_ic_chot () ;

   WHILE (true)
   {
      FOR (p = 0; p < 60; p++)
         FOR (g = 0; g < 60; g++)
         {
            xuat_4led_7doan_4so (ma7doan[p / 10], ma7doan[p % 10], ma7doan[g / 10], ma7doan[g % 10]);
            
         delay_ms (200) ;
         }
   }

}

