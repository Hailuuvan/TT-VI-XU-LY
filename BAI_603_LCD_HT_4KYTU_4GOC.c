#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_lcd.c>
void main()
{
    set_up_port_ic_chot();
    setup_lcd();
    lcd_command(lcd_addr_line1);
    lcd_data("A                  B");
    lcd_data("C                  D");
    
}