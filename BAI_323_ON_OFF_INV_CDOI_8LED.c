
 #include <tv_pickit2_shift_1.c>
//!#include <TV_PICKIT2_SHIFT_1_PROTEUS.C>
unsigned INT8 y;

void main()
{
   set_up_port_ic_chot () ;
   set_tris_b (0x3c) ;
   y = 0;
   xuat_32led_don_4byte (0, 0, 0, 0) ;

   WHILE (true)
   {
      IF ( ! input (bt0) )
      {
         delay_ms (20) ;

         IF ( ! input (bt0))
         {
            y = 0x0F;
            xuat_32led_don_4byte (0, 0, 0, y) ;
            WHILE ( ! input (bt0)) ;
         }
      }

      IF ( ! input (bt1) )
      {
         delay_ms (20) ;

         IF ( ! input (bt1))
         {
            y = 0x0F;
            xuat_32led_don_4byte (0, 0, 0, y) ;
            WHILE ( ! input (bt1)) ;
         }
      }

      IF ( ! input (bt1) )
      {
         delay_ms (20) ;

         IF ( ! input (bt1))
         {
            y = ~y;
            xuat_32led_don_4byte (0, 0, 0, y) ;
            WHILE ( ! input (bt1)) ;
         }
      }

   }
}

