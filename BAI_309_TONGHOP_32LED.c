//! #include <tv_pickit2_shift_1.c>
#include <TV_PICKIT2_SHIFT_1_PROTEUS.C>
unsigned int32 y;
unsigned int8 i,j;
void sang_tat_5lan(){
   for(i = 0; i < 5; i++){
            xuat_32led_don_1dw(y);
            delay_ms(1000);
            y = ~y;
        }
//!      for(i=0;i<5;i++)
//!      {
//!         xuat_32led_don_4byte(0,0,0,0);
//!         delay_ms(1000);
//!         xuat_32led_don_4byte(0xff,0xff,0xff,0xff);
//!         delay_ms(1000);
//!      }
 }
void sang_tat_dan_pst_32led_2lan()
{ 
for(j=0;j<2;j++)
 {
 for(i=0;i<32;i++)
 { 
    xuat_32led_don_1dw(y);
    delay_ms(30); 
    y= (y<<1)+1;
 }
 for(i=0;i<32;i++)
 { 
    xuat_32led_don_1dw(y);
    delay_ms(30); 
    y= (y<<1);
 } 
 }
} 
void sang_tat_dan_tsp_32led_2lan()
{ 
   for(j=0;j<2;j++)
    { 
    for(i=0;i<32;i++)
    { 
       xuat_32led_don_1dw(y);
       delay_ms(30); 
       y= (y>>1)+0x80000000;
    }
    for(i=0;i<32;i++)
    { 
       xuat_32led_don_1dw(y);
       delay_ms(30); 
       y= (y>>1);
    } 
    }
} 
void main()
{ 
set_up_port_ic_chot(); 
 y=0x00000000;
 while(true)
 {
    sang_tat_5lan();
    sang_tat_dan_pst_32led_2lan();
    sang_tat_5lan();
    sang_tat_dan_tsp_32led_2lan();
 }
}


