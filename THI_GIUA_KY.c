#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_lcd.c>
#include <tv_pickit2_shift_key4x4_138.c>
signed int8 mp, i, t0, bdn;
signed int8 chuc, donvi,dem,ch_lcd,dv_lcd, box, ch_box, dv_box;
signed int8 gt_cai_tren = 0 , gt_cai_duoi = 0, gt_cai_sp = 11;
signed int8 ch_tren = 0xc0, dv_tren , ch_duoi , dv_duoi, cai_lcd2 = 0, cai_lcd1 = 0;
unsigned int8 array1[2] = {4,2};  //gh tren
unsigned int8 array2[2] = {1,1};  //gh duoi
int1 tt_ss, tt_dem;
unsigned int8 tt_ht;
#int_timer1
void interrupt_timer1()
{
    bdn++;
    set_timer1(3036);
}
void giai_ma_led_7doan_quet()
{
    led_7dq[1] = 0xf1;    //1111 0001
    led_7dq[2] = 0xc7 & 0x7f;
    chuc = dem/10%10;
    donvi = dem%10;
    led_7dq[3] = ma7doan[donvi];
    led_7dq[4] = ma7doan[chuc];
    led_7dq[5] = 0xf1;
    led_7dq[6] = 0xc7 & 0x7f;
    // if (chuc == 0)
    //     led_7dq[4] = 0xff;
}

void cai_gt_4x4()
{
    if(tt_ht == 0)
    {
        array1[1] = array1[0];
        array1[0] = mp ;
        gt_cai_tren = (array1[1])* 10 + (array1[0]);
        ch_tren = ma7doan[gt_cai_tren/10%10];
        dv_tren = ma7doan[gt_cai_tren%10];
    }
    else if(tt_ht == 1) 
    {
        array2[1] = array2[0];
        array2[0] = mp;
        gt_cai_duoi = (array2[1])*10 + (array2[0] ) ;
        ch_duoi = ma7doan[gt_cai_duoi/10%10];
        dv_duoi = ma7doan[gt_cai_duoi%10];
        
    }
}
void hien_thi_ban_dau()
{
   gt_cai_tren = (array1[1]) * 10 + (array1[0]) ;
   ch_tren = ma7doan[gt_cai_tren/10%10];
   dv_tren = ma7doan[gt_cai_tren%10];
   
   gt_cai_duoi = (array2[1])*10 + (array2[0] ) ;
   ch_duoi = ma7doan[gt_cai_duoi/10%10];
   dv_duoi = ma7doan[gt_cai_duoi%10];
   
   XUAT_4LED_7DOAN_4SO(ch_tren, dv_tren, ch_duoi, dv_duoi);
   lcd_goto_xy(3,10);
   lcd_data("CD:");
}
void GM_LCD()
{
   ch_lcd=t0/10%10;
   dv_lcd=t0%10;
   if(ch_lcd==0) 
      ch_lcd=10;
      
   ch_box = box/10%10;
   dv_box = box%10;
   if(ch_box == 0)
      ch_box = 10;
}
void xu_ly_nhap_nhay()
{
    if(tt_ht == 0)
    {
        if(bdn < 7)
        {
            if (bdn == 0)
                  XUAT_4LED_7DOAN_4SO(ch_tren, dv_tren, ch_duoi, dv_duoi);
            if(bdn == 4)
                  XUAT_4LED_7DOAN_4SO(0xff, 0xff, ch_duoi, dv_duoi);
        }
    }
    else if(tt_ht == 1)
    {
         if(bdn < 7)
        {
            if (bdn == 0)
                  XUAT_4LED_7DOAN_4SO(ch_tren, dv_tren, ch_duoi, dv_duoi);
            if(bdn == 4)
                  XUAT_4LED_7DOAN_4SO(ch_tren, dv_tren,0xff, 0xff);
        }        
    }
//!    else if(tt_ht == 2)
//!    {
//!      if(bdn < 7)
//!        {
//!            if (bdn == 0)
//!                  lcd_goto_xy(3,13);
//!                  lcd_data(0x20);
//!                  lcd_data(0x20);
//!            if(bdn == 4)
//!            {
//!                 GM_LCD();
//!            }
//!        }
//!    }
     }
void lcd_hienthi_so_z_toado_xy(signed int8 lcd_so, x1, y1)
{
    lcd_goto_xy(x1, y1);
    for (i = 0; i < 6; i++)
    {
        if (i == 3)
            lcd_goto_xy(x1 + 1, y1);
        lcd_data(lcd_so_x[lcd_so][i]);
        hien_thi_8led_7doan_quet();
    }
}



void hien_thi_lcd()
{
    lcd_goto_xy(0,0);
    lcd_hienthi_so_z_toado_xy(5, 0, 0);
    lcd_data(":  ");
//!    lcd_hienthi_so_z_toado_xy(0,0,4);
//!    lcd_hienthi_so_z_toado_xy(0,0,8);
    lcd_command(0x40);
    for (i = 0; i < 64; i++)
    {
        lcd_data(lcd_ma_8doan[i]);
        hien_thi_8led_7doan_quet();
    }
   
    t0 = get_timer0();
    lcd_hienthi_so_z_toado_xy(ch_lcd,0,4);
    lcd_hienthi_so_z_toado_xy(dv_lcd,0,8);
    lcd_data("_");
    if (t0 > gt_cai_sp)
    {
      set_timer0(1);
      box++;
    }
    lcd_hienthi_so_z_toado_xy(ch_box,0,12);
    lcd_hienthi_so_z_toado_xy(dv_box,0,15);
    //cai_gt_4x4();
    
}
// xxxxxxxxxxxxxxxx
// xu ly cac phim nhan
void phim_ss()
{
   if(mp != 0xff && mp == 10)
   {
      tt_ss =~ tt_ss;
      do{hien_thi_8led_7doan_quet();}
      while(mp == 10);
   }
}

void phim_tt_dem_sp()
{
   if(mp != 0xff && mp == 11)
   {
      tt_dem =~ tt_dem;
      do{hien_thi_8led_7doan_quet();}
      while(mp == 11);
   }
}
void cai_dat_so_sp()
{
   if(tt_ht == 2)
   {
      cai_lcd2 = cai_lcd1;
      cai_lcd1 = mp;
      gt_cai_sp = (cai_lcd2)*10 + (cai_lcd1);
      lcd_goto_xy(3,10);
      lcd_data("CD:");
      lcd_data(gt_cai_sp/10 + 0x30);
      lcd_data(gt_cai_sp%10 + 0x30);
      
   }
}
void delay_hienthi(unsigned int8 dl)
{
   for (i = 0; i< dl;i++)
   {
      delay_ms(1);
      hien_thi_8led_7doan_quet();
   }
}
void dao_vitri_chinh()
{
    if(mp == 15)
    {
        tt_ht++;
        if(tt_ht == 3) //
            tt_ht = 0;
    }
}

void main()
{
    set_up_port_ic_chot();
    setup_timer_1(t1_internal | t1_div_by_8);
    set_timer1(3036);
    enable_interrupts(global);
    enable_interrupts(int_timer1);
    setup_timer_0(t0_ext_l_to_h | t0_div_1 | t0_8_bit);
    set_timer0(0);
    setup_lcd();
    bdn  = 0;
    dem = 24;
    tt_ht = 0; //
    box = 0; ch_lcd = 0;dv_lcd=0; tt_dem = 0; tt_ss = 0;
    hien_thi_ban_dau();
    while (true)
    {
        phim_tt_dem_sp();
        phim_tt_dem_sp();
        mp = key_4x4_dw();
        XUAT_4LED_7DOAN_4SO(ch_tren, dv_tren, ch_duoi, dv_duoi);
         if(tt_ss == 0)
         {
           giai_ma_led_7doan_quet();
           if (bdn < 7)
           {
               //hien_thi_8led_7doan_quet();
   //!            delay_us(20);
               delay_hienthi(20);
               
           }
           else
           {
               bdn = bdn - 7;
               dem--;
               if (dem == gt_cai_duoi - 1)
               {
                   dem = gt_cai_tren;
               }
           }
         }
         else setup_timer_0(t0_off);
            
        dao_vitri_chinh();
        if(mp != 0xff && mp < 10)
        {
            cai_gt_4x4();
            cai_dat_so_sp();    
        }
        xu_ly_nhap_nhay();
        if(tt_dem == 0)
        {
           GM_LCD();
           hien_thi_lcd();
        }
        else setup_timer_1(t1_disabled);
    }
}
