#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_lcd.c>
signed int8 giay, bdn, phut, gio;
#int_timer1
void interrupt_timer1()
{
    bdn++;
    set_timer1(3036);
}

void lcd_hienthi_dongho()
{
    lcd_goto_xy(0, 12);
    delay_us(20);
    lcd_data(gio / 10 + 0x30);
    lcd_data(gio % 10 + 0x30);
    lcd_data(' ');
    lcd_data(phut / 10 + 0x30);
    lcd_data(phut % 10 + 0x30);
    lcd_data(' ');
    lcd_data(giay / 10 + 0x30);
    lcd_data(giay % 10 + 0x30);
} 
void main()
{
    set_up_port_ic_chot();
    setup_timer_1(t1_internal | t1_div_by_8);
    set_timer0(3036);
    enable_interrupts(global);
    enable_interrupts(int_timer1);
    setup_lcd();
    giay = 0;
    bdn = 0;
    phut = 0;
    gio = 0;
    lcd_goto_xy(0,0);
    lcd_data("dong ho:");
    while (true)
    {
        
        if (bdn < 10)
            lcd_hienthi_dongho();
        else
        {
            bdn = bdn - 10;
            giay++;
            if (giay == 60)
            {
                giay = 0;
                phut ++ ;
                if(phut == 60)
                {
                    gio++;
                    phut = 0;
                } 
            }
        }
        delay_ms(200);
    }
}
