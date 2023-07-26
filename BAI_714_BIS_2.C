
 #include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_lcd.c>

unsigned int16 ch_a, dv_a, ch_b, dv_b, ch_kc, dv_kc;
unsigned int16 kqadc, tam;
float k_cach, clk_cach;
unsigned int8 j,i, solan = 100;
unsigned int16 lm35a, lm35b;

void do_k_cach()
{
    set_adc_channel(2);
    kqadc = 0;
    for (j = 0; j < 20; j++)
    {
        kqadc = kqadc + read_adc();
        //delay_ms(10);
        hien_thi_8led_7doan_quet();
    }

    kqadc = kqadc / 20;
    if (kqadc <= 80)
        k_cach = 80;

    else if ((kqadc > 80) && (kqadc < 87))
    {
        clk_cach = kqadc - 80;
        k_cach = 80 - clk_cach / 0.77;
    }

    else if (kqadc == 87)
        k_cach = 70;

    else if ((kqadc > 87) && (kqadc < 106))
    {
        clk_cach = kqadc - 87;
        k_cach = 70 - clk_cach / 2.11;
    }

    else if (kqadc == 106)
        k_cach = 60;

    else if ((kqadc > 106) && (kqadc < 124))
    {
        clk_cach = kqadc - 106;
        k_cach = 60 - clk_cach / 2;
    }

    else if (kqadc == 124)
        k_cach = 50;

    else if ((kqadc > 124) && (kqadc < 150))
    {
        clk_cach = kqadc - 124;
        k_cach = 50 - clk_cach / 2.88;
    }

    else if (kqadc == 150)
        k_cach = 40;

    else if ((kqadc > 150) && (kqadc < 196))
    {
        clk_cach = kqadc - 150;
        k_cach = 40 - clk_cach / 5.11;
    }

    else if (kqadc == 196)
        k_cach = 30;

    else if ((kqadc > 196) && (kqadc < 276))
    {
        clk_cach = kqadc - 196;
        k_cach = 30 - clk_cach / 8.88;
    }

    else if (kqadc == 276)
        k_cach = 20;

    else if ((kqadc > 276) && (kqadc < 490))
    {
        clk_cach = kqadc - 276;
        k_cach = 20 - clk_cach / 23.77;
    }

    else if (kqadc == 490)
        k_cach = 10;
    hien_thi_8led_7doan_quet();
}

void doc_nd_lm35a()
{
    set_adc_channel(0);
    lm35a = 0;
    for (j = 0; j < solan; j++)
    {
        lm35a = lm35a + read_adc();
        //delay_us(100);
        hien_thi_8led_7doan_quet();
    }
    lm35a = lm35a / 2.046;
    lm35a = lm35a / solan;
}
void doc_nd_lm35b()
{
    set_adc_channel(1);
    lm35b = 0;
    for (j = 0; j < solan; j++)
    {
        lm35b = lm35b + read_adc();
        //delay_us(100);
        hien_thi_8led_7doan_quet();
    }
    lm35b = lm35b / 2.046;
    lm35b = lm35b / solan;
}

void giai_ma_8led_quet()
{
    ch_b = ma7doan[lm35b / 10];
    dv_b = ma7doan[lm35b % 10];
    ch_a = ma7doan[lm35a / 10];
    dv_a = ma7doan[lm35a % 10];
    ch_kc = ma7doan[tam / 10];
    dv_kc = ma7doan[tam % 10];

    led_7dq[0] = dv_b;
    led_7dq[1] = ch_b;
    led_7dq[2] = 0xbf;
    led_7dq[3] = dv_a;
    led_7dq[4] = ch_a;
    led_7dq[5] = 0xbf;
    led_7dq[6] = dv_kc;
    led_7dq[7] = ch_kc;
}

void gm_4led_7doan()
{
    ch_b = ma7doan[lm35b / 10];
    dv_b = ma7doan[lm35b % 10];
    ch_kc = ma7doan[tam / 10];
    dv_kc = ma7doan[tam % 10];
    xuat_4led_7doan_4so(ch_kc, dv_kc & 0x7f, ch_b, dv_b);
}

void lcd_hienthi_so_z_toado_xy(signed int8 lcd_so, x1, y1)
{
    lcd_goto_xy(x1, y1);
    for (i = 0; i < 6; i++)
    {
        if (i == 3)
            lcd_goto_xy(x1 + 1, y1);

        lcd_data(lcd_so_x[lcd_so][i]);
        hien_thi_8led_7doan_quet();
    }
}

void hienthi_lcd()
{
   
   ch_a = lm35a / 10 ;
   dv_a = lm35a % 10;

   //xoa so 0 vn
   if (ch_a == 0)
      ch_a = 10;

   lcd_goto_xy (0, 0) ;
   lcd_data ("Kcach:") ;
   lcd_goto_xy (1, 0) ;
   lcd_data(tam/10 + 0x30);
   lcd_data(tam%10 + 0x30);
   lcd_goto_xy (0, 7) ;
   lcd_data ("LM35A:") ;
   lcd_goto_xy (1, 7) ;
   lcd_data (ch_a + 0x30);
   lcd_data (dv_a + 0x30);
   
   ch_b = lm35b / 10 ;
   dv_b = lm35b % 10;

   //xoa so 0 vn
   if (ch_b == 0)
      ch_b = 10;

   lcd_goto_xy (0, 14) ;
   lcd_data ("LM35B:") ;
   lcd_goto_xy (1, 15) ;
   lcd_data (ch_b + 0x30);
   lcd_data (dv_b + 0x30);
   
   lcd_hienthi_so_z_toado_xy(tam%10, 2,3);
   lcd_hienthi_so_z_toado_xy(tam/10, 2,0);
   lcd_hienthi_so_z_toado_xy(lm35a/10, 2,7);
   lcd_hienthi_so_z_toado_xy(lm35a%10, 2,10);
   lcd_hienthi_so_z_toado_xy(lm35b/10, 2,14);
   lcd_hienthi_so_z_toado_xy(lm35b%10, 2,17);
}

void main()
{
    set_up_port_ic_chot();
    setup_adc(adc_clock_div_32);
    setup_adc_ports(an0_to_an2 | vss_vdd);
    setup_lcd();
    lcd_command(0x40);
    for (i = 0; i < 64; i++)
    {
        lcd_data(lcd_ma_8doan[i]);
        hien_thi_8led_7doan_quet();
    }
    while (true)
    {

        tam = k_cach;
        doc_nd_lm35a();
        doc_nd_lm35b();
        do_k_cach();
        giai_ma_8led_quet();
        hien_thi_8led_7doan_quet();
        gm_4led_7doan();
        hienthi_lcd();
    }
}
