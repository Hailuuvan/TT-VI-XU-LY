//! #include <tv_pickit2_shift_1.c>
#include <TV_PICKIT2_SHIFT_1_PROTEUS.C>
unsigned int16 y,dem;
void main(){
set_up_port_ic_chot();
y=0;
while(true){
   if (dem < 16){
   xuat_32led_don_2word(y, y);
   delay_ms(200);
   y = (y << 1) + 1;
   }
   else if(dem < 32){
      xuat_32led_don_2word(y, y);
      delay_ms(200);
      y = y << 1;
   }
   else{
      dem = 0;
      y = 0;
   }
   dem++;
}
}


