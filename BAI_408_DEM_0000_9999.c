#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
unsigned int16 i;
void giai_ma_hien_thi(unsigned int16 tam)
{
    donvi = ma7doan[tam % 1000 % 100 % 10];
    chuc = ma7doan[tam % 1000 % 100 / 10];
    tram = ma7doan[tam % 1000 / 100];
    ngan = ma7doan[tam / 1000];
    if (ngan == 0)
    {
        ngan = 0xff;
        if (tram == 0xc0) 
        {
            tram = 0xff;
            if (chuc == 0xc0)
                chuc = 0xff;
        }
    }
    xuat_4led_7doan_4so(ngan,tram, chuc, donvi);
}
void main()
{
    set_up_port_ic_chot();
    while (true)
    {
        for (i = 0; i < 10000; i++)
        {
            giai_ma_hien_thi(i);
                   
            delay_ms(200);
        }
    }
}
