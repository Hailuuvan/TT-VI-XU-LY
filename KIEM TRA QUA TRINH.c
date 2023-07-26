
#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_lcd.c>
#include <tv_pickit2_shift_key4x4_138.c>

signed int8 mp, i, t0, bdn, dem, dem_led;
signed int8 chuc, donvi, chuc_lcd, donvi_lcd;

#int_timer1
void interrupt_timer1()
{
   bdn++;
   set_timer1 (3036) ;
}

void lcd_hienthi_so_z_toado_xy(signed int8 lcd_so, x1, y1)
{
   lcd_goto_xy (x1, y1);
   for (i = 0; i < 6; i++)
   {
      if (i == 3)
         lcd_goto_xy (x1 + 1, y1);

      lcd_data (lcd_so_x[lcd_so][i]) ;
      hien_thi_8led_7doan_quet () ;
   }
}

void giai_ma_lcd()
{
   chuc_lcd  = dem/10;
   donvi_lcd  = dem%10;
   if(chuc_lcd == 0)
      chuc_lcd = 10;  
}

void hien_thi_lcd()
{
   lcd_hienthi_so_z_toado_xy(chuc_lcd,0,16);
   lcd_hienthi_so_z_toado_xy(donvi_lcd,0,9);
   lcd_goto_xy(2,4);
   lcd_data('*');
   lcd_data(chuc_lcd + 0x30);
   lcd_data(donvi_lcd +0x30);
   lcd_data('*');
   lcd_data("Second");
   lcd_data('*');
   lcd_goto_xy(3,0);
   lcd_data("Chuc=");
   lcd_data(chuc_lcd +0x30);
   lcd_goto_xy(3,14);
   lcd_data("Dvi=");
   lcd_data(donvi_lcd +0x30);
}
void giai_ma_led_7doan_quet()
{
   chuc = t0 / 10;
   donvi = t0 % 10;
   led_7dq[2] = ma7doan[chuc]&0x7f;
   led_7dq[3] = 0xc9&0x7f;
   led_7dq[4] = 0xc7&0x7f;
   led_7dq[5] = ma7doan[donvi]&0x7f;
   
   if (chuc == 0)
      led_7dq[2] = 0xff;
}


void giai_ma_hien_thi_4led_7doan()
{
   //giai ma led 7 doan
   donvi = ma7doan[t0 % 10];
   chuc = ma7doan[t0 / 10];

   //xoa so 0 vo nghia
   if (chuc == 0xc0)
      chuc = 0xff;
}

void hien_thi_4_led_7doan()
{
   xuat_4led_7doan_4so (donvi&0x7f, 0xc7&0x7f, 0xc9&0x7f, chuc&0x7f);
}

void main()
{
   set_up_port_ic_chot();
    setup_timer_1(t1_internal | t1_div_by_8);
    set_timer1(3036);
    enable_interrupts(global);
    enable_interrupts(int_timer1);
    setup_timer_0(t0_ext_l_to_h | t0_div_1 | t0_8_bit);
    set_timer0(0);
    setup_lcd();
   //set_timer0 (9) ;
   set_timer0 (0) ;
   bdn =0; dem =0; chuc_lcd=0; donvi_lcd = 0; dem_led = 0;
   while (true)
   {
      
      t0 = 14 - get_timer0 ();

      if (t0 == 8)
         set_timer0 (0) ;

      giai_ma_hien_thi_4led_7doan () ;
      hien_thi_4_led_7doan () ;
      
      giai_ma_led_7doan_quet () ;
      hien_thi_8led_7doan_quet () ;
      giai_ma_lcd();
      if (bdn < 10)
      {
         hien_thi_lcd();
      }
      else
      {
         bdn = bdn - 10;
         dem++;
         if (dem == 60)
         {
            dem = 0;
         }
      }
   }
}

