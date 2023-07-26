//!#include <TV_PICKIT2_SHIFT_1_PROTEUS.C>
#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_key4x4_138.c>

signed INT8 mp;

void main()
{
   set_up_port_ic_chot();
   set_tris_b(0x3c);

   WHILE(true)
   {
      mp = key_4x4_dw();
      IF (mp!= 0xff) 
      xuat_32led_don_4byte(0,0,0,mp);
   }
}

