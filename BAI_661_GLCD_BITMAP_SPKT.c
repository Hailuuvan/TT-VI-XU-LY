
#include<tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_glcd128x64.c>

void main()
{
   set_up_port_ic_chot();
   setup_glcd(glcd_graphic_mode);
   glcd_mau_nen(0) ;
   glcd_xuat_anh(64,64,32,0) ;
   gdram_vdk_to_gdram_glcd_all ();
   while(true);
}

