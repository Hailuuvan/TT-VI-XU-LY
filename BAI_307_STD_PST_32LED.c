//! #include <tv_pickit2_shift_1.c>
#include <TV_PICKIT2_SHIFT_1_PROTEUS.C>
unsigned int32 y;
unsigned int8 i;
void main()
{
    set_up_port_ic_chot();
    y = 0;
    while (true)
    {
        for (i = 0; i < 32; i++)
        {
            xuat_32led_don_1dw(y);
            delay_ms(300);
            y = (y << 1) + 1;
            
        }

        for (i = 0; i < 32; i++)
        {
            xuat_32led_don_1dw(y);
            delay_ms(300);
            y = (y << 1);
            
        }
    }
}
