
//! #include <tv_pickit2_shift_1.c>
#include <TV_PICKIT2_SHIFT_1_PROTEUS.C>

unsigned INT32 y;
unsigned INT8 dem;

void sang_tat_dan_32led_no_loop()
{
   IF (dem < 32)
   {
      xuat_32led_don_1dw (y) ;
      delay_ms (300) ;
      y = (y<<1) + 1;
   }

   IF (dem >= 32&&dem < 64)
   {
      xuat_32led_don_1dw (y) ;
      delay_ms (300) ;
      y = (y<<1);
   }

   IF (dem >= 64)
   {
      dem = 0;
      y = 0;
   }

   dem++;
}

void main()
{
   set_up_port_ic_chot () ;

   WHILE (true)
   {
      sang_tat_dan_32led_no_loop () ;
   }
}

