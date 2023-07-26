
//!#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_lcd.c>
#include <tv_pickit2_shift_key4x4_138.c>

unsigned int8 array[2]={0XFE, 0XFE};
unsigned int8 t0, tr, ch, dv, gt_cai, mp;


void hienthi_lcd()
{
   lcd_goto_xy (1, 0);
   lcd_data ("dem san pham") ;
   //tr = t0 / 100 + 0x30;
   ch = t0 / 10 % 10 + 0x30;
   dv = t0 % 10 + 0x30;
   if (ch == 0x30)
      ch = 0x20;
   

   lcd_goto_xy (1, 13);
   //lcd_data (tr) ;
   lcd_data (ch) ;
   lcd_data (dv) ;
   lcd_goto_xy (0, 12) ;
   lcd_data (array[0]) ;
   lcd_data (array[1]) ;
   gt_cai = (array[0] - 0x30) * 10 + (array[1] - 0x30)  ;
   lcd_goto_xy (0, 0);
   lcd_data ("gia tri cai:") ;
   lcd_data (gt_cai % 10 + 0x30);
   lcd_data (gt_cai / 10 + 0x30);
}

void cai_gt_4x4()
{
   array[1] = array[0];
   array[0] = mp + 0x30;
}

void main()
{
   set_up_port_ic_chot () ;
   set_tris_b (0x3c) ;
   setup_lcd () ;
   setup_timer_0 (t0_ext_l_to_h|t0_div_1|t0_8_bit) ;
   set_timer0 (0) ;
   gt_cai = 0;
   array[0] = 0x30; array[1] = 0x30;
   while (true)
   {
      t0 = get_timer0 ();
      xuat_4led_7doan_3so (ma7doan[t0 / 100], ma7doan[t0 / 10 % 10], ma7doan[t0 % 10]);
      hienthi_lcd () ;
      mp = key_4x4_dw ();

      if (mp != 0xff && mp < 10)
      {
         cai_gt_4x4 () ;
         hienthi_lcd () ;
      }
      if (mp == 12)    
         {  
            set_timer0 (1) ;
            array[0] = 0x30; array[1] = 0x30;
            gt_cai = (array[0] - 0x30) * 10 + (array[1] ) + 1   ;  
         }

      if (t0 > gt_cai)
         set_timer0 (1) ;
   }
}

