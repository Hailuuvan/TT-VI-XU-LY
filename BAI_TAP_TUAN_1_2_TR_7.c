#include <tv_pickit2_shift_1.c>
//!#include <TV_PICKIT2_SHIFT_1_PROTEUS.C>
unsigned int16 slt,slp,yt,yt1;
void dich_trai_10_led()
{
      if(yt < 11)
      {
         slt = (slt << 1) + 1;
         xuat_32led_don_2word(slt, slp);
         delay_ms(20); 
         
      }
      else {
         slt = 0;
         yt = 0;
      }  
      yt++;
}
void dich_phai_16led()
{
      if(yt1 < 17)
      {
         slp = (slp >> 1) + 0x8000;
         xuat_32led_don_2word(slt, slp);
         delay_ms(20);
         
      }
       else {
         slp = 0;
         yt1 = 0;
      }
      yt1++;
}
void main()
{
   set_up_port_ic_chot();
      slp= 0;
      slt =0;
   WHILE(true)
   {
      
      dich_trai_10_led();
      dich_phai_16led();
   }
}
