
//! #include <tv_pickit2_shift_1.c>
#include <TV_PICKIT2_SHIFT_1_PROTEUS.C>
#include <tv_pickit2_shift_32led_don.c>
INT8 tt_ct;
unsigned INT32 y,i;

void phim_up()
{
   IF ( ! input (up) )
   {
      delay_ms (20);
      tt_ct++;

      IF (tt_ct == 5)
         tt_ct = 4;

      WHILE (input (up) == 0);
   }
}

void phim_dw()
{
   IF (input (dw))
   {
      delay_ms (20);
      tt_ct--;

      IF (tt_ct == 1)
         tt_ct = 2;

      WHILE (input (dw) == 0);
   }
}

void phim_clr()
{
   IF (input (clr))
   {
      delay_ms (20);
      tt_ct = 1;
      WHILE (input (clr) == 0);
   }
}

void blink_32led()
{
   xuat_32led_don_1dw (0xffffffff);
   delay_ms (300);
   xuat_32led_don_1dw (0);
   delay_ms (300);
}

void sang_tat_dan_pst_32led()
{
   FOR (i = 0; i < 32; i++)
   {
      xuat_32led_don_1dw (y) ;
      delay_ms (100);
      y = (y<<1) + 1;
   }

   FOR (i = 0; i < 32; i++)
   {
      xuat_32led_don_1dw (y) ;
      delay_ms (100);
      y = (y<<1);
   }
}

void main()
{
   set_up_port_ic_chot ();
   y = 0;
   tt_ct = 1 ;
   set_tris_b (0x3c);
   xuat_32led_don_4byte (0, 0, 0, 0);

   WHILE (true)
   {
      phim_up () ;
      phim_dw () ;
      phim_clr () ;
      IF (tt_ct == 1)
         blink_32led ();
      if (tt_ct == 2)
         sang_tat_dan_pst_32led();
   }
}

