//!#include <TV_PICKIT2_SHIFT_1_PROTEUS.C>
 #include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_key4x4_138.c>
unsigned char led7[8] = {0X7F, 0X7F, 0X7F, 0X7F, 0X7F, 0X7F, 0X7F, 0X7F};
unsigned char ma_4led[4] = {0X7F, 0X7F, 0X7F, 0X7F};

unsigned int8 mp;
unsigned int8 dem_ud,i;
void hien_thi_4led_7doan()
{
    for(i = 0; i < 4; i++)
    {
        ma_4led[i] = led7[i + 4];
    }
        xuat_4led_7doan_4so(ma_4led[0], ma_4led[1], ma_4led[2], ma_4led[3]);
}
void dich_led_thuan()
{
    for(i = 0; i < 7; i++)
        led7[i] = led7[i + 1];
    led7[7] = ma7doan[mp];
    if(dem_ud < 4)
        dem_ud ++;
    hien_thi_4led_7doan();
}
void phim_undo()
{
    if(dem_ud > 0)
    {
        for(i = 7; i > 0; i--)
        led7[i] = led7[i - 1];
        dem_ud-- ;

    }
    hien_thi_4led_7doan();
}

void phim_clear()
{
    for(i = 0;i < 8; i++)
    {
        led7[i] = 0xff;
        if(i >= 4)
           led7[i] = 0x7f;
    }
    dem_ud = 0;
    hien_thi_4led_7doan();
}
void main()
{
    set_up_port_ic_chot();
    set_tris_b(0x3c);
    hien_thi_4led_7doan();
    WHILE(true)
    {
        mp = key_4x4_dw();
        delay_ms(50);
        if (mp != 0xff)
        {
            if (mp < 10)
                dich_led_thuan(); 
            if (mp == 11)
                phim_undo();
            if (mp == 12)
                phim_clear();
            
        }
    }
}
