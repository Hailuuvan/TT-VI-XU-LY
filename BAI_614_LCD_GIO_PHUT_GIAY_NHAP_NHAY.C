//! #include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_lcd.c>

signed int8 gio, phut, giay, bdn;

unsigned int8 gia_tri_mod, i;
unsigned int8 DVgio, CHgio, DVphut, CHphut, DVgiay, CHgiay;

#int_timer1
void interrupt_timer1()
{
    bdn++;
    set_timer1(3036);
}

void phim_mod()
{
    if (input(bt3) == 0)
    {
        if (!input(bt3))
        {
            gia_tri_mod++;
            if (gia_tri_mod >= 4)
                gia_tri_mod = 0;
            while (!input(bt3))
                ;
            lcd_goto_xy(2, 10);
            lcd_data(gia_tri_mod + 0x30);
        }
    }
}

void phim_up()
{
    if (!input(bt0))
    {
        if (!input(bt0))
        {
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

            while (!input(bt0));
        }
    }
}

void phim_dw()
{
    if (!input(bt1))
    {
        if (!input(bt1))
        {
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

            while (!input(bt1));
        }
    }
}

void lcd_giaima_dongho()
{
    DVgio = gio % 10 + 0x30;
    CHgio = gio / 10 + 0x30;
    DVphut = phut % 10 + 0x30;
    CHphut = phut / 10 + 0x30;
    DVgiay = giay % 10 + 0x30;
    CHgiay = giay / 10 + 0x30;
}

void lcd_hienthi_dongho()
{
    lcd_goto_xy(0, 12);
    lcd_data(CHgio);
    lcd_data(DVgio);
    lcd_data(' ');
    lcd_data(CHphut);
    lcd_data(DVphut);
    lcd_data(' ');
    lcd_data(CHgiay);
    lcd_data(DVgiay);
}

void tat_2LED_chinh_LCD()
{
    if (gia_tri_mod == 1)
    {
        CHgio = 0x20;
        DVgio = 0x20;
    }
    else if (gia_tri_mod == 2)
    {
        CHphut = 0x20;
        DVphut = 0x20;
    }
    else if (gia_tri_mod == 3)
    {
        CHgiay = 0x20;
        DVgiay = 0x20;
    }
}

// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void main()
{
    set_up_port_ic_chot();
    setup_timer_1(t1_internal | t1_div_by_8);
    set_timer1(3036);
    enable_interrupts(global);
    enable_interrupts(int_timer1);
    setup_lcd();
    lcd_goto_xy(0, 0);
    lcd_data("dong ho:");
    giay = 0x00;
    phut = 0;
    gio = 0;
    gia_tri_mod = 0;

    // hien thi gia tri mod
    lcd_goto_xy(2, 10);
    lcd_data(gia_tri_mod + 0x30);

    while (true)
    {
        if (bdn < 10)
        {
            if (gia_tri_mod != 0)
            {
                if ((bdn < 5)) //&& ( ! input (bt0))&& ( ! input (bt1)))
                    tat_2LED_chinh_LCD();

                else if (bdn < 10)
                    lcd_giaima_dongho();
            }
            else
                lcd_giaima_dongho();

            //!            lcd_giaima_dongho();
            lcd_hienthi_dongho();
            phim_mod();
            phim_up();
            phim_dw();
        }

        else
        {
            bdn = bdn - 10;
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
        }
        delay_ms(200);
    }
}
