
 #include <TV_PICKIT2_SHIFT_1_PROTEUS.C>
// // #include <tv_pickit2_shift_1.c>

signed int8 t0,bdn;

unsigned int8 donvi, chuc, giay;
unsigned int1 tt_ss, tt_dc, st_pau;

#int_timer1
void interrupt_timer1()
{
   bdn++;
   set_timer1 (3036);
}

void giai_ma_8led_quet()
{
   if (tt_dc == 0)
   {
      led_7dq[6] = ma7doan[giay % 10];
      led_7dq[7] = ma7doan[giay / 10];
      
      led_7dq[0] = ma7doan[t0 % 10];
      led_7dq[1] = ma7doan[t0 / 10];
   }

   else
   {

      led_7dq[0] = ma7doan[giay % 10];
      led_7dq[1] = ma7doan[giay / 10];
      
      led_7dq[6] = ma7doan[t0 % 10];
      led_7dq[7] = ma7doan[t0 / 10];
   }
}

void giai_ma_hien_thi_4_led_7doan()
{
   donvi = ma7doan[giay % 10];
   chuc = ma7doan[giay / 10 % 10];

   if (chuc == 0xc0)
      chuc = 0xff;

   if (tt_dc == 0)
      xuat_4led_7doan_4so (chuc, donvi&0x7f, ma7doan[t0 / 10 % 10], ma7doan[t0 % 10]) ;

   else
      xuat_4led_7doan_4so (ma7doan[t0 / 10 % 10], ma7doan[t0 % 10]&0x7f, chuc, donvi);
}

void phim_start_pause() 
{
   if (!input (bt1))
   {
      delay_ms (20);

      if (!input (bt1))
      {
         st_pau = ~ st_pau;
         
         while (!input (bt1));
      }
   }
}

void dao_chieu_ht()  
{
   if (!input (bt0))
   {
      delay_ms (20);

      if (!input (bt0))
      {
         tt_dc = ~tt_dc;
         //xuat_4led_7doan_4so (0x92, 0x8c, chuc, donvi&0x7f);
         
         while (!input (bt0));
      }
   }
}

void phim_dao()   
{
//!   delay_ms (50);

   if (input (inv) == 0)
   {
      tt_ss = ~tt_ss;
      //setup_timer_0 (t0_ext_l_to_h|t0_div_1|t0_8_bit);
      set_timer0 (99 - get_timer0 ());
      while (!input (inv));
   }
}

void main()
{
   set_up_port_ic_chot ();
   setup_timer_1 (t1_internal|t1_div_by_8);
   set_timer1 (3036);
   enable_interrupts (global);
   enable_interrupts (int_timer1);
   giay = 0;
   bdn = 0;
   tt_ss = 1;
   tt_dc = 0;
   st_pau = 1;
   
   set_timer0 (0);
   setup_timer_0 (t0_off);
   // xuat_4led_7doan_4so (0);

   while (true)
   {
      phim_start_pause ();
      phim_dao ();
      dao_chieu_ht ();
      giai_ma_8led_quet ();
      hien_thi_8led_7doan_quet ();
      if (st_pau == 0)
      {
         setup_timer_0 (t0_ext_l_to_h|t0_div_1|t0_8_bit);
         giai_ma_8led_quet ();
         if (bdn < 10)
         {
            hien_thi_8led_7doan_quet ();
            giai_ma_hien_thi_4_led_7doan ();
         }
         else
         {
            bdn = bdn - 10;
            giay++;

            if (giay == 60)
               giay = 0;
         }

         
         if (tt_ss == 1)
         {
            
            t0 = get_timer0 ();

            if (t0 >= 100)
               set_timer0 (1) ;
         }

         if (tt_ss == 0)
         {
            t0 = 99 - get_timer0 ();

            if (t0 == 0)
               set_timer0 (0) ;  
         }

         phim_dao ();
         dao_chieu_ht ();
      }
      else
         setup_timer_0 (t0_off);
   } 
}


