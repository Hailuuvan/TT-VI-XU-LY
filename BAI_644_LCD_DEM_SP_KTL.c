#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_lcd.c>
unsigned int8 t0, tr, ch, dv;
signed int8 i,dem;
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
    
    tr = t0 / 100 ;
    ch = t0 / 10 % 10 ;
    dv = t0 % 10 ;
    //xoa so 0 vn
    if (tr == 0)
    {
        tr = 10;
        if(ch == 0)
            ch = 10;
    }
    lcd_hienthi_so_z_toado_xy(tr, 2, 0);
    lcd_hienthi_so_z_toado_xy(ch, 2, 4);
    lcd_hienthi_so_z_toado_xy(dv, 2, 8);

}
void main()
{
    set_up_port_ic_chot();
    setup_lcd();
    setup_timer_0(t0_ext_l_to_h | t0_div_1 | t0_8_bit);
    set_timer0(0);
    lcd_command(0x40);
    for (i = 0; i < 64; i++)
    {
        lcd_data(lcd_ma_8doan[i]);
    }
    
    while (true)
    {
        t0 = get_timer0();
        xuat_4led_7doan_3so(ma7doan[t0 / 100], ma7doan[t0 / 10 % 10], ma7doan[t0 % 10]);
        lcd_goto_xy(0, 0);
        lcd_data("**DEM SAN PHAM**");
        delay_us(20);
        hienthi_lcd();
        delay_ms(100);
        if (t0 >= 101)
            set_timer0(1);
    }
}
