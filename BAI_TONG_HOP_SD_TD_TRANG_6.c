
//!#include <tv_pickit2_shift_1.c>
#include <TV_PICKIT2_SHIFT_1_PROTEUS.C>

unsigned INT32 y;
unsigned INT8 i,j;

void sang_dan_12bit()
{
   y = 0;
   FOR (i = 0;i < 4; i++)
   {
      xuat_32led_don_1dw (y) ;
      delay_ms (200) ;
      y = ( ( (y>>5)|0x3E0000)&0X003FFC00);
   }

   
   FOR (i = 0;i < 4; i++)
   {
      xuat_32led_don_1dw (y) ;
      delay_ms (200) ;
      y = ( ( (y<<5)|0x7C00)&0X003FFC00);
   }
}

   VOID tat_dan_12bit () 
   {
      FOR (i = 0;i < 4; i++)
      {
         xuat_32led_don_1dw (y) ;
         delay_ms (200) ;
         y = ( ( (y>>5)&0xFFC1FFFF)|0XFFC003FF);
      }

      FOR (i = 0;i < 4; i++)
      {

         xuat_32led_don_1dw (y) ;
         delay_ms (200) ;
         y = ( ( (y<<5)&0xFFFF83FF)|0XFFC003FF);
      }
   }

   VOID Chop_tat_12led_giua_3lan()
   {
      y = 0x00000000;
      FOR (i = 0; i < 3; i++)
      {
         xuat_32led_don_1dw (y);
         delay_ms (300);
         xuat_32led_don_1dw (0x3FFC00);
         delay_ms (300);
      }
   }

   VOID main ()
   {
      set_up_port_ic_chot();

      WHILE (true)
      {
         FOR (j = 0; j < 2; j++)
            sang_dan_12bit () ;

         FOR (j = 0; j < 2; j++)
            tat_dan_12bit () ;

         Chop_tat_12led_giua_3lan () ;
         tat_dan_12bit () ;
         Chop_tat_12led_giua_3lan () ;
      }
   }

