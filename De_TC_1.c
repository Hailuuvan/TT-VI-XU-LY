#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_ds18b20.c>
#include <tv_pickit2_shift_ds1307_i2c.c>
#include <tv_pickit2_shift_step_motor.c>
unsigned int16 kqadc,  tp_kc, kc_int, ch_nguyen;
float k_cach,clk_cach;
signed int8 i,j,bdn;
unsigned int16 mode,so_buoc = 0;
void phim_up()
{
   if (!input(up))
   {
      delay_ms(20);
      {
         if (!input(up))
         {
            mode ++;
            while(!input(up));
            if(mode == 10)
               mode = 1;
         }
      }
   }
}

void phim_dw()
{
   if (!input(dw))
   {
      delay_ms(20);
      {
         if (!input(dw))
         {
            mode --;
            while(!input(dw));
            if(mode == -1)
               mode = 9;
         }
      }
   }
}
void phim_stop()
{
   if (!input(bt3))
   {
      delay_ms(20);
      {
         if (!input(bt3))
         {
            mode = 0;
            so_buoc =0;
            while(!input(bt3));
         }
      }
   }
}
unsigned int8 step_motor_delay()
{
   if(mode == 1)  stepmotor_delay=45;
   else if(mode == 2)  stepmotor_delay=40;
   else if(mode == 3)  stepmotor_delay=35;
   else if(mode == 4)  stepmotor_delay=30;
   else if(mode == 5)  stepmotor_delay=25;
   else if(mode == 6)  stepmotor_delay=20;
   else if(mode == 7)  stepmotor_delay=15;
   else if(mode == 8)  stepmotor_delay=10;
   else if(mode == 9)  stepmotor_delay=5;

   return stepmotor_delay;
}
#int_timer1
void interrupt_timer1()
{
   bdn++;
   set_timer1 (3036);
}
void lcd_hienthi_so_z_toado_xy(signed int8 lcd_so, x1, y1)
{
   lcd_goto_xy(x1,y1);
   for (i=0;i<6;i++)
   {
      if (i==3) lcd_goto_xy(x1+1,y1);
      lcd_data(lcd_so_x[lcd_so][i]);
   }
}
void giai_ma_hienthi_4led (float tam)
{
   unsigned int16 x;
   x = (unsigned int16) tam;
   tp_kc = k_cach*100;
   xuat_4led_7doan_4so(ma7doan[x / 10], ma7doan[x % 10]&0x7f, ma7doan[tp_kc % 1000 %100 /10], ma7doan[tp_kc % 1000 %100 % 10]);
   lcd_goto_xy(0,14);
   printf(lcd_data, "%3.2f", k_cach);
   //1234 234 23 10 
}
void gm_lcd_so_lon()
{
   kc_int = k_cach;
   tp_kc = k_cach*100;
   ch_nguyen  = kc_int/10;
   if(ch_nguyen == 0)
   ch_nguyen = 10;
   lcd_hienthi_so_z_toado_xy(ch_nguyen, 0,0);
   lcd_hienthi_so_z_toado_xy(kc_int % 10, 0,3);
   lcd_goto_xy(1,6);
   lcd_data('.');
   lcd_hienthi_so_z_toado_xy(tp_kc % 1000 %100 /10 , 0,7);
   lcd_hienthi_so_z_toado_xy(tp_kc % 1000 %100 % 10, 0,10);
}

void nhapnhay()
{
   if (k_cach > 30)
   {
      if (bdn < 10)
      {
         if (bdn < 5)
         {
            giai_ma_hienthi_4led (k_cach);
            gm_lcd_so_lon();
         }

         else if (bdn < 10)
         {
            lcd_hienthi_so_z_toado_xy(10, 0,0);
            lcd_hienthi_so_z_toado_xy( 10, 0,3);
            lcd_hienthi_so_z_toado_xy(10 , 0,7);
            lcd_hienthi_so_z_toado_xy(10, 0,10);
            xuat_4led_7doan_4so(0xff,0xff,0xff,0xff);
         }
      }

      else
      bdn = bdn - 10;
   }

   else
   giai_ma_hienthi_4led (k_cach) ;
}
void dokhoangcach()
{
   set_adc_channel (2);
   kqadc = 0;
   for (j = 0; j < 20; j++)
   {
      kqadc = kqadc + read_adc () ;
      delay_ms (10);
   }

   kqadc = kqadc / 20;
   if (kqadc <= 80) k_cach = 80;

   else if ((kqadc > 80) && (kqadc < 87))
   {
      clk_cach = kqadc - 80;
      k_cach = 80 - clk_cach / 0.77;
   }

   else if (kqadc == 87) k_cach = 70;

   else if ((kqadc > 87) && (kqadc < 106))
   {
      clk_cach = kqadc - 87;
      k_cach = 70 - clk_cach / 2.11;
   }

   else if (kqadc == 106) k_cach = 60;

   else if ((kqadc > 106) && (kqadc < 124))
   {
      clk_cach = kqadc - 106;
      k_cach = 60 - clk_cach / 2;
   }

   else if (kqadc == 124) k_cach = 50;

   else if ((kqadc>124) &&(kqadc<150))
   {
      clk_cach = kqadc-124;
      k_cach=50 - clk_cach/2.88;
   }

   else if (kqadc==150) k_cach=40;

   else if ((kqadc>150) &&(kqadc<196))
   {
      clk_cach = kqadc-150;
      k_cach=40 - clk_cach/5.11;
   }

   else if (kqadc==196) k_cach=30;

   else if ((kqadc>196) &&(kqadc<276))
   {
      clk_cach = kqadc-196;
      k_cach=30 - clk_cach/8.88;
   }

   else if (kqadc==276) k_cach=20;

   else if ((kqadc>276) &&(kqadc<490))
   {
      clk_cach = kqadc-276;
      k_cach=20 - clk_cach/23.77;
   }

   else if (kqadc==490) k_cach=10;

   giai_ma_hienthi_4led (k_cach) ;
}

void main  ()
{
   set_up_port_ic_chot ();
   setup_lcd () ;
   setup_adc (adc_clock_div_32);
   setup_adc_ports (an0_to_an1|vss_vdd);
   khoi_tao_ds18b20 ();
   ds18a_tam = 0;
   doc_thoi_gian_tu_realtime ();

   if (ma_ds13 != ma_ds)
   {
      thiet_lap_thoi_gian_hien_tai () ;
      nap_thoi_gian_htai_vao_ds13b07 () ;
   }
   setup_timer_1 (t1_internal|t1_div_by_8) ;
   set_timer1 (3036) ;
   enable_interrupts (global) ;
   enable_interrupts (int_timer1) ;
   bdn = 0;
   doc_thoi_gian_tu_realtime () ;
   giaytam = giay_ds13;
   lcd_command(0x40);
   for (i=0;i<64;i++) { lcd_data(lcd_ma_8doan[i]); }
   
   //khai bao dc
   stepmotor_onoff = 1; //de khoi canh bao
   stepmotor_tn = 0;
   while (true)
   {
      //doc_thoi_gian_tu_realtime () ;
      dokhoangcach();
      gm_lcd_so_lon();
      nhapnhay();
      phim_up () ;
      phim_dw () ;
      phim_stop () ;
      phim_inv () ;
      step_motor_delay () ;
   }
}
