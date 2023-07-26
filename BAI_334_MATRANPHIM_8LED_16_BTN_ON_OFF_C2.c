#include <TV_PICKIT2_SHIFT_1_PROTEUS.C>
//!#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_key4x4_138.c>

signed INT8 mp,y;

void main()
{
   set_up_port_ic_chot () ;
   set_tris_b (0x3c) ;
   y = 0;
   xuat_32led_don_4byte (0, 0, 0, 0) ;

   WHILE(true)
   {
      if(mp!=0xFF)
      {
         if(mp == 0)    y =y|0x01;            
         if(mp == 1)    y =y|0x02;           
         if(mp == 2)    y =y|0x04;            
         if(mp == 3)    y =y|0x08;            
         if(mp == 4)    y =y|0x10;              
         if(mp == 5)    y =y|0x20;             
         if(mp == 6)    y =y|0x40;           
         if(mp == 7)    y =y|0x80;   
         
         if(mp == 8)    y =0xfe&Y; 
         if(mp == 9)    y =0xfd&Y; 
         if(mp == 10)    y =0xfb&Y;
         if(mp == 11)    y =0xf7&Y; 
         if(mp == 12)    y =0xef&Y; 
         if(mp == 13)    y =0xdf&Y;
         if(mp == 14)    y =0xcf&Y;
         if(mp == 15)    y =0xbf&Y;
         if(mp == 15)    y =0x7f&Y;
         xuat_32led_don_4byte(0,0,0,y);
         
      }
   }
}

