#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_lcd.c>
signed int8 giay, phut;
void lcd_hienthi_dongho()
{
    lcd_goto_xy(0, 16);
    delay_us(20);
    lcd_data(phut / 10 + 0x30);
    lcd_data(phut % 10 + 0x30);

    lcd_data(giay / 10 + 0x30);
    lcd_data(giay % 10 + 0x30);
}  
void main()
{
    set_up_port_ic_chot();
    setup_lcd();
    lcd_goto_xy(0, 0);
    lcd_data("dong ho:");
    giay = 57;
    phut = 0;
    while(true)
    {
        lcd_hienthi_dongho();
        delay_ms(1000);
        giay++;
        if(giay == 60)
            {
                giay = 0;
                phut++;
            }

    }
}