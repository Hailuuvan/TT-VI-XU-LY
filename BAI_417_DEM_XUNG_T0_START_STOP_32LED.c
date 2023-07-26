
//! #include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_1_proteus.c>
unsigned INT8 t0, t0_tam;


void main()
{
   set_up_port_ic_chot();
   // setup_timer_0 (t0_ext_l_to_h|t0_div_1|t0_8_bit);
   set_timer0(0);

   xuat_4led_7doan_giaima_xoa_so0(t0);
   setup_timer_0(t0_off);
   WHILE(true)
   {
      t0 = get_timer0();
      xuat_4led_7doan_giaima_xoa_so0(t0);
      
      if (t0 >= 100)
         set_timer0(1);
      IF(input(on) == 0)
      {
         delay_ms(20);
         IF(input(on) == 0)
         {
            xuat_32led_don_1dw(0xffffffff);
            setup_timer_0(t0_ext_l_to_h | t0_div_1 | t0_8_bit);
         }
      }
      IF(input(off) == 0)
      {
         setup_timer_0(t0_off);
         xuat_32led_don_1dw(0);
      }
   }
}
