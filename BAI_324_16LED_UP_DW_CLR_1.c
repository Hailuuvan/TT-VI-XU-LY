
//! #include <tv_pickit2_shift_1.c>
#include <TV_PICKIT2_SHIFT_1_PROTEUS.C>
unsigned INT8 y;

void main()
{
   set_up_port_ic_chot () ;
   set_tris_b (0x3c) ;
   y = 0;
   xuat_32led_don_4byte (0, 0, 0, 0) ;

   WHILE (true)
   {
      IF ( ! input (up) )
      {
         delay_ms (20) ;

         IF ( ! input (up))
         {
            y = (y<<1) + 1;
            xuat_32led_don_4byte (0, 0, 0, y) ;
            WHILE ( ! input (up)) ;
         }
      }

      IF ( ! input (dw) )
      {
         delay_ms (20) ;

         IF ( ! input (dw))
         {
            y = (y>>1) ;
            xuat_32led_don_4byte (0, 0, 0, y) ;
            WHILE ( ! input (dw)) ;
         }
      }

      if(!input(clr))
      {
         delay_ms (20) ;

         IF ( ! input (clr))
         {
            y = 0;
            xuat_32led_don_4byte (0, 0, 0, y) ;
            WHILE ( ! input (dw)) ;
         }
      }

   }
}

