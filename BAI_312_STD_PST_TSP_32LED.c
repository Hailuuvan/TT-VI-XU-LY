
 #include <tv_pickit2_shift_1.c>
//!#include <TV_PICKIT2_SHIFT_1_PROTEUS.C>

unsigned INT32 y;
unsigned INT8 dem;

void delay_tuy_y(UNSIGNED int8 dl2)
{
   UNSIGNED int8 dl;
   FOR (dl = 0; dl < dl2; dl++)
      delay_ms (1) ;
}

void sang_tat_dan_32led_pst_no_loop(UNSIGNED int8 dl)
{
   
   IF (dem < 32)
   {
      xuat_32led_don_1dw (y) ;
      delay_tuy_y (dl) ;
      y = (y<<1) + 1;
   }

   else IF (dem < 64)
   {
      xuat_32led_don_1dw (y) ;
      delay_tuy_y (dl) ;
      y = (y<<1);
   }

   
   else IF (dem < 96)
   {
      xuat_32led_don_1dw (y) ;
      delay_tuy_y (dl) ;
      y = (y>>1) + 0x80000000;
   }

   else IF (dem < 128)
   {
      xuat_32led_don_1dw (y) ;
      delay_tuy_y (dl) ;
      y = (y>>1);
   }

   ELSE
   {
      y = 0;
      dem = 0;
   }

   dem++;
}

void main()
{
   set_up_port_ic_chot () ;

   WHILE (true)
   {
      sang_tat_dan_32led_pst_no_loop (1000) ;
   }
}

