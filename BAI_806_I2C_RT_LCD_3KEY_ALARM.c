
#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
#include <TV_PICKIT2_SHIFT_DS1307_I2C.c>

unsigned int16 k, bdn,bdn_h, gio, phut, giay, giay_buzzer;
unsigned char giatri_mod;

#int_timer1
void interrupt_timer1()
{
   bdn++;
   bdn_h++;
   set_timer1 (3036);
}

void hien_thi_gia_tri_mod()
{
   lcd_command (0x8a);
   lcd_data (giatri_mod + 0x30);
}

void phim_mod()
{
   if (!input (mod))
   {
      delay_ms (20);
      {
         if (!input (mod))
         {
            if (giatri_mod < 10)
               giatri_mod++;

            else
            giatri_mod = 0;
            hien_thi_gia_tri_mod ();
            while (!input (mod));
         }
      }
   }
}

unsigned int8 hieu_chinh_so_bcd_tang(unsigned int8 x)
{
   unsigned int8 y;
   y = x;
   x = x&0x0f;

   if (x == 0x0a)
      y = y + 6;

   return (y);
}

unsigned int8 hieu_chinh_so_bcd_giam(unsigned int8 x)
{
   unsigned int8 y;
   y = x;
   x = x&0x0f;

   if (x == 0x0f)
      y = y - 6;

   return (y);
}

void luu_giai_ma_hien_thi_sau_khi_chinh()
{
   nap_thoi_gian_htai_vao_ds13b07 ();
   //hien_thi_thoi_gian_ds13b07 ();
}

void phim_up()
{
   if (!input (up))
   {
      delay_ms (20);

      if (!input (up))
      {
         switch (giatri_mod)
         {
            case 1:
            if (giay_ds13 == 0x59)
               giay_ds13 = 0;

            else
            {
               giay_ds13++;
               giay_ds13 = hieu_chinh_so_bcd_tang (giay_ds13);
            }

            luu_giai_ma_hien_thi_sau_khi_chinh ();
            break;

            case 2:
            if (phut_ds13 == 0x59)
               phut_ds13 = 0;

            else
            {
               phut_ds13++;
               phut_ds13 = hieu_chinh_so_bcd_tang (phut_ds13);
            }

            luu_giai_ma_hien_thi_sau_khi_chinh ();
            break;

            case 3:
            if (gio_ds13 == 0x23)
               gio_ds13 = 0;

            else
            {
               gio_ds13++;
               gio_ds13 = hieu_chinh_so_bcd_tang (gio_ds13);
            }

            luu_giai_ma_hien_thi_sau_khi_chinh ();
            break;

            case 4:
            if (ngay_ds13 == 0x31)
               ngay_ds13 = 1;

            else
            {
               ngay_ds13++;
               ngay_ds13 = hieu_chinh_so_bcd_tang (ngay_ds13);
            }

            luu_giai_ma_hien_thi_sau_khi_chinh ();
            break;

            case 5:
            if (thang_ds13 == 0x12)
               thang_ds13 = 1;

            else
            {
               thang_ds13++;
               thang_ds13 = hieu_chinh_so_bcd_tang (thang_ds13);
            }

            luu_giai_ma_hien_thi_sau_khi_chinh ();
            break;

            case 6:
            if (nam_ds13 == 0x99)
               nam_ds13 = 0;

            else
            {
               nam_ds13++;
               nam_ds13 = hieu_chinh_so_bcd_tang (nam_ds13);
            }

            luu_giai_ma_hien_thi_sau_khi_chinh ();
            break;
            case 7: if (thu_ds13 == 7) thu_ds13 = 1;

            else
            {
               thu_ds13++;
               thu_ds13 = hieu_chinh_so_bcd_tang (thu_ds13) ;
            }

            luu_giai_ma_hien_thi_sau_khi_chinh ();
            break;
            case 8: if (giay == 0x59) giay = 0x00;

            else
            {
               giay++;
               giay = hieu_chinh_so_bcd_tang (giay) ;
            }

            luu_giai_ma_hien_thi_sau_khi_chinh ();
            break;
            case 9: if (phut == 0x59) phut = 0x00;

            else
            {
               phut++;
               phut = hieu_chinh_so_bcd_tang (phut) ;
            }

            luu_giai_ma_hien_thi_sau_khi_chinh ();
            break;
            case 10: if (gio == 0x23) gio = 0x00;

            else
            {
               gio++;
               gio = hieu_chinh_so_bcd_tang (gio) ;
            }

            luu_giai_ma_hien_thi_sau_khi_chinh ();
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
      delay_ms (20);

      if (!input (dw))
      {
         switch (giatri_mod)
         {
            case 1:
            if (giay_ds13 == 0)
               giay_ds13 = 0x59;

            else
            {
               giay_ds13--;
               giay_ds13 = hieu_chinh_so_bcd_giam (giay_ds13);
            }

            luu_giai_ma_hien_thi_sau_khi_chinh ();
            break;

            case 2:
            if (phut_ds13 == 0)
               phut_ds13 = 0x59;

            else
            {
               phut_ds13--;
               phut_ds13 = hieu_chinh_so_bcd_giam (phut_ds13);
            }

            luu_giai_ma_hien_thi_sau_khi_chinh ();
            break;

            case 3:
            if (gio_ds13 == 0)
               gio_ds13 = 0x23;

            else
            {
               gio_ds13--;
               gio_ds13 = hieu_chinh_so_bcd_giam (gio_ds13);
            }

            luu_giai_ma_hien_thi_sau_khi_chinh ();
            break;

            case 4:
            if (ngay_ds13 == 0)
               ngay_ds13 = 0x31;

            else
            {
               ngay_ds13--;
               ngay_ds13 = hieu_chinh_so_bcd_giam (ngay_ds13);
            }

            luu_giai_ma_hien_thi_sau_khi_chinh ();
            break;

            case 5:
            if (thang_ds13 == 1)
               thang_ds13 = 0x12;

            else
            {
               thang_ds13--;
               thang_ds13 = hieu_chinh_so_bcd_giam (thang_ds13);
            }

            luu_giai_ma_hien_thi_sau_khi_chinh ();
            break;

            case 6:
            if (nam_ds13 == 0)
               nam_ds13 = 0x99;

            else
            {
               nam_ds13--;
               nam_ds13 = hieu_chinh_so_bcd_giam (nam_ds13);
            }

            luu_giai_ma_hien_thi_sau_khi_chinh ();
            break;
            case 7: if (thu_ds13 == 1) thu_ds13 = 7;

            else
            {
               thu_ds13--;
               thu_ds13 = hieu_chinh_so_bcd_tang (thu_ds13) ;
            }

            luu_giai_ma_hien_thi_sau_khi_chinh ();
            break;
            case 8: if (giay == 0x00) giay = 0x59;

            else
            {
               giay--;
               giay = hieu_chinh_so_bcd_giam (giay) ;
            }

            luu_giai_ma_hien_thi_sau_khi_chinh ();
            break;
            case 9: if (phut == 0x00) phut = 0x59;

            else
            {
               phut--;
               phut = hieu_chinh_so_bcd_giam (phut) ;
            }

            luu_giai_ma_hien_thi_sau_khi_chinh ();
            break;
            case 10: if (gio == 0x00) gio = 0x23;

            else
            {
               gio--;
               gio = hieu_chinh_so_bcd_giam (gio) ;
            }

            luu_giai_ma_hien_thi_sau_khi_chinh ();
            break;

            default:
            break;
         }

         while (!input (dw));
      }
   }
}

void nhap_nhay_con_tro()
{
   switch (giatri_mod)
   {
      case 1:
      lcd_command (0xd3);
      break;

      case 2:
      lcd_command (0xd0);
      break;

      case 3:
      lcd_command (0xcd);
      break;

      case 4:
      lcd_command (0x8d);
      break;

      case 5:
      lcd_command (0x90);
      break;

      case 6:
      lcd_command (0x93);
      break;

      default:
      break;
   }
}

void nhap_nhay()
{
   if (giatri_mod == 0)
   {
      LCD_COMMAND (0x8C);
      LCD_DATA (0x20);
      LCD_DATA (0x20);
      LCD_DATA (' ');
   }

   else if (giatri_mod == 1)
   {
      LCD_COMMAND (0x8f);
      LCD_DATA (0x20);
      LCD_DATA (0x20);
      LCD_DATA (' ');
   }

   else if (giatri_mod == 2)
   {
      LCD_COMMAND (0x92);
      LCD_DATA (0x20);
      LCD_DATA (0x20);
      LCD_DATA (' ');
   }

   else if (giatri_mod == 3)
   {
      LCD_COMMAND (0xd2);
      LCD_DATA (0x20);
      LCD_DATA (0x20);
      LCD_DATA (' ');
   }

   else if (giatri_mod == 4)
   {
      LCD_COMMAND (0xcf);
      LCD_DATA (0x20);
      LCD_DATA (0x20);
      LCD_DATA (' ');
   }

   else if (giatri_mod == 5)
   {
      LCD_COMMAND (0xcc);
      LCD_DATA (0x20);
      LCD_DATA (0x20);
      LCD_DATA (' ');
   }
}

void HIEN_THI_DS13B07()
{
   
   LCD_COMMAND (0x8C);
   LCD_DATA (GIO_DS13 / 16 + 0X30); LCD_DATA (GIO_DS13 % 16 + 0X30) ;
   LCD_DATA (' ');
   LCD_DATA (PHUT_DS13 / 16 + 0X30); LCD_DATA (PHUT_DS13 % 16 + 0X30);
   LCD_DATA (' ');
   LCD_DATA (GIAY_DS13 / 16 + 0X30); LCD_DATA (GIAY_DS13 % 16 + 0X30);
   LCD_COMMAND (0xCC);
   LCD_DATA (NGAY_DS13 / 16 + 0X30); LCD_DATA (NGAY_DS13 % 16 + 0X30);
   LCD_DATA (' ');
   LCD_DATA (THANG_DS13 / 16 + 0X30); LCD_DATA (THANG_DS13 % 16 + 0X30);
   LCD_DATA (' ');
   LCD_DATA (NAM_DS13 / 16 + 0X30); LCD_DATA (NAM_DS13 % 16 + 0X30);
   lcd_goto_xy (1, 8) ;
   lcd_data (thu_ds13 + 0x30);
   lcd_data (' ');
   lcd_goto_xy (2, 12) ;
   LCD_DATA (GIO / 16 + 0X30); LCD_DATA (GIO % 16 + 0X30) ;
   LCD_DATA (' ');
   LCD_DATA (PHUT / 16 + 0X30); LCD_DATA (PHUT % 16 + 0X30);
   LCD_DATA (' ');
   LCD_DATA (GIAY / 16 + 0X30); LCD_DATA (GIAY % 16 + 0X30);
   lcd_goto_xy (1, 9) ;

   if (thu_ds13 == 0||thu_ds13 == 7)
      lcd_data ("CN");

   else if (thu_ds13 == 1)
      lcd_data ("T2");

   else if (thu_ds13 == 2)
      lcd_data ("T3");

   else if (thu_ds13 == 3)
      lcd_data ("T4");

   else if (thu_ds13 == 4)
      lcd_data ("T5");

   else if (thu_ds13 == 5)
      lcd_data ("T6");

   else if (thu_ds13 == 6)
      lcd_data ("T7");

   lcd_goto_xy (2, 0);
   lcd_data ("hen gio");
}

void hen_gio()
{
   if (gio == gio_ds13)
   {
      if (phut == phut_ds13)
      {
         if (giay == giay_ds13)
         {
            if (bdn_h < 10)
            {
               XUAT_32LED_DON_4BYTE (0, 0, 0, 0xff) ;
               giay_buzzer++;
               if (giay_buzzer == 5)
                  XUAT_32LED_DON_4BYTE (0, 0, 0,0) ;  
            }

            else
            bdn_h = bdn_h - 10;
         }
      }
   }
}

   void main  ()
   {
      set_up_port_ic_chot ();
      setup_lcd ();
      lcd_command (lcd_addr_line1);
      lcd_data ("clock:");
      doc_thoi_gian_tu_realtime ();

      if (ma_ds13 != ma_ds)
      {
         thiet_lap_thoi_gian_hien_tai ();
         nap_thoi_gian_htai_vao_ds13b07 ();
      }

      giatri_mod = 0;
      hien_thi_gia_tri_mod ();
      doc_thoi_gian_tu_realtime ();
      giaytam = giay_ds13;

      while (true)
      {
         doc_thoi_gian_tu_realtime ();
         HIEN_THI_DS13B07 () ;

         if (giaytam != giay_ds13)
         {
            giaytam = giay_ds13;

            if (bdn < 10)
            {
               if (giatri_mod != 0)
               {
                  if (bdn < 5)
                     nhap_nhay ();
                  else if (bdn < 10)
                  {
                     
                     HIEN_THI_DS13B07 () ;
                  }
               }
            }

            else
            bdn = bdn - 10;
            hien_thi_gia_tri_mod ();
            hen_gio () ;
         }

         for (k = 0; k < 10000; k++)
         {
            phim_mod ();
            phim_up ();
            phim_dw ();
         }

         if (giatri_mod != 0)
            nhap_nhay_con_tro ();
      }
   }

