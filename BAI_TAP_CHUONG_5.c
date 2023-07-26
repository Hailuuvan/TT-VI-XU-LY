//!#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_1.c>
signed int8 giay, bdn, chuc, dv;
#int_timer1
void interrupt_timer1()
{
    bdn++;
    set_timer1(3036);
}

void giai_ma_gan_cho_8led_quet()
{
    chuc = giay / 10;
    dv = giay % 10;
    led_7dq[3] = ma7doan[dv];
    led_7dq[4] = ma7doan[chuc];
}
void main()
{
    set_up_port_ic_chot();
    setup_timer_1(t1_internal | t1_div_by_8);
    set_timer1(3036);
    enable_interrupts(global);
    enable_interrupts(int_timer1);

    giay = 0;
    bdn = 0;
    while (true)
    {
        giai_ma_gan_cho_8led_quet();
        if (bdn < 10)
            hien_thi_8led_7doan_quet();
        else
        {
            bdn = bdn - 10;
            giay++;
        }
      //  hien_thi_8led_7doan_quet();
        if (giay > 10)
            {
                if (bdn < 5)
                {
                    led_7dq[3] = 0xff;
                    led_7dq[4] = 0xff;
                }
                else
                {
                    giai_ma_gan_cho_8led_quet();
                    hien_thi_8led_7doan_quet();
                }
                if (giay == 60)
                    giay = 0;
            }
    }
}
