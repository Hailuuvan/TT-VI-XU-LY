//! #include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_1_proteus.c>
unsigned int8 j, solan = 100;
unsigned int16 lm35a, lm35b, ch_a,  dv_a,  ch_b,  dv_b;
int doc_nd_lm35a()
{
    set_adc_channel(0);
    lm35a = 0;
    for (j = 0; j < solan; j++)
    {
        lm35a = lm35a + read_adc();
        delay_us(100);
    }
    lm35a = lm35a / 2.046;
    lm35a = lm35a / solan;
    return lm35a;
}
int doc_nd_lm35b()
{
    set_adc_channel(1);
    lm35b = 0;
    for (j = 0; j < solan; j++)
    {
        lm35b = lm35b + read_adc();
        delay_us(100);
    }
    lm35b = lm35b / 2.046;
    lm35b = lm35b / solan;
    return lm35b;
}

void giai_ma_4led_7doan() 
{
    ch_a = ma7doan[lm35a/10];
    dv_a = ma7doan[lm35a%10];

    if(ch_a == 0xc0)
        ch_a = 0xff;
    ch_b = ma7doan[lm35b/10];
    dv_b = ma7doan[lm35b%10];

    if(ch_b == 0xc0)
        ch_b = 0xff;
}

void main()
{
    set_up_port_ic_chot();
    setup_adc(adc_clock_div_32);
    setup_adc_ports(an0_to_an1 | vss_vdd);
    while (true)
    {
        doc_nd_lm35a();
        doc_nd_lm35b();
        giai_ma_4led_7doan() ;
        xuat_4led_7doan_4so( ch_a, dv_a & 0x7f,ch_b, dv_b);
    }
}