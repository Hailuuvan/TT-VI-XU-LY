#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_32led_don.c>
unsigned int8 t0, t0_tam;
void main()
{
    set_up_port_ic_chot();
    setup_timer_0(t0_ext_l_to_h | t0_div_1 | t0_8_bit);
    set_timer0(1);
    t0_tam = t0 = 0;
    xuat_4led_7doan_giaima_xoa_so0(t0);
    while (true)
    {
        t0 = get_timer0();
        if (t0 != t0_tam)
        {
            t0_tam = t0;
            xuat_4led_7doan_giaima_xoa_so0(t0);
            if (t0 >= 15)
                set_timer0(1);
        }
        if (t0 == 1)
            sang_tat_32led(10, 0);
        if (t0 == 2)
            sang_tat_dan_pst_32led(10, 0);
        if (t0 == 3)
            sang_tat_dan_tsp_32led(10, 0);
        if (t0 == 4)
            sang_tat_dan_ngoai_vao_32led(10, 0);
        if (t0 == 5)
            sang_tat_dan_trong_ra_32led(10, 0);
        if (t0 == 6)
            sang_don_pst_32led(10, 0);
        if (t0 == 7)
            diem_sang_dich_trai_mat_dan_32led(10, 0);
        if (t0 == 8)
            sang_don_tsp_32led(10, 0);
        if (t0 == 9)
            diem_sang_dich_phai_mat_dan_32led(10, 0);
        if (t0 == 10)
            sang_tat_dan_trai_sang_phai_2x16led(40, 0);
        if (t0 == 11)
            sang_tat_dan_phai_sang_trai_2x16led(40, 0);
        if (t0 == 12)
            diem_sang_di_chuyen_pst_32led(40, 0);
        if (t0 == 13)
            diem_sang_di_chuyen_tsp_32led(40, 0);
        if (t0 == 14)
            sang_don_tnt_32led(40, 0);
        if (t0 == 15)
            sang_don_ttr_32led(40, 0);
        if (t0 > 15)
            t0 = 1;
        xuat_4led_7doan_2so(ma7doan[t0 / 10], ma7doan[t0 % 10]);
    }
}