//!#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_1.c>

unsigned int8 g,p;

void main()
    {
        g = 0;
        p = 0;
        set_up_port_ic_chot();
        while (true)
        {
            xuat_4led_7doan_4so(ma7doan[p/10],ma7doan[p%10], ma7doan[g/10],ma7doan[g%10]);
         
            delay_ms(200);
            g++;
            if(g == 60)
            {
                g = 0;
                p++;
            }
                     
        }
        
    }
