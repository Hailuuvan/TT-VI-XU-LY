
//!#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_key4x4_138.c>
#include <tv_pickit2_shift_step_motor.c>

signed int8 mp, so_buoc = 0, so_vong = 0;
unsigned int16 vong;

void doc_so_vong()
{
   if (mp != 0xff&&mp < 10)
   {
      if (mp == 0) vong = 0;
      else if (mp == 1) vong = 1;
      else if (mp == 2) vong = 2;
      else if (mp == 3) vong = 3;
      else if (mp == 4) vong = 4;
      else if (mp == 5) vong = 5;
      else if (mp == 6) vong = 6;
      else if (mp == 7) vong = 7;
      else if (mp == 8) vong = 8;
      else if (mp == 9) vong = 9;
      xuat_4led_7doan_4so (ma7doan[mp], 0xff, ma7doan[so_vong / 10], ma7doan[so_vong % 10]) ;
   }
}

void main()
{
   set_up_port_ic_chot ();
   set_tris_b (0x3c);
   stepmotor_onoff = 1; //de khoi canh bao
   stepmotor_delay = 5;

   while (true)
   {
      
      mp = key_4x4_dw ();
      doc_so_vong () ;
      if (mp != 0xff && mp == 13)
      {
         so_vong = 0;
         do
         {
            step_motor_quay_thuan_fs () ;
            delay_ms (stepmotor_delay) ;
            so_buoc++;
            if (so_buoc == 200)
               so_vong ++;
            xuat_4led_7doan_4so (ma7doan[vong % 10], 0xff, 0xff, ma7doan[so_vong % 10]) ;
         }while (so_vong != vong);
      }
   }
}

