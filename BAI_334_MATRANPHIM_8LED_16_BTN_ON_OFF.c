#include <TV_PICKIT2_SHIFT_1_PROTEUS.C>
//!#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_key4x4_138.c>

signed INT8 mp,y;
void dkhien_8led_4x4()
{
   mp = key_nhan();
   if(mp<8)
   {
      y = y | (0x01<<mp);
      xuat_32led_don_4byte(0,0,0,y);
   }
   if (mp>=8 && mp <16){
      y = y & (~(0x01<<(mp-8)));
      xuat_32led_don_4byte(0,0,0,y);
   }
}
void main()
{
   set_up_port_ic_chot () ;
   set_tris_b (0x3c) ;
   y = 0;
   xuat_32led_don_4byte (0, 0, 0, 0) ;

   WHILE(true)
   {
      dkhien_8led_4x4();
   }
}

