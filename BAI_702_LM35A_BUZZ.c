//!#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_1_proteus.c>

#define nd_tren 40
unsigned int8 j, solan = 100;
unsigned int16 lm35a;
//int1 ttqn = 0;
void so_sanh_dk_buzzer()
{
    if (lm35a > nd_tren)
    {
        //ttqn = 1;
        buzzer_on();
    }
    else if (lm35a < nd_tren)
    {
        //ttqn = 0;
        buzzer_off();
    }
}
void main()
{
    set_up_port_ic_chot();
    setup_adc(adc_clock_div_32);
    setup_adc_ports(an0 | vss_vdd);
    set_adc_channel(0);
    setup_lcd();
    ttqn = 0;
    while (true)
    {
        lm35a = 0;
        for (j = 0; j < solan; j++)
        {
            lm35a = lm35a + read_adc();
            delay_ms(1);
        }
        lm35a = lm35a / 2.046;
        lm35a = lm35a / solan;
        xuat_4led_7doan_giaima_xoa_so0(lm35a);
        so_sanh_dk_buzzer();
    }
}