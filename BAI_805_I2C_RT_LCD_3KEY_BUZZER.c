//!#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_1_proteus.c>
#include <TV_PICKIT2_SHIFT_DS1307_I2C.c>

unsigned int16 k, bdn, giay;
unsigned char giatri_mod;

#int_timer1
void interrupt_timer1()
{
    bdn++;
    set_timer1(3036);
}
void hien_thi_gia_tri_mod()
{
   lcd_command(0x8a);
   lcd_data(giatri_mod + 0x30);
}

void phim_mod()
{
   if (!input(mod))
   {
      delay_ms(20);
      {
         if (!input(mod))
         {
            if (giatri_mod < 6)
               giatri_mod++;
            else
               giatri_mod = 0;
            hien_thi_gia_tri_mod();
            while (!input(mod));
              
         }
      }
   }
}

unsigned int8 hieu_chinh_so_bcd_tang(unsigned int8 x)
{
   unsigned int8 y;
   y = x;
   x = x & 0x0f;
   if (x == 0x0a)
      y = y + 6;
   return (y);
}

unsigned int8 hieu_chinh_so_bcd_giam(unsigned int8 x)
{
   unsigned int8 y;
   y = x;
   x = x & 0x0f;
   if (x == 0x0f)
      y = y - 6;
   return (y);
}

void luu_giai_ma_hien_thi_sau_khi_chinh()
{
   nap_thoi_gian_htai_vao_ds13b07();
   hien_thi_thoi_gian_ds13b07();
}

void phim_up()
{
   if (!input(up))
   {
      delay_ms(20);

      if (!input(up))
      {
         switch (giatri_mod)
         {
         case 1:
            if (giay_ds13 == 0x59)
               giay_ds13 = 0;

            else
            {
               giay_ds13++;
               giay_ds13 = hieu_chinh_so_bcd_tang(giay_ds13);
            }

            luu_giai_ma_hien_thi_sau_khi_chinh();
            break;
         case 2:
            if (phut_ds13 == 0x59)
               phut_ds13 = 0;

            else
            {
               phut_ds13++;
               phut_ds13 = hieu_chinh_so_bcd_tang(phut_ds13);
            }

            luu_giai_ma_hien_thi_sau_khi_chinh();
            break;
         case 3:
            if (gio_ds13 == 0x23)
               gio_ds13 = 0;

            else
            {
               gio_ds13++;
               gio_ds13 = hieu_chinh_so_bcd_tang(gio_ds13);
            }

            luu_giai_ma_hien_thi_sau_khi_chinh();
            break;
         case 4:
            if (ngay_ds13 == 0x31)
               ngay_ds13 = 1;

            else
            {
               ngay_ds13++;
               ngay_ds13 = hieu_chinh_so_bcd_tang(ngay_ds13);
            }

            luu_giai_ma_hien_thi_sau_khi_chinh();
            break;
         case 5:
            if (thang_ds13 == 0x12)
               thang_ds13 = 1;

            else
            {
               thang_ds13++;
               thang_ds13 = hieu_chinh_so_bcd_tang(thang_ds13);
            }

            luu_giai_ma_hien_thi_sau_khi_chinh();
            break;
         case 6:
            if (nam_ds13 == 0x99)
               nam_ds13 = 0;

            else
            {
               nam_ds13++;
               nam_ds13 = hieu_chinh_so_bcd_tang(nam_ds13);
            }

            luu_giai_ma_hien_thi_sau_khi_chinh();
            break;
         default:
            break;
         }

         while (!input(up));
            
      }
   }
}

void phim_dw()
{
   if (!input(dw))
   {
      delay_ms(20);

      if (!input(dw))
      {
         switch (giatri_mod)
         {
         case 1:
            if (giay_ds13 == 0)
               giay_ds13 = 0x59;

            else
            {
               giay_ds13--;
               giay_ds13 = hieu_chinh_so_bcd_giam(giay_ds13);
            }

            luu_giai_ma_hien_thi_sau_khi_chinh();
            break;
         case 2:
            if (phut_ds13 == 0)
               phut_ds13 = 0x59;

            else
            {
               phut_ds13--;
               phut_ds13 = hieu_chinh_so_bcd_giam(phut_ds13);
            }

            luu_giai_ma_hien_thi_sau_khi_chinh();
            break;
         case 3:
            if (gio_ds13 == 0)
               gio_ds13 = 0x23;

            else
            {
               gio_ds13--;
               gio_ds13 = hieu_chinh_so_bcd_giam(gio_ds13);
            }

            luu_giai_ma_hien_thi_sau_khi_chinh();
            break;
         case 4:
            if (ngay_ds13 == 0)
               ngay_ds13 = 0x31;

            else
            {
               ngay_ds13--;
               ngay_ds13 = hieu_chinh_so_bcd_giam(ngay_ds13);
            }

            luu_giai_ma_hien_thi_sau_khi_chinh();
            break;
         case 5:
            if (thang_ds13 == 1)
               thang_ds13 = 0x12;

            else
            {
               thang_ds13--;
               thang_ds13 = hieu_chinh_so_bcd_giam(thang_ds13);
            }

            luu_giai_ma_hien_thi_sau_khi_chinh();
            break;
         case 6:
            if (nam_ds13 == 0)
               nam_ds13 = 0x99;

            else
            {
               nam_ds13--;
               nam_ds13 = hieu_chinh_so_bcd_giam(nam_ds13);
            }

            luu_giai_ma_hien_thi_sau_khi_chinh();
            break;
         default:
            break;
         }

         while (!input(dw));
            
      }
   }
}

void nhap_nhay_con_tro()
{
   switch (giatri_mod)
   {
   case 1:
      lcd_command(0xd3);
      break;
   case 2:
      lcd_command(0xd0);
      break;
   case 3:
      lcd_command(0xcd);
      break;
   case 4:
      lcd_command(0x8d);
      break;
   case 5:
      lcd_command(0x90);
      break;
   case 6:
      lcd_command(0x93);
      break;
   default:
      break;
   }
}
void dk_buzzer()
{
   if(giay_ds13 == 0x59)
   {
      
      if(bdn < 10)
      {
         giay++;
         if(giay == 2)
            XUAT_32LED_DON_4BYTE(0,0,0,0xff);
         else
            XUAT_32LED_DON_4BYTE(0,0,0,0);
      }
      else 
         bdn = bdn - 10;
      
   }
}
void nhap_nhay()
{
   if(giatri_mod == 0)
   {
      LCD_COMMAND(0x8C);
      LCD_DATA(0x20);
      LCD_DATA(0x20);
      LCD_DATA(' ');
   }

   else if(giatri_mod == 1)
   {
      LCD_COMMAND(0x8f);
      LCD_DATA(0x20);
      LCD_DATA(0x20);
      LCD_DATA(' ');
   }
   else if(giatri_mod == 2)
   {
      LCD_COMMAND(0x92);
      LCD_DATA(0x20);
      LCD_DATA(0x20);
      LCD_DATA(' ');
   }
   else if(giatri_mod == 3)
   {
      LCD_COMMAND(0xd2);
      LCD_DATA(0x20);
      LCD_DATA(0x20);
      LCD_DATA(' ');
   }
   else if(giatri_mod == 4)
   {
      LCD_COMMAND(0xcf);
      LCD_DATA(0x20);
      LCD_DATA(0x20);
      LCD_DATA(' ');
   }
   else if(giatri_mod == 5)
   {
      LCD_COMMAND(0xcc);
      LCD_DATA(0x20);
      LCD_DATA(0x20);
      LCD_DATA(' ');
   }
}

void main()
{
   set_up_port_ic_chot();
   setup_lcd();
   lcd_command(lcd_addr_line1);
   lcd_data("clock:");
   doc_thoi_gian_tu_realtime();

   if (ma_ds13 != ma_ds)
   {
      thiet_lap_thoi_gian_hien_tai();
      nap_thoi_gian_htai_vao_ds13b07();
   }

   giatri_mod = 0;
   hien_thi_gia_tri_mod();
   doc_thoi_gian_tu_realtime();
   giaytam = giay_ds13;

   while (true)
   {
      doc_thoi_gian_tu_realtime();
      hien_thi_thoi_gian_ds13b07();
      delay_ms(200);
      dk_buzzer();
      if (giaytam != giay_ds13)
      {
         giaytam = giay_ds13;
         if(bdn < 10)
         {
            if(giatri_mod != 0)
            {
               if(bdn < 5)
                  hien_thi_thoi_gian_ds13b07();
               else if(bdn < 10)
               {
                  nhap_nhay();
                  delay_ms(100);  
               }
            }
            
         }
         else
            bdn = bdn - 10;
         hien_thi_gia_tri_mod();
      }

      for (k = 0; k < 10000; k++)
      {
         phim_mod();
         phim_up();
         phim_dw();
      }

      if (giatri_mod != 0)
         nhap_nhay_con_tro();
   }
}
