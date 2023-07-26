
 #include < tv_pickit2_shift_1.c >
//!#include <TV_PICKIT2_SHIFT_1_PROTEUS.C>
#include <tv_pickit2_shift_key4x4_138.c>
unsigned INT8 y;
signed INT8 mp;

void main()
{
   set_up_port_ic_chot ();
   set_tris_b (0x3c);
   y = 0;
   xuat_32led_don_4byte (0, 0, 0, 0);
   
   WHILE (true)
   {
      mp = key_nhan ();
      delay_ms (50);

      IF (mp != 0xff)
      {
         IF (mp == 0)
            delay_ms (20);

         IF (mp == 0)
         {
            y = (y<<1) + 1;
            xuat_32led_don_4byte (0, 0, 0, y);
            WHILE (mp == 0) mp = key_nhan ();
         }

         IF (mp == 4)
            delay_ms (20);

         IF (mp == 4)
         {
            y = (y>>1);
            xuat_32led_don_4byte (0, 0, 0, y);
            WHILE (mp == 4) mp = key_nhan ();
         }

         IF (mp == 8)
            delay_ms (20);

         IF (mp == 8)
         {
            y = 0;
            xuat_32led_don_4byte (0, 0, 0, y);
            WHILE (mp == 8) mp = key_nhan ();
         }
      }
   }
}

