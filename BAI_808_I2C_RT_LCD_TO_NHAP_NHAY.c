
//!#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_1_proteus.c>
#include <TV_PICKIT2_SHIFT_DS1307_I2C.c>

unsigned int16 k, ch_gio, ch_phut, ch_giay;
unsigned char giatri_mod;
signed int8 i,bdn;
#int_timer1
void interrupt_timer1()
{
   bdn++;
   set_timer1(3036);
}
void hien_thi_gia_tri_mod ( )
{
   lcd_command (0x8a);
   xuat_4led_7doan_4so(ma7doan[giatri_mod],0xff,0xff,0xff) ;
}

void phim_mod()
{
   if (!input (mod))
   {
      delay_ms (20);
      {
         if (!input (mod))
         {
            if (giatri_mod < 4) giatri_mod++;
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
            
            CASE 4: if (THU_DS13 == 7) THU_DS13 = 1;

            else
            {
               THU_DS13++;
               THU_DS13 = HIEU_CHINH_SO_BCD_TANG (THU_DS13) ;
            }

            LUU_GIAI_MA_HIEN_THI_SAU_KHI_CHINH ();
            break;
            default: break;
         }

         while ( ! input (up)) ;
      }
   }
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

void HIEN_THI_DS13B07()
{
   ch_gio = gio_ds13/16;
   if(ch_gio == 0)
      ch_gio = 10;
   lcd_hienthi_so_z_toado_xy(ch_gio, 0, 0);
   lcd_hienthi_so_z_toado_xy(gio_ds13%16, 0, 4);
   
   ch_phut = phut_ds13/16;
   if(ch_phut == 0)
      ch_phut = 10;
   lcd_hienthi_so_z_toado_xy(ch_phut, 0, 14);
   lcd_hienthi_so_z_toado_xy(phut_ds13%16, 0, 17);

   ch_giay = giay_ds13/16;
   if(ch_giay == 0)
      ch_giay = 10;
   lcd_hienthi_so_z_toado_xy(ch_giay, 2, 0);
   lcd_hienthi_so_z_toado_xy(giay_ds13%16, 2, 4);
   
   lcd_hienthi_so_z_toado_xy(thu_ds13%16, 2, 17);   
}
void nhap_nhay()
{
   if(giatri_mod == 1)
   {
      lcd_hienthi_so_z_toado_xy(10, 2, 4);
      lcd_hienthi_so_z_toado_xy(10, 2, 17);
   }
   else if(giatri_mod == 2)
   {
      lcd_hienthi_so_z_toado_xy(10, 0, 4);
      lcd_hienthi_so_z_toado_xy(10, 0, 17);
   }
   else if(giatri_mod == 3)
   {
      lcd_hienthi_so_z_toado_xy(10, 0, 4);
      lcd_hienthi_so_z_toado_xy(10, 0, 0);
   }
   else if(giatri_mod == 4)
      lcd_hienthi_so_z_toado_xy(10, 2, 17);
    
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
         
            

            CASE 4: if (THU_DS13 == 1)
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
   setup_timer_1(t1_internal | t1_div_by_8);
   set_timer1(3036);
   enable_interrupts(global);
   enable_interrupts(int_timer1);
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
   lcd_command(0x40);
   for (i=0;i<64;i++) { lcd_data(lcd_ma_8doan[i]); }
   while (true)
   {
      doc_thoi_gian_tu_realtime ();

         if (giaytam != giay_ds13)
         {
            giaytam = giay_ds13;
            if(bdn < 10)
            {
               if(giatri_mod != 0)
               {
                  if(bdn < 5)
                     nhap_nhay();
                  else if(bdn < 10)
                     HIEN_THI_DS13B07() ;
               }
            }
         }

         else
         bdn = bdn - 10;
         HIEN_THI_DS13B07 () ;
        

      for (k = 0; k < 10000; k++)
      {
         phim_mod (); phim_up (); phim_dw () ;
      }

      if (giatri_mod != 0) nhap_nhay_con_tro () ;
   }
}


