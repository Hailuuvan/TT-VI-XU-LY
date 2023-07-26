//!#include <TV_PICKIT2_SHIFT_1_PROTEUS.C>
#include <tv_pickit2_shift_1.c>
signed int8 t0;
unsigned int8 donvi, chuc;
unsigned int1 tt_ss, tt_dc, st_pau;
void giai_ma_hien_thi(unsigned int16 tam)
{
    //giai ma led 7 doan
    donvi = ma7doan[tam % 10];
    chuc = ma7doan[tam / 10 % 10];
    // xoa so 0 vo nghia
    if (chuc == 0xc0)
        chuc = 0xff;
    if (tt_dc == 0)  // tt dao chieu
        xuat_4led_7doan_4so(chuc, donvi & 0x7f, 0x92, 0x8c);
    else
        xuat_4led_7doan_4so(0x92, 0x8c & 0x7f, chuc, donvi);
        // dao ben hien thi
}
// xu ly nut nhan star pause (bt0)
void phim_start_pause() 
{
    if (!input(bt1))
    {
        delay_ms(20);
        if (!input(bt1))
        {
            st_pau =~ st_pau;
            
            while (!input(bt1));
                
        }
    }
}
// xu ly nut nhan dao ben hien thi
void dao_chieu_sp()  
{
    if (!input(bt0))
    {
        delay_ms(20);
        if (!input(bt0))
        {
            tt_dc = ~tt_dc;

            //xuat_4led_7doan_4so( 0x92, 0x8c, chuc, donvi & 0x7f);
            
            while (!input(bt0));

        }
    }
}
// xu ly nut nhan dao chieu dem
void phim_s_p()   
{
        delay_ms(50);
        if (input(inv) == 0)
        {
            tt_ss = ~tt_ss;
            //setup_timer_0(t0_ext_l_to_h | t0_div_1 | t0_8_bit);
            set_timer0(99 - get_timer0());
            while (!input(inv));
                
        }
}
void main()
{
    set_up_port_ic_chot();
    // setup_timer_0(t0_ext_l_to_h | t0_div_1 | t0_8_bit);
    tt_ss = 1;
    tt_dc = 0;
    st_pau = 1;
    
    set_timer0(0);
    setup_timer_0(t0_off);
    // xuat_4led_7doan_4so(0);
    while (true)
    {
        phim_start_pause();
        phim_s_p();
        dao_chieu_sp();
        if (st_pau == 0) // bắt đầu đêm
        {
            setup_timer_0(t0_ext_l_to_h | t0_div_1 | t0_8_bit);
            
            if (tt_ss == 1)
            {
                
                t0 = get_timer0();
                giai_ma_hien_thi(t0);
                
                if (t0 >= 100)
                    set_timer0(1);
            }
            if (tt_ss == 0)
            {
                t0 =99 - get_timer0();
                if(t0 == 0)
                    set_timer0(0);
                giai_ma_hien_thi(t0);
            }
        }
        else
        {            
            do
            setup_timer_0(t0_off);
            while(st_pau == 0);
        }
    }
}
