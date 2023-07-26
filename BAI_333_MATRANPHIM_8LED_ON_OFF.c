
#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_key4x4_138.c>

signed INT8 mp;

void main()
{
   set_up_port_ic_chot();
   set_tris_b(0x3c);

   WHILE(true)
   {
      DO {mp= key_nhan();}
      WHILE(mp!=1);
      xuat_32led_don_4byte(0,0,0,0xff);
      DO {mp= key_nhan();}
      WHILE(mp!=0);
      xuat_32led_don_4byte(0,0,0,0);
   }
}

