
//!#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_dc_motor.c>

void main()
{
   set_up_port_ic_chot();
   dc_motor_enable();
   dc_motor_stop();

   while(true)
   {
      while(input(on));
      {
         dc_motor_quay_thuan();
         xuat_32led_don_4byte(0,0,0,0xff);
      }

      while(input(off));
      {
         dc_motor_stop();
         xuat_32led_don_4byte(0,0,0,0);
      }
   }
}

