
 #include <tv_pickit2_shift_1.c>
//!#include <TV_PICKIT2_SHIFT_1_PROTEUS.C>

INT1 tt;
unsigned INT16 y;

void phim_up()
{
   IF ( ! input (up) )
   {
      delay_ms (20);

      IF ( ! input (up))
      {
         IF (tt == 0)
            y = (y<<1) + 1;

         else
         y = (y>>1) + 8000;
         xuat_32led_don_2word (0, y);
         WHILE ( ! input (up)) ;
      }
   }
}

void phim_down()
{
   IF ( ! input (dw) )
   {
      delay_ms (100);

      IF ( ! input (dw))
      {
         IF (tt == 0)
            y = (y>>1) ;

         else
            y = (y<<1) ;
         xuat_32led_don_2word (0, y);
         WHILE ( ! input (up)) ;
      }
   }
}

void phim_clr()
{
   IF ( ! input (clr) )
   {
      y = 0;
      tt=~tt;
      xuat_32led_don_2word (0, y);
      WHILE ( ! input (clr)) ;
   }
}

void main()
{
   set_up_port_ic_chot ();
   set_tris_b (0x3c);
   y = 0;
   tt = 0;
   WHILE (true)
   {
      phim_up () ;
      phim_down () ;
      phim_clr () ;
   }
}

