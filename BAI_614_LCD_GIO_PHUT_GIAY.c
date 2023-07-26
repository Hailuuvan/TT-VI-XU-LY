//!#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_lcd.c>

signed int8 gio, phut, giay, bdn;
signed int8 ch_gio, dv_gio, ch_phut, dv_phut, ch_giay, dv_giay;
unsigned int8 gia_tri_mod;

#int_timer1

void interrupt_timer1()
{
   bdn++;
   set_timer1 (3036) ;
}

void giai_ma_lcd()
{
   dv_gio = gio % 10 + 0x30;
   ch_gio = gio / 10 + 0x30;
   dv_phut = phut % 10 + 0x30;
   ch_phut = phut / 10 + 0x30;
   dv_giay = giay % 10 + 0x30;
   ch_giay = giay / 10 + 0x30;
}

void hien_thi_lcd()
{
   LCD_goto_XY (0, 0) ;
   delay_us (20) ;
   lcd_data (ch_gio) ;
   lcd_data (dv_gio) ;
   lcd_data (' ') ;
   lcd_data (ch_phut) ;
   lcd_data (dv_phut) ;
   lcd_data (' ') ;
   lcd_data (ch_giay) ;
   lcd_data (dv_giay) ;
}

void phim_mod()
{
   if (!input (mod))
   {
      
      if (!input (mod))
      {
         gia_tri_mod++;

         if (gia_tri_mod >= 4)
            gia_tri_mod = 0;

         xuat_4led_7doan_giaima_xoa_so0 (gia_tri_mod) ;
         while (!input (mod));
      }
   }
}

void phim_up()
{
   if (!input (up))
   {
      
      if (!input (up))
      {
         switch (gia_tri_mod)
         {
            case 1:
            if (gio == 23)
               gio = 0;

            else
            gio++;
            break;

            case 2:
            if (phut == 59)
               phut = 0;

            else
            phut++;
            break;

            case 3:
            if (giay == 59)
               giay = 0;

            else
            giay++;
            break;

            default:
            break;
         }

         while (!input (up));
      }
   }
}

void phim_dw()
{
   if (!input (dw))
   {
      
      if (!input (dw))
      {
         switch (gia_tri_mod)
         {
            case 1:
            if (gio == 0)
               gio = 23;

            else
            gio--;
            break;

            case 2:
            if (phut == 0)
               phut = 59;

            else
            phut--;
            break;

            case 3:
            if (giay == 0)
               giay = 59;

            else
            giay--;
            break;

            default:
            break;
         }

         while (!input (dw));
      }
   }
}

// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void main()
{
   set_up_port_ic_chot () ;
   setup_timer_1 (t1_internal|t1_div_by_8) ;
   set_timer1 (3036) ;
   enable_interrupts (global) ;
   enable_interrupts (int_timer1) ;
   SETUP_LCD () ;
   ch_gio = 0; dv_gio = 0; ch_phut = 0; dv_phut = 0; ch_giay = 0; dv_giay = 0;
   giay = 0;
   phut = 0;
   gio = 0;
   gia_tri_mod = 0;

   while (true)
   {
      giai_ma_lcd () ;

      if (bdn < 10)
      {
         hien_thi_lcd () ;
         phim_mod () ;
         phim_up () ;
         phim_dw () ;
      }

      else
      {
         bdn = bdn - 10;
         giay++;

         if (giay == 60)
         {
            giay = 0;
            phut++;

            if (phut == 60)
            {
               phut = 0;
               gio++;

               if (gio == 24)
                  gio = 0;
            }
         }
      }

      delay_ms (100) ;
   }
}

