
#include <tv_pickit2_shift_1.c>
#include <TV_PICKIT2_SHIFT_DS1307_I2C.c>

unsigned int16 k;
unsigned char giatri_mod;

void hien_thi_gia_tri_mod ( )
{
   lcd_command (0x8a);
   lcd_data (giatri_mod + 0x30) ;

}

void phim_mod()
{
   if (!input (mod))
   {
      delay_ms (20);
      {
         if (!input (mod))
         {
            if (giatri_mod < 7) giatri_mod++;
            else giatri_mod = 0;
            hien_thi_gia_tri_mod ();
            while ( ! input (mod)) ;
         }
      }
   }
}

unsigned int8 hieu_chinh_so_bcd_tang(unsigned int8 x )
{
   unsigned int8 y;
   y = x;
   x = x&0x0f;
   if (x == 0x0a) y = y + 6;
   return (y);
}

unsigned int8 hieu_chinh_so_bcd_giam(unsigned int8 x )
{
   unsigned int8 y;
   y = x;
   x = x&0x0f;
   if (x == 0x0f) y = y - 6;
   return (y);
}

void luu_giai_ma_hien_thi_sau_khi_chinh()
{
   nap_thoi_gian_htai_vao_ds13b07 ();
   hien_thi_thoi_gian_ds13b07 ();
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
            case 1: if (giay_ds13 == 0x59) giay_ds13 = 0;

            else
            {
               giay_ds13++;
               giay_ds13 = hieu_chinh_so_bcd_tang (giay_ds13) ;
            }

            luu_giai_ma_hien_thi_sau_khi_chinh ();
            break;
            case 2: if (phut_ds13 == 0x59) phut_ds13 = 0;

            else
            {
               phut_ds13++;
               phut_ds13 = hieu_chinh_so_bcd_tang (phut_ds13) ;
            }

            luu_giai_ma_hien_thi_sau_khi_chinh ();
            break;
            case 3: if (gio_ds13 == 0x23) gio_ds13 = 0;

            else
            {
               gio_ds13++;
               gio_ds13 = hieu_chinh_so_bcd_tang (gio_ds13) ;
            }

            luu_giai_ma_hien_thi_sau_khi_chinh ();
            break;
            case 4: if (ngay_ds13 == 0x31) ngay_ds13 = 1;

            else
            {
               ngay_ds13++;
               ngay_ds13 = hieu_chinh_so_bcd_tang (ngay_ds13) ;
            }

            luu_giai_ma_hien_thi_sau_khi_chinh ();
            break;
            case 5: if (thang_ds13 == 0x12) thang_ds13 = 1;

            else
            {
               thang_ds13++;
               thang_ds13 = hieu_chinh_so_bcd_tang (thang_ds13) ;
            }

            luu_giai_ma_hien_thi_sau_khi_chinh ();
            break;
            case 6: if (nam_ds13 == 0x99) nam_ds13 = 0;

            else
            {
               nam_ds13++;
               nam_ds13 = hieu_chinh_so_bcd_tang (nam_ds13) ;
            }

            luu_giai_ma_hien_thi_sau_khi_chinh ();
            break;
            CASE 7: if (THU_DS13 == 7) THU_DS13 = 1;

            else
            {
               THU_DS13++;
               THU_DS13 = HIEU_CHINH_SO_BCD_TANG (THU_DS13) ;
            }
            LUU_GIAI_MA_HIEN_THI_SAU_KHI_CHINH () ;
            break;
            default: break;
         }

         while ( ! input (up)) ;
      }
   }
}
void HIEN_THI_DS13B07()
{     
      LCD_COMMAND (0x8C);
      LCD_DATA(GIO_DS13/16  +0X30);    LCD_DATA(GIO_DS13%16  +0X30);
      LCD_DATA(' ');
      LCD_DATA(PHUT_DS13/16 +0X30);    LCD_DATA(PHUT_DS13%16 +0X30);
      LCD_DATA(' ');
      LCD_DATA(GIAY_DS13/16 +0X30);    LCD_DATA(GIAY_DS13%16 +0X30);
      LCD_COMMAND (0xCC);  
      LCD_DATA(NGAY_DS13/16 +0X30);    LCD_DATA(NGAY_DS13%16 +0X30);
      LCD_DATA(' ');
      LCD_DATA(THANG_DS13/16 +0X30);   LCD_DATA(THANG_DS13%16 +0X30);
      LCD_DATA(' ');
      LCD_DATA(NAM_DS13/16 +0X30);     LCD_DATA(NAM_DS13%16 +0X30); 
      lcd_goto_xy(1,8);
      lcd_data(thu_ds13 + 0x30);
      lcd_data(' ');
      if(thu_ds13 == 0)
      lcd_data("CN");
      else if(thu_ds13 == 1)
      lcd_data("T2");
      else if(thu_ds13 == 2)
      lcd_data("T3");
      else if(thu_ds13 == 3)
      lcd_data("T4");
      else if(thu_ds13 == 4)
      lcd_data("T5");
      else if(thu_ds13 == 5)
      lcd_data("T6");
      else if(thu_ds13 == 6)
      lcd_data("T7");
      
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
            case 1: if (giay_ds13 == 0) giay_ds13 = 0x59;

            else
            {
               giay_ds13--;
               giay_ds13 = hieu_chinh_so_bcd_giam (giay_ds13) ;
            }

            luu_giai_ma_hien_thi_sau_khi_chinh ();
            break;
            case 2: if (phut_ds13 == 0) phut_ds13 = 0x59;

            else
            {
               phut_ds13--;
               phut_ds13 = hieu_chinh_so_bcd_giam (phut_ds13) ;
            }

            luu_giai_ma_hien_thi_sau_khi_chinh ();
            break;
            case 3: if (gio_ds13 == 0) gio_ds13 = 0x23;

            else
            {
               gio_ds13--;
               gio_ds13 = hieu_chinh_so_bcd_giam (gio_ds13) ;
            }

            luu_giai_ma_hien_thi_sau_khi_chinh ();
            break;
            case 4: if (ngay_ds13 == 0) ngay_ds13 = 0x31;

            else
            {
               ngay_ds13--;
               ngay_ds13 = hieu_chinh_so_bcd_giam (ngay_ds13) ;
            }

            luu_giai_ma_hien_thi_sau_khi_chinh ();
            break;
            case 5: if (thang_ds13 == 1) thang_ds13 = 0x12;

            else
            {
               thang_ds13--;
               thang_ds13 = hieu_chinh_so_bcd_giam (thang_ds13) ;
            }

            luu_giai_ma_hien_thi_sau_khi_chinh ();
            break;
            case 6: if (nam_ds13 == 0) nam_ds13 = 0x99;

            else
            {
               nam_ds13--;
               nam_ds13 = hieu_chinh_so_bcd_giam (nam_ds13) ;
            }

            luu_giai_ma_hien_thi_sau_khi_chinh ();
            break;
            CASE 7: if (THU_DS13 == 1)
               THU_DS13 = 7;
            else
            {
               THU_DS13--;
               THU_DS13 = HIEU_CHINH_SO_BCD_TANG (THU_DS13) ;
            }

            LUU_GIAI_MA_HIEN_THI_SAU_KHI_CHINH ();
            break;
            default: break;
         }

         while (! input (dw)) ;
      }
   }
}

void nhap_nhay_con_tro()
{
   switch (giatri_mod)
   {
      case 1: lcd_command (0xd3);
      break;
      case 2: lcd_command (0xd0);
      break;
      case 3: lcd_command (0xcd);
      break;
      case 4: lcd_command (0x8d);
      break;
      case 5: lcd_command (0x90);
      break;
      case 6: lcd_command (0x93);
      break;
      default: break;
   }
}


void main()
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

      if (giaytam != giay_ds13)
      {
         giaytam = giay_ds13;
         hien_thi_gia_tri_mod ();
         HIEN_THI_DS13B07();
      }

      for (k = 0; k < 10000; k++)
      {
         phim_mod (); phim_up (); phim_dw () ;
      }

      if (giatri_mod != 0) nhap_nhay_con_tro () ;
   }
}

