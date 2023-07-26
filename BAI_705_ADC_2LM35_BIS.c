
//!#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_lcd.c>
unsigned int8 j, solan = 100, bdn;
unsigned int16 lm35a, lm35b, ch_a,  dv_a,  ch_b,  dv_b;
int1 tt_nn;

#int_timer1
void interrupt_timer1()
{
   bdn++;
   set_timer1 (3036) ;
}

void doc_nd_lm35a()
{
   set_adc_channel (0) ;
   lm35a = 0;
   for (j = 0; j < solan; j++)
   {
      lm35a = lm35a + read_adc ();
      delay_us (100) ;
      //hien_thi_8led_7doan_quet();
   }

   lm35a = lm35a / 2.046;
   lm35a = lm35a / solan;
}

void doc_nd_lm35b()
{
   set_adc_channel (1) ;
   lm35b = 0;
   
   for (j = 0; j < solan; j++)
   {
      lm35b = lm35b + read_adc ();
      delay_us (100) ;
      //hien_thi_8led_7doan_quet();
   }

   lm35b = lm35b / 2.046;
   lm35b = lm35b / solan;
}

void hien_thi_lcd()
{
   lcd_goto_xy(0,0);
   lcd_data("LM35A:");
   lcd_goto_xy(0,6);
   lcd_data(lm35a/10 + 0x30);
   lcd_data(lm35a%10 + 0x30);
   lcd_data(0xdf);
   lcd_data("C");
   
   lcd_goto_xy(1,0);
   lcd_data("LM35B:");
   lcd_goto_xy(1,6);
   lcd_data(lm35b/10 + 0x30);
   lcd_data(lm35b%10 + 0x30);
   lcd_data(0xdf);
   lcd_data("C");
}
void giai_ma_4led_7doan() 
{
   ch_a = ma7doan[lm35a / 10];
   dv_a = ma7doan[lm35a % 10];

   if (ch_a == 0xc0)
      ch_a = 0xff;

   ch_b = ma7doan[lm35b / 10];
   dv_b = ma7doan[lm35b % 10];

   if (ch_b == 0xc0)
      ch_b = 0xff;
}

void giai_ma_8led_quet()
{
   led_7dq[6] = ma7doan [lm35a % 10];
   led_7dq[7] = ma7doan [lm35a / 10];
   
   led_7dq[0] = ma7doan [lm35b % 10];
   led_7dq[1] = ma7doan [lm35b / 10];
}

void main()
{
   set_up_port_ic_chot () ;
   setup_adc (adc_clock_div_32) ;
   setup_adc_ports (an0_to_an1|vss_vdd) ;
   setup_lcd();
   
   while (true)
   {
      doc_nd_lm35a () ;
      doc_nd_lm35b () ;
      giai_ma_4led_7doan ();
      xuat_4led_7doan_4so (ch_a, dv_a&0x7f, ch_b, dv_b);
      giai_ma_8led_quet();
      hien_thi_8led_7doan_quet();
      hien_thi_lcd();
      if(lm35a > 30 || lm35b > 30) tt_nn = 1;
      else           tt_nn = 0;
      if(tt_nn == 1)
      {
         if (bdn < 5) 
         {
            xuat_4led_7doan_4so(0xff, 0xff, 0xff, 0xff);
           
            //erorr lcd chua nhap nhay duoc
            lcd_goto_xy(0,6);
            lcd_data(' ');
            lcd_data(' ');
            lcd_goto_xy(1,6);
            lcd_data(' ');
            lcd_data(' ');
       
         }
         else if (bdn < 10)
         {
            xuat_4led_7doan_4so (ch_a, dv_a&0x7f, ch_b, dv_b);
            lcd_goto_xy(0,6);
            lcd_data(lm35a/10 + 0x30);
            lcd_data(lm35a%10 + 0x30);
            lcd_goto_xy(1,6);
            lcd_data(lm35b/10 + 0x30);
            lcd_data(lm35b%10 + 0x30);
            
                      
         }
         if(bdn > 10)
            bdn = 0;
      }
      else
            xuat_4led_7doan_4so (ch_a, dv_a&0x7f, ch_b, dv_b);     
   }
}

