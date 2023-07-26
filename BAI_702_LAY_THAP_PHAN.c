#include <tv_pickit2_shift_1_proteus.c>
//!#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_lcd.c>
#define nd_tren 40

unsigned int8 j, solan=100;
float lm35a;
unsigned int16 KQ_HT, tp, ch, dv;
int1 ttqn=0;

void so_sanh_dk_buzzer()
{
   if ((lm35a>nd_tren)&&(ttqn==0))
   {
      ttqn = 1;
//!      buzzer_on();
       xuat_32led_don_4byte(0,0,0,0xff);
   }

   else if ((lm35a<nd_tren)&&(ttqn==1))
   {
      ttqn = 0;
//!      buzzer_off();
      xuat_32led_don_4byte(0,0,0,0);
   }
}

void main()
{
   set_up_port_ic_chot();
   setup_adc(adc_clock_div_32);
   setup_adc_ports(an0|vss_vdd );
   set_adc_channel(0);
   ttqn = 0;
   setup_lcd();
   while(true)
   {
      lm35a = 0;
      for (j=0; j<solan; j++)
      {
         lm35a = lm35a + read_adc();
         delay_ms(1);
      }

      lm35a = lm35a /2.046;
      lm35a = lm35a /solan;
      //xuat_4led_7doan_giaima_xoa_so0(lm35a);
      so_sanh_dk_buzzer();
      
      KQ_HT = (int16) (lm35a*10);
      
      //giai ma lay phan thap phan
      
      tp = ma7doan[KQ_HT%10];
      dv = ma7doan[KQ_HT/10%10];
      ch = ma7doan[KQ_HT/100];
      
      //hien thi led 7 doan
      
      xuat_4led_7doan_4so(ch, dv& 0x7f, tp, 0xff);
     
     //hien thi lcd
     lcd_command(0xc0);
     printf(lcd_data,"nd = %3.2f", lm35a);
   }
}

