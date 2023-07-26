
 #include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
unsigned INT8 t0,chuc,donvi;
unsigned INT1 dao;

void phim_dao()
{
    if (!input(inv))
    {
        delay_ms(20);
        if (!input(inv))
        {
            dao =~dao;

            while (!input(inv));
                
        }
    }
}
void phim_clear()
{
    if(input(on) == 0)
        delay_ms(20);
        if(input(on) == 0)
        {
            set_timer0(0);
        }
        while(!input(on));
}
void giai_ma_gan_cho_8led_quet()
{
    //xoa so 0 vo nghia
    donvi = t0 %10;
    chuc = t0 / 10;
    if(chuc == 0)
    {
        led_7dq[1] = 0xff;
        led_7dq[0] = ma7doan [donvi];
    }
    else
    {
        led_7dq[0] = ma7doan [donvi];
        led_7dq[1] = ma7doan [chuc];
    }

}
void main()
{
    set_up_port_ic_chot();
    // setup_timer_0 (t0_ext_l_to_h|t0_div_1|t0_8_bit);
    set_timer0(0);

    xuat_4led_7doan_giaima_xoa_so0(t0);
    setup_timer_0(t0_off);
    dao  = 0;
    WHILE(true)
    {
        t0 = get_timer0();
        xuat_4led_7doan_giaima_xoa_so0(t0);
        

        if (t0 >= 100)
            set_timer0(1);
        phim_dao();
        phim_clear();
        if(dao == 0)
        {
       
            setup_timer_0(t0_ext_l_to_h | t0_div_1 | t0_8_bit);
            giai_ma_gan_cho_8led_quet();
            hien_thi_8led_7doan_quet();
        }
        if(dao == 1)
        {
            setup_timer_0(t0_off);
        }
    }
}
