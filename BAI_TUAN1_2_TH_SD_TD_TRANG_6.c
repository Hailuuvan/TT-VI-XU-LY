//!#include <TV_PICKIT2_SHIFT_1.c>
#include <TV_PICKIT2_SHIFT_1_PROTEUS.c>

unsigned INT32 y;
unsigned INT8 i, j;

void Sang_dan_12led_giua_2lan()
{
   FOR (j = 0; j < 2; j++)
   {
      y = 0x00000000;
      FOR (i = 0; i < 4; i++)
      {
         xuat_32led_don_1dw (y);
         delay_ms (300);
         y = ( ( (y >> 5)|0x3E0000)&0x3FFC00);
      }
   }

   
   //Dich phai qua trai
   FOR (j = 0; j < 2; j ++)
   {
      y = 0x00000000;
      FOR (i = 0; i < 4; i++)
      {
         xuat_32led_don_1dw (y);
         delay_ms (300);
         y = ( ( (y << 5)|0x7C00)&0x3FFC00);
      }
   }
}

void Chop_tat_12led_giua_3lan()
{
   y = 0x00000000;
   FOR (i = 0; i < 3; i++)
   {
      xuat_32led_don_1dw (y);
      delay_ms (300);
      xuat_32led_don_1dw (0x3FFC00);
      delay_ms (300);
   }
}

void Tat_dan_12led_giua_2lan()
{
   //Tat dan trai sang phai
   FOR (j = 0; j < 2; j++)
   {
      y = 0xFFFFFFFF;
      FOR (i = 0; i < 4; i++)
      {
         xuat_32led_don_1dw (y);
         delay_ms (300);
         y = ( ( (y >> 5)&0xFFC1FFFF)|0xFFC003FF);
      }
   }

   FOR (j = 0; j < 2; j++)
   {
      y = 0xFFFFFFFF;
      FOR (i = 0; i < 4; i++)
      {
         xuat_32led_don_1dw (y);
         delay_ms (300);
         y = ( ( (y << 5)&0xFFFF83FF)|0xFFC003FF);
      }
   }
}

void main() 
{
   set_up_port_ic_chot ();
   y = 0x00000000;

   WHILE (true)
   {
      Sang_dan_12led_giua_2lan ();
      Chop_tat_12led_giua_3lan ();
      Tat_dan_12led_giua_2lan ();
      Chop_tat_12led_giua_3lan ();
   }
}

