#include <TV_PICKIT2_SHIFT_1_PROTEUS.C>
//! #include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_key4x4_138.c>
// CONST unsigned char LED7[4] = {0X7F, 0X7F, 0X7F, 0X7F};
unsigned int8 mp;
unsigned int8 y3, y2, y1, y0;

void hien_thi_led_7_doan_tu_ban_phim()
{

    y3 = y2;
    y2 = y1;
    y1 = y0;

    y0 = ma7doan[mp];
}
void main()
{
    set_up_port_ic_chot();
    set_tris_b(0x3c);
    y0 = y1 = y2 = y3 = 0X7F;
    xuat_4led_7doan_4so(y3, y2, y1, y0);
    WHILE(true)
    {
        mp = key_4x4_dw();
        delay_ms(50);
        {
            if (mp != 0xff)
            {
                hien_thi_led_7_doan_tu_ban_phim();
                XUAT_4LED_7DOAN_4SO(y3, y2, y1, y0);
            }
        }
    }
}