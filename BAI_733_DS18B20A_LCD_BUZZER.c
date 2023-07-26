#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_ds18b20.c>
int1 ttqn;
#define gh_nda_tren 33
#define gh_nda_duoi 31
void main()
{
    set_up_port_ic_chot();
    khoi_tao_ds18b20();
    ds18a_tam = 0;
    xuat_4led_7doan_giaima_xoa_so0(0);
    xuat_32led_don_1dw(0);
    ttqn = 0;
    while (true)
    {
        if (touch_present())
        {
            doc_giatri_ds18b20();
        }
        if (ds18al != ds18a_tam)
        {
            ds18a_tam = ds18al;
            ds18a = ds18a >> 4;
            ds18a = ds18a & 0x0ff;
            xuat_4led_7doan_giaima_xoa_so0(ds18a);
            if ((ds18a > gh_nda_tren) && (ttqn == 0))
            {
                ttqn = 1;
                xuat_32led_don_1dw(0x0000ffff);
            }
            else if ((ds18a < gh_nda_duoi) && (ttqn == 1))
            {
                ttqn = 0;
                xuat_32led_don_1dw(0xffff0000);
            }
        }
    }
}