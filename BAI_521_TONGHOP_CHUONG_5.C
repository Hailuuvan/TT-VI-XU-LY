
 #include <tv_pickit2_shift_1_proteus.c>
// #include <tv_pickit2_shift_1.c>
signed INT8 giay, bdn, t0;
signed INT8 chuc7, donvi6, chuc1, donvi0;
unsigned INT1 button0, button1, button2, button3;

#int_timer1
void interrupt_timer1()
{
   bdn++;
   set_timer1(3036);
}

void giai_ma_hien_thi()
{
   donvi0 = ma7doan[giay % 10];
   chuc1 = ma7doan[giay / 10 % 10];

   IF(chuc1 == 0xc0)
   chuc1 = 0xff;

   // counter
   donvi6 = ma7doan[t0 % 10];
   chuc7 = ma7doan[t0 / 10 % 10];

   IF(chuc7 == 0xc0)
   chuc7 = 0xff;

   xuat_4led_7doan_4so(chuc7, donvi6, chuc1, donvi0);

   donvi0 = giay % 10;
   chuc1 = giay / 10;

   donvi6 = t0 % 10;
   chuc7 = t0 / 10;


   if(chuc1 == 0xc0)
      chuc1 =0xff;
   if(chuc7 == 0xc0)
      chuc7 =0xff;

   led_7dq[6] = ma7doan[donvi6];
   led_7dq[7] = ma7doan[chuc7];
   led_7dq[0] = ma7doan[donvi0];
   led_7dq[1] = ma7doan[chuc1];
   hien_thi_8led_7doan_quet();
}

void phim_dao_dem() // phím đảo chiều đêm
{
   IF(input(bt3) == 0)
   delay_ms(50);

   IF(input(bt3) == 0)
   {
      button3 = ~button3;
      // setup_timer_0 (t0_ext_l_to_h|t0_div_1|t0_8_bit);
      set_timer0(15 - get_timer0());
      WHILE(!input(inv));
   }
}

void phim_dao_time() // phím đảo chiều thoi gian
{
   IF(input(bt1) == 0)
   delay_ms(50);
   {
      IF(input(bt1) == 0)
      {
         button1 = ~button1;
         // setup_timer_0 (t0_ext_l_to_h|t0_div_1|t0_8_bit);
         // set_timer0 (15 - get_timer0 ());
         WHILE(!input(bt1));
      }
   }
}

void phim_start_pause() // phím đảo chiều thoi gian
{
   IF(input(bt0) == 0)
   {
      delay_ms(50);

      IF(input(bt0) == 0)
      {
         button0 =~ button0;

         WHILE(!input(bt0));
      }
   }
}

void phim_start_pause_dem() // phím đảo chiều thoi gian
{
   IF(input(bt2) == 0)
   {
      delay_ms(50);

      IF(input(bt2) == 0)
      {
         button2 = ~button2;

         WHILE(!input(bt2));
      }
   }
}

void main()
{
   set_up_port_ic_chot();
   setup_timer_1(t1_internal | t1_div_by_8);
   set_timer1(3036);
   enable_interrupts(global);
   enable_interrupts(int_timer1);
   set_timer0(5);

   giay = 7;
   bdn = 0;
   button0 = 0;
   button1 = 0;
   button2 = 0;
   button3 = 0;
   WHILE(true)
   {
      // 
      phim_start_pause();
      phim_dao_time();
      // 
      if(button0 == 0)
         setup_timer_1(T1_DISABLED);
      else 
         setup_timer_1(t1_internal | t1_div_by_8);

      if(bdn < 10)
      
      HIEN_THI_8LED_7DOAN_QUET();
      else
      {
         bdn = bdn - 10;
         if(button1 == 0)
         {
            giay++;

            IF(giay == 13)
            giay = 7;
         }
         else
         {
            giay --;
            if(giay == 6)
               giay = 12;
         }
      }
      phim_dao_dem ();
      phim_start_pause_dem();

      if(button2 == 0)
         setup_timer_0(T0_OFF);
      else 
         setup_timer_0 (t0_ext_l_to_h|t0_div_1|t0_8_bit);
      if(button3 == 0)
      {
         t0 = get_timer0 ();

         IF (t0 == 16)
         set_timer0 (5);
      }
      else
      {
         t0 = 15 - get_timer0 () ;

         IF (t0 == 4)
         set_timer0 (0);
      }
      giai_ma_hien_thi();

   }
}


