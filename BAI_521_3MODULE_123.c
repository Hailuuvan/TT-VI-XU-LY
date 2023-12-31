#include <tv_pickit2_shift_1_PROTEUS.c>
signed int8 gio, phut, giay, bdn, gia_tri_mod, dem_tg_exit = 0;
unsigned int8 t0, t0_tam;
void delay_quet_8led(unsigned int8 dl);
#include <tv_pickit2_shift_32led_don.c>
#int_timer1
void interrupt_timer1()
{
    bdn++;
    set_timer1(3036);
}
void giai_ma_gan_cho_8led_quet()
{
    led_7dq[0] = ma7doan[giay % 10];
    led_7dq[1] = ma7doan[giay / 10];
    led_7dq[3] = ma7doan[phut % 10];
    led_7dq[4] = ma7doan[phut / 10];
    led_7dq[6] = ma7doan[gio % 10];
    led_7dq[7] = ma7doan[gio / 10];
}
void tat_2led_chinh() 
{
    if (gia_tri_mod == 1)
    {
        led_7dq[7] = 0xff;
        led_7dq[6] = 0xff;
    }
    else if (gia_tri_mod == 2)
    {
        led_7dq[4] = 0xff;
        led_7dq[3] = 0xff;
    }
    else if (gia_tri_mod == 3)
    {
        led_7dq[1] = 0xff;
        led_7dq[0] = 0xff;
    }
}
void phim_mod()
{
    if (phim_bt1(50))
    {
        gia_tri_mod++;
        if (gia_tri_mod >= 4)
            gia_tri_mod = 0;
        dem_tg_exit = 0;
    }
}
void phim_up()
{
    if (phim_bt0(20))
    {
        dem_tg_exit = 0;
        switch (gia_tri_mod)
        {
        case 1:
            if (gio == 23)
                gio = 0;
            else
                gio++;
            break;
        case 2:
            if (phut == 59)
                phut = 0;
            else
                phut++;
            break;
        case 3:
            if (giay == 59)
                giay = 0;
            else
                giay++;
            break;
        default:
            break;
        }
        giai_ma_gan_cho_8led_quet();
    }
}
void phim_dw()
{
    if (phim_bt2(20))
    {
        dem_tg_exit = 0;
        switch (gia_tri_mod)
        {
        case 1:
            if (gio == 0)
                gio = 23;
            else
                gio--;
            break;
        case 2:
            if (phut == 0)
                phut = 59;
            else
                phut--;
            break;
        case 3:
            if (giay == 0)
                giay = 59;
            else
                giay--;
            break;
        default:
            break;
        }
        giai_ma_gan_cho_8led_quet();
    }
}
void main()
{
    set_up_port_ic_chot();
    setup_timer_1(t1_internal | t1_div_by_8);
    set_timer1(3036);
    enable_interrupts(global);
    enable_interrupts(int_timer1);
    
    bdn = 0;
    giay = 0x00;
    phut = 0;
    gio = 0;
    gia_tri_mod = 0;
    setup_timer_0(t0_ext_l_to_h | t0_div_1 | t0_8_bit);
    set_timer0(0);
    t0_tam = t0 = 0;
    xuat_4led_7doan_giaima_xoa_so0(t0);
    giai_ma_gan_cho_8led_quet();
    while (true)
    {
        if (bdn < 10)
        {
            if (gia_tri_mod != 0)
            {
                if ((bdn == 0) && (input(bt0)) && (input(bt2)))
                    tat_2led_chinh();
                else if (bdn == 5)
                    giai_ma_gan_cho_8led_quet();
            }
            hien_thi_8led_7doan_quet_all();
            phim_mod();
            phim_up();
            phim_dw();
            t0 = get_timer0();
            if (t0 != t0_tam)
            {
                t0_tam = t0;
                xuat_4led_7doan_giaima_xoa_so0(t0);
                if (t0 >= 101)
                    set_timer0(1);
            }
            if (ttct_td == 1)
                sang_tat_32led(2, 1);
            if (ttct_td == 2)
                sang_tat_dan_pst_32led(5, 1);
            if (ttct_td == 3)
                sang_tat_dan_tsp_32led(5, 1);
            if (ttct_td == 4)
                sang_tat_dan_ngoai_vao_32led(5, 1);
            if (ttct_td == 5)
                sang_tat_dan_trong_ra_32led(5, 1);
            if (ttct_td == 6)
                sang_don_pst_32led(5, 1);
            if (ttct_td == 7)
                diem_sang_dich_trai_mat_dan_32led(5, 1);
            if (ttct_td == 8)
                sang_don_tsp_32led(5, 1);
            if (ttct_td == 9)
                diem_sang_dich_phai_mat_dan_32led(5, 1);
            if (ttct_td == 10)
                sang_tat_dan_trai_sang_phai_2x16led(5, 1);
            if (ttct_td == 11)
                sang_tat_dan_phai_sang_trai_2x16led(5, 1);
            if (ttct_td == 12)
                diem_sang_di_chuyen_pst_32led(5, 1);
            if (ttct_td == 13)
                diem_sang_di_chuyen_tsp_32led(5, 1);
            if (ttct_td == 14)
                sang_don_tnt_32led(5, 1);
            if (ttct_td == 15)
                sang_don_ttr_32led(5, 1);
            if (ttct_td > 15)
                ttct_td = 1;
        }
        else
        {
            bdn = bdn - 10;
            dem_tg_exit++;
            if (dem_tg_exit == 20)
                gia_tri_mod = 0;
            giay++;
            if (giay == 60)
            {
                giay = 0;
                phut++;
                if (phut == 60)
                {
                    phut = 0;
                    gio++;
                    if (gio == 24)
                        gio = 0;
                }
            }
            giai_ma_gan_cho_8led_quet();
        }
    }
}