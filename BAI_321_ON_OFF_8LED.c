
#include <tv_pickit2_shift_1.c>

void main()
{
   set_up_port_ic_chot();
   set_tris_b(0x3c);
   xuat_32led_don_4byte(0,0,0,0);

   WHILE(true)
   {
      WHILE(input(bt0));
         xuat_32led_don_4byte(0,0,0,0xff);
      WHILE(input(bt1));
         xuat_32led_don_4byte(0,0,0,0);
   }
}

