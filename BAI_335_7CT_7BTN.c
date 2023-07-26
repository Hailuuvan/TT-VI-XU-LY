
//!#include <tv_pickit2_shift_1.c> 
#include <TV_PICKIT2_SHIFT_1_PROTEUS.C>
signed ttct=1;
#include <TV_PICKIT2_SHIFT_KEY4X4_138.c>
#include <tv_pickit2_shift_32led_don.c> 
signed int8 mp;
void phim_up()
{

   IF (mp == 0 && (ttct < 7) )
   {
      delay_ms (10) ;

      IF (mp == 0)
      {
         ttct++;
         WHILE (mp == 0)
         mp = key_nhan();

        
      }
   }
}

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void phim_dw()
{
   IF (!input (dw)&& (ttct > 1))
   {
      delay_ms(10);

      IF (!input (dw))
      {
         ttct--;
         WHILE ( ! input (dw));
      }
   }
}

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void phim_clr()
{
   IF (!input (clr)&& (ttct > 1))
   {
      ttct=1;
      reset_toan_bo_bien () ;
   }
}

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void main()
{
   set_up_port_ic_chot();
   set_tris_b (0x3c);

   WHILE (true)
   {
    mp = key_nhan();
      xuat_4led_7doan_1so (ma7doan[ttct]) ;
      IF (ttct == 1) sang_tat_32led (10, 0);
      IF (ttct == 2) sang_tat_dan_pst_32led (10, 0);
      IF (ttct == 3) sang_tat_dan_tsp_32led (10, 0);
      IF (ttct == 4) sang_tat_dan_ngoai_vao_32led (10, 0);
      IF (ttct == 5) sang_tat_dan_trong_ra_32led (10, 0);
      IF (ttct == 6) sang_don_pst_32led (10, 0);
      IF (ttct == 7) sang_don_tsp_32led (10, 0);
      phim_dw () ;
      phim_up () ;
      phim_clr () ;
   }
}

