#include <tv_pickit2_shift_1_proteus.c>
//!#include <tv_pickit2_shift_1.c>
signed int8 t0;
unsigned int8 chuc, donvi;
int1 tt_ht, tt_dem, tt_ss;

void giai_ma_hien_thi()
{
   donvi = ma7doan[t0%10];
   chuc  = ma7doan[t0/10%10];
   
   if(chuc == 0xc0)
      chuc = 0xff;
}
void hien_thi_led_7doan()
{
   if(tt_ht == 0)
      xuat_4led_7doan_4so(chuc, donvi & 0x7f, 0x92, 0x8c);
   else
      xuat_4led_7doan_4so(0x92, 0x8c & 0x7f,chuc, donvi);
}

void phim_start_pause()
{
   if(!input(bt0))
   {
      delay_ms(20);
      if(!input(bt0))
      {
         tt_ss =~ tt_ss;
         while(!input(bt0));
      }
   }
}

void phim_dao_ben_hien_thi()
{
   if(!input(bt1))
   {
      delay_ms(20);
      if(!input(bt1))
      {
         tt_ht =~ tt_ht;
         while(!input(bt1));
      }
   }
}

void phim_dao_tt_dem()
{
   if(!input(bt2))
   {
      delay_ms(20);
      if(!input(bt2))
      {
         tt_dem =~ tt_dem;
         set_timer0(99 - get_timer0());
         while(!input(bt2));
      }
   }
}

void main()
{
   set_up_port_ic_chot();
   tt_ht = 0 ;tt_dem = 0; tt_ss = 0;
   set_timer0(0);
   while(true)
   {
      phim_start_pause();
      phim_dao_ben_hien_thi();
      phim_dao_tt_dem();
      
      if(tt_ss == 1)
      {
         setup_timer_0(t0_ext_l_to_h | t0_div_1 | t0_8_bit);
         xuat_32led_don_1dw(0xffffffff);
         giai_ma_hien_thi();
         if(tt_dem == 0)
         {
            t0 = get_timer0();
            hien_thi_led_7doan();
            if( t0 >= 100)
               set_timer0(1);
         }
         else
         {
            t0  = 99 - get_timer0();
            hien_thi_led_7doan();
            if( t0 == 0)
               set_timer0(0);
         }
      }
      else
      {
         setup_timer_0(t0_off);
         xuat_32led_don_1dw(0);
      }
      delay_ms(100);
   } 
}
