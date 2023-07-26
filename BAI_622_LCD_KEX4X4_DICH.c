#include <tv_pickit2_shift_1.c>
//! #include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_lcd.c>
#include <tv_pickit2_shift_key4x4_138.c>
signed int8 mp, i;
unsigned int8 array[20] = {0XFE, 0XFE, 0XFE, 0XFE, 0XFE, 0XFE, 0XFE, 0XFE, 0XFE, 0XFE,
                           0XFE, 0XFE, 0XFE, 0XFE, 0XFE, 0XFE, 0XFE, 0XFE, 0XFE, 0XFE};
void giai_ma_lcd()
{
    for (i = 19; i >= 0; i--)
        array[i] = array[i - 1];
    if (mp < 10)
        array[0] = mp + 0x30;
    else
        array[0] = mp + 0x37;
}
void hienthi_lcd()
{
    lcd_goto_xy(1, 0);
    for (i = 19; i >= 0; i--)
        lcd_data(array[i]);
}
void main()
{
    set_up_port_ic_chot();
    setup_lcd();

    lcd_goto_xy(0, 0);
    lcd_data("HAY NHAN PHIM:");

    while (true)
    {
        mp = key_4x4_up();
        delay_ms(100);
        if (mp != 0xff)
        {
            giai_ma_lcd();
            hienthi_lcd();
        }
    }
}
