#include <tv_pickit2_shift_1_proteus.c>

unsigned int8 i;

void main()
    {
        set_up_port_ic_chot();
        while (true)
        {
            for ( i = 0; i < 60; i++)
            {
                xuat_4led_7doan_2so(ma7doan[i/10], ma7doan[i%10]);
                delay_ms(100);
            }
            for ( i = 60; i > 0; i--)
            {
                xuat_4led_7doan_2so(ma7doan[i/10], ma7doan[i%10]);
                delay_ms(200);
            }
            
        }
        
    }