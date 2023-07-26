#include <tv_pickit2_shift_1_proteus.c>

unsigned int16 tg_delay;

void main()
{
   set_up_port_ic_chot();
   tg_delay=1;

   while(true)
   {
      xuat_8led_7doan_quet_1(0xfd, 0xc0); //6
      delay_ms(tg_delay);
      xuat_8led_7doan_quet_1(0xfe, 0xf9); //7
      delay_ms(tg_delay);
   }
}