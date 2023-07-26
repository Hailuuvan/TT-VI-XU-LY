
//! #include <tv_pickit2_shift_1.c>
#include <TV_PICKIT2_SHIFT_1_PROTEUS.C>

unsigned INT32 y;
unsigned INT16 sd,td;
unsigned INT8 i,j;

void sang_tat_5lan()
{
   //!y = 0;
   // ! FOR (i = 0; i < 5; i++)
   {
      //!            xuat_32led_don_1dw(y);
      //!            delay_ms(1000);
      //!            y = ~y;

      // !
   }

   FOR (i = 0; i < 5; i++)
   {
      xuat_32led_don_4byte (0, 0, 0, 0) ;
      delay_ms (1000) ;
      xuat_32led_don_4byte (0xff, 0xff, 0xff, 0xff) ;
      delay_ms (1000) ;
   }
}

void sang_tat_dan_pst_32led_2lan()
{
   FOR(j=0;j<2;j++)
   {
      FOR (i = 0; i < 32; i++)
      {
         xuat_32led_don_1dw (y) ;
         delay_ms (30);
         y = (y<<1) + 1;
      }

      FOR (i = 0; i < 32; i++)
      {
         xuat_32led_don_1dw (y) ;
         delay_ms (30);
         y = (y<<1);
      }
   }
}

void sang_tat_dan_tsp_32led_2lan()
{
   FOR (j = 0; j < 2; j++)
   {
      FOR (i = 0; i < 32; i++)
      {
         xuat_32led_don_1dw (y) ;
         delay_ms (30);
         y = (y>>1) + 0x80000000;
      }

      FOR (i = 0; i < 32; i++)
      {
         xuat_32led_don_1dw (y) ;
         delay_ms (30);
         y = (y>>1);
      }
   }
}

void sang_tat_dan_ngoai_vao_32led_2lan()
{
   sd = 0;
   td = 0;
   FOR (j = 0;j < 2; j++)
   {
      FOR (i = 0;i < 16;i++)
      {
         xuat_32led_don_2word (td, sd); // (ben trai, ben phai)
         delay_ms (300) ;
         
         sd = (sd<<1) + 1;
         td = (td>>1) + 0x8000;
      }

      FOR (i = 0; i < 16; i++)
      {
         xuat_32led_don_2word (td, sd); // (ben trai, ben phai)
         delay_ms (300) ;
         sd = (sd>>1);
         td = (td<<1);
      }
   }
}

void sang_tat_dan_trong_ra_32led_2lan()
{
   sd = 0;
   td = 0;
   FOR (j = 0;j < 2; j++)
   {
      FOR (i = 0;i < 16;i++)
      {
         xuat_32led_don_2word (sd, td); // (ben trai, ben phai)
         delay_ms (300) ;
         
         sd = (sd<<1) + 1;
         td = (td>>1) + 0x8000;
      }

      FOR (i = 0; i < 16; i++)
      {
         xuat_32led_don_2word (sd, td); // (ben trai, ben phai)
         delay_ms (300) ;
         sd = (sd>>1);
         td = (td<<1);
      }
   }
}

void main()
{
   set_up_port_ic_chot();
   y = 0x00000000;

   WHILE (true)
   {
      sang_tat_5lan () ;
      sang_tat_dan_pst_32led_2lan () ;
      sang_tat_5lan () ;
      sang_tat_dan_tsp_32led_2lan () ;
      sang_tat_5lan () ;
      sang_tat_dan_ngoai_vao_32led_2lan () ;
      sang_tat_5lan () ;
      sang_tat_dan_trong_ra_32led_2lan () ;
   }
}

