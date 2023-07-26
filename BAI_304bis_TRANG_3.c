//! #include <tv_pickit2_shift_1.c>
#include <TV_PICKIT2_SHIFT_1_PROTEUS.C>
unsigned int8 y,i;
void main()
{
    set_up_port_ic_chot();
    y = 0;
    while (true)
    {    
         y = 0;
         xuat_32led_don_4byte(0, 0, 0, y);
         delay_ms(200);
        for (i = 0; i < 8; i++)
        {
            y = (y << 1) + 1;
            xuat_32led_don_4byte(0, 0, 0, y);
            delay_ms(200);
            
        }
        y = 0;
        xuat_32led_don_4byte(0, 0, 0, y);
        delay_ms(200);
        for (i = 0; i < 8; i++)
        {
            y = (y >> 1) + 0x80;
            xuat_32led_don_4byte(0, 0, 0, y);
            delay_ms(200);
            
        }
        
    }
}
