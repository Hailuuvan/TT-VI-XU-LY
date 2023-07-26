#include <tv_pickit2_shift_1.c>
//! #include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_lcd.c>

unsigned int8 t0, tr, ch, dv, gt_cai;
void hienthi_lcd()
{
    lcd_goto_xy(1, 0);
    lcd_data("dem san pham");

    tr = t0 / 100 + 0x30;
    ch = t0 / 10 % 10 + 0x30;
    dv = t0 % 10 + 0x30;
    if (tr == 0x30)
    {
        tr = 0x20;

        if (ch == 0x30)
            ch = 0x20;
    }
    lcd_goto_xy(1, 13);
    lcd_data(tr);
    lcd_data(ch);
    lcd_data(dv);

    lcd_goto_xy(0, 0);
    lcd_data("gia tri cai: ");
    lcd_data(gt_cai / 10 + 0x30);
    lcd_data(gt_cai % 10 + 0x30);
}
void main()
{
    set_up_port_ic_chot();
    setup_lcd();
    setup_timer_0(t0_ext_l_to_h | t0_div_1 | t0_8_bit);
    set_timer0(0);
    gt_cai = 0;
    while (true)
    {
        t0 = get_timer0();
        xuat_4led_7doan_3so(ma7doan[t0 / 100], ma7doan[t0 / 10 % 10], ma7doan[t0 % 10]);

        hienthi_lcd();

        if (!input(up))
        {
            delay_ms(20);
            if (!input(up))

            {
                gt_cai++;
                while (!input(up));
                   
            }
        }
        if (!input(dw))
            delay_ms(20);
        {
            if (!input(dw))

            {
                gt_cai--;
                while (!input(dw));
                    
            }
        }
        if (!input(clr))
            delay_ms(20);
        {
            if (!input(clr))

            {
                set_timer0(1);
                gt_cai = 1;
                while (!input(clr));
                    
            }
        }
        if (t0 > gt_cai)
            set_timer0(1);
    }
}
