#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_lcd.c>
#define nd_tren 40
#define nd_duoi 40
unsigned int8 j,i,ch,dv, solan = 100;
unsigned int16 lm35a;
//int1 ttqn = 0;
void lcd_hienthi_so_z_toado_xy(signed int8 lcd_so, x1, y1)
{
    lcd_goto_xy(x1, y1);
    for (i = 0; i < 6; i++)
    {
        if (i == 3)
            lcd_goto_xy(x1 + 1, y1);
        lcd_data(lcd_so_x[lcd_so][i]);
    }
}
void hienthi_lcd()
{
    ch = lm35a / 10  ;
    dv = lm35a % 10 ;
    //xoa so 0 vn
        if(ch == 0)
            ch = 10;
    lcd_hienthi_so_z_toado_xy(ch, 2, 4);
    lcd_hienthi_so_z_toado_xy(dv, 2, 8);

}
void so_sanh_dk_buzzer()
{
    if (lm35a > nd_tren)
    {
        //ttqn = 1;
        xuat_32led_don_4byte(0,0,0,0xff);
        triac_2_off();
    }
    else if (lm35a < nd_tren)
    {
        //ttqn = 0;
        xuat_32led_don_4byte(0,0,0,0);
    if (lm35a < nd_duoi)
        triac_2_on();
}
}

void main()
{
    set_up_port_ic_chot();
    setup_adc(adc_clock_div_32);
    setup_adc_ports(an0 | vss_vdd);
    set_adc_channel(0);
    SETUP_LCD();
    //ttqn = 0;
    lcd_command(0x40);
    for (i = 0; i < 64; i++)
    {
        lcd_data(lcd_ma_8doan[i]);
    }
    while (true)
    {
        
        lm35a = 0;
        for (j = 0; j < solan; j++)
        {
            lm35a = lm35a + read_adc();
            delay_ms(1);
        }
        lm35a = lm35a / 2.046;
        lm35a = lm35a / solan;
        xuat_4led_7doan_giaima_xoa_so0(lm35a);
        so_sanh_dk_buzzer();
        hienthi_lcd();
    }
}

