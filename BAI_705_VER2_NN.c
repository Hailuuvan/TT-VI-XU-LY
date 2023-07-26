//KENH NAO QUA DO KENH DO NHAP NHAY

#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_lcd.c>
#define range 30
unsigned int8 j,i, TT_NN, solan=10;
unsigned int8 ch_toA, dv_toA, ch_toB, dv_toB, ch_A, dv_A, ch_B, dv_B;
signed int16 lm35a, lm35b;
signed INT8 bdn;

#INT_timer1
VOID interrupt_timer1()
{
   bdn++;
   set_timer1 (3036);
}
VOID lcd_hienthi_so_z_toado_xy(signed int8 lcd_so, x1, y1)
{
   lcd_goto_xy (x1, y1) ;
   for (i = 0; i < 6; i++)
   {
      if (i == 3) lcd_goto_xy (x1 + 1, y1);
      lcd_data (lcd_so_x[lcd_so][i]);
   }
}
VOID delay_hienthi()
{
//!   for (i = 0; i < 100; i++)
   hien_thi_8led_7doan_quet ();
}
VOID doc_nd_kenhA()
{
   set_adc_channel (0);
   delay_ms (1);
   lm35a = 0;
   for (j = 0; j < solan; j++)
   {
      lm35a = lm35a + read_adc () ;
      delay_hienthi() ;
   }

   lm35a = lm35a / 2.046;
   lm35a = lm35a / solan;
}
VOID doc_nd_kenhB()
{
   set_adc_channel (1);
   delay_ms (1);
   lm35b = 0;
   for (j = 0; j < solan; j++)
   {
      lm35b = lm35b + read_adc () ;
      delay_hienthi() ;
   }

   lm35b = lm35b / 2.046;
   lm35b = lm35b / solan;
}
VOID so_sanh_dk_buzzer()
{
   if(lm35a> range && lm35b > range) TT_NN=0;
   if(lm35a< range && lm35b < range) TT_NN=1;
   if(lm35a> range && lm35b < range) TT_NN=2;
   if(lm35a< range && lm35b > range) TT_NN=3;
}
VOID GIAI_MA()
{
   // giai ma 8led quet
   led_7dq[0]=ma7doan[lm35b%10];
   led_7dq[1]=ma7doan[lm35b/10%10];
   led_7dq[6]=ma7doan[lm35a%10];
   led_7dq[7]=ma7doan[lm35a/10%10];
   // giai ma lcd font to
   ch_toA = lm35a / 10 % 10;
   dv_toA = lm35a % 10;   
   ch_toB = lm35b / 10 % 10;
   dv_toB = lm35b % 10;
   // giai ma led 7 doan
   ch_A=ma7doan[lm35a/10%10];
   dv_A=ma7doan[lm35a%10];
   ch_B=ma7doan[lm35b/10%10];
   dv_B=ma7doan[lm35b%10];
}
VOID TAT_HET()
{
   if(TT_NN==0)
   {
      // led quet tat het
      led_7dq[0]=0xff;
      led_7dq[1]=0xff;
      led_7dq[6]=0xff;
      led_7dq[7]=0xff;
      // LCD font to tat het
      ch_toA = 10;
      dv_toA = 10;  
      ch_toB = 10;
      dv_toB = 10;  
      // led 7 doan tat het
      ch_A=0xff;
      dv_A=0xff;
      ch_B=0xff;
      dv_B=0xff;
   }
   if(TT_NN==2)
   {
      // led quet tat het
      led_7dq[6]=0xff;
      led_7dq[7]=0xff;
      // LCD font to tat het
      ch_toA = 10;
      dv_toA = 10;  
      // led 7 doan tat het
      ch_A=0xff;
      dv_A=0xff;
   }
   if(TT_NN==3)
   {
      // led quet tat het
      led_7dq[0]=0xff;
      led_7dq[1]=0xff;
      // LCD font to tat het
      ch_toB = 10;
      dv_toB = 10;  
      // led 7 doan tat het
      ch_B=0xff;
      dv_B=0xff;
   }
   
}
VOID HIEN_THI()
{
   // hien thi LCD
   lcd_hienthi_so_z_toado_xy (ch_toA, 0, 14) ;
   lcd_hienthi_so_z_toado_xy (dv_toA, 0, 17) ;
   lcd_hienthi_so_z_toado_xy (ch_toB, 2, 14) ;
   lcd_hienthi_so_z_toado_xy (dv_toB, 2, 17) ;
   // hien thi led 7 doan
   xuat_4led_7doan_4so(ch_A,dv_A,ch_B,dv_B);
}

VOID main()
{
   set_up_port_ic_chot () ;
   
   setup_lcd () ;
   lcd_command (0x40);
   for (i = 0; i < 64; i++) { lcd_data (lcd_ma_8doan[i]); }
 
   setup_adc (adc_clock_div_32);
   setup_adc_ports (an0_to_an1|vss_vdd); 
   
   setup_timer_1 (t1_internal|t1_div_by_8);
   set_timer1 (3036);
   enable_interrupts (global);
   enable_interrupts (INT_timer1);
   bdn=0;
   lcd_goto_xy(0,0);
   lcd_data("LM35A:");
   lcd_goto_xy(2,0);
   lcd_data("LM35B:");
   while (true)
   {
      doc_nd_kenhA () ;
      doc_nd_kenhB();
      so_sanh_dk_buzzer () ;
      if(TT_NN!=1)
      {
         if(bdn<5)
         {
            TAT_HET();
         }
         else if(bdn<10)
         {
            GIAI_MA();
         }
         else
         {
            bdn=0;
         }
         hien_thi_8led_7doan_quet();
         HIEN_THI();
      }
      if(TT_NN==1) 
      {
         
         hien_thi_8led_7doan_quet();
         GIAI_MA();
         HIEN_THI();
      }
   }
}


