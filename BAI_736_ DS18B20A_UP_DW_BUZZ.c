
#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_ds18b20.c>
#include <tv_pickit2_shift_key4x4_138.c>
#define nd_tren 60
#define nd_duoi 30

unsigned int8 gt2 = 3,gt1 = 5,gtc,mp;
unsigned int8 ch_gtc  ,dv_gtc ,ch_nd,dv_nd;

void do_nhietdo_ds18b20()
{
   if (touch_present () )
   doc_giatri_ds18b20 ();

   if (ds18al != ds18a_tam)
   {
      ds18a_tam = ds18al;
      ds18a = ds18a >> 4;
      ds18a = ds18a&0x0ff;
      ch_nd = ma7doan[ds18a / 10];
      dv_nd = ma7doan[ds18a % 10];
      xuat_4led_7doan_4so (ch_gtc, dv_gtc, ch_nd, dv_nd);

      //so sanh dk
      if (ds18a > gtc && ds18a < nd_tren)
      {
         xuat_32led_don_1dw (0x0000ffff);
         triac_2_off () ;
      }

      if (ds18a < gtc && ds18a > nd_duoi)
      {
         xuat_32led_don_1dw (0);
         triac_2_on () ;
      }
   }
}

void cai_gia_tri()
{
   gt2 = gt1;
   gt1 = mp;
   gtc = gt2 * 10 + gt1;
}

void phim_up()
{
   if(!input(bt2))
   {
      delay_ms(10);
      if(!input(bt2))
      {
         gtc++;
         while(!input(bt2));
      }
   }
}

void phim_dw()
{
   if(!input(bt1))
   {
      delay_ms(10);
      if(!input(bt1))
      {
         gtc--;
         while(!input(bt1));
      }
   }
}

void gm_hien_thi()
{
   ch_gtc = ma7doan[gtc / 10];
   dv_gtc = ma7doan[gtc % 10];
   xuat_4led_7doan_4so (ch_gtc, dv_gtc, ch_nd, dv_nd);
}

void main()
{
   set_up_port_ic_chot ();
   khoi_tao_ds18b20 ();
   ds18a_tam = 0;
   set_tris_b (0x3c);

   while (true)
   {
      mp = key_4x4_dw ();
      phim_up();
      phim_dw();
      if (mp != 0xff&&mp < 10)
      {
         cai_gia_tri () ;
      }
      do_nhietdo_ds18b20 () ;
      //!      so_sanh_dk();
      gm_hien_thi () ;
   }
}

