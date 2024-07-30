#include "screen.h"
#include "../ports.h"
#include "../../kernel/utility.h"

int get_cursor_offset();
void set_cursor_offset(int offset);
int print_char(char c, int col, int row, char color);
int get_offset(int col, int row);
int get_offset_row(int offset);
int get_offset_col(int offset);


////////////////////////
///      PUBLIC      ///
////////////////////////

void VGA_clear_screen()
{
   int size = VGA_MAX_ROW * VGA_MAX_COL;
   char* screen = (char*)VGA_VIDEO_MEM;
   
   for (int i = 0; i < size; ++i)
   {
      screen[i*2] = ' ';
      screen[i*2+1] = 0b00000000;
   }
}

void VGA_print_color_at(char* msg, char color, int col, int row)
{
   int offset;
   if (col >= 0 && row >= 0)
      offset = get_offset(col, row);
   else
   {
      offset = get_cursor_offset();
      col = get_offset_col(offset);
      row = get_offset_row(offset);
   }

   int i = 0;
   while (msg[i] != 0)
   {
      offset = print_char(msg[i++], col, row, color);
      col = get_offset_col(offset);
      row = get_offset_row(offset);
   }
}

void VGA_print_at(char* msg, int col, int row)
{
   VGA_print_color_at(msg, VGA_create_bg_fg_color(VGA_BLACK, VGA_WHITE), col, row);
}

void VGA_print(char* msg)
{
   VGA_print_at(msg, -1, -1);
}

void VGA_print_color(char* msg, char color)
{
   VGA_print_color_at(msg, color, -1, -1);
}

char VGA_create_bg_fg_color(char bg, char fg)
{
   return (bg << 4) + fg;
}

////////////////////////
///      PRIVATE     ///
////////////////////////

int print_char(char c, int col, int row, char color)
{
   unsigned char* video = (unsigned char*)VGA_VIDEO_MEM;

   if (row >= VGA_MAX_ROW) {
      set_cursor_offset(get_offset(0,0));
      VGA_clear_screen();
      col = 0;
      row = 0;
   }

   if (col >= VGA_MAX_COL || row >= VGA_MAX_ROW)
   {
      video[2*VGA_MAX_COL*VGA_MAX_ROW-2] = 'X';
      video[2*VGA_MAX_COL*VGA_MAX_ROW-1] = VGA_create_bg_fg_color(VGA_RED, VGA_LIGHTRED);
      return get_offset(col, row);
   }

   int offset;
   if (col >= 0 && row >= 0) offset = get_offset(col, row);
   else offset = get_cursor_offset();

   if (c == '\n')
   {
      row = get_offset_row(offset);
      offset = get_offset(0, row+1);
   } else {
      video[offset] = c;
      video[offset+1] = color;
      offset += 2;
   }


   set_cursor_offset(offset);

   return offset;
}

int get_cursor_offset()
{
   port_byte_out(VGA_SCREEN_CTRL, 14);
   int offset = port_byte_in(VGA_SCREEN_DATA) << 8;
   port_byte_out(VGA_SCREEN_CTRL, 15);
   offset += port_byte_in(VGA_SCREEN_DATA);
   return offset*2;
}

void set_cursor_offset(int offset)
{
   offset /= 2;
   port_byte_out(VGA_SCREEN_CTRL, 14);
   port_byte_out(VGA_SCREEN_DATA, (unsigned char)(offset >> 8));
   port_byte_out(VGA_SCREEN_CTRL, 15);
   port_byte_out(VGA_SCREEN_DATA, (unsigned char)(offset & 0xff));
}

int get_offset(int col, int row) { return 2 * (row * VGA_MAX_COL + col); }
int get_offset_row(int offset) { return offset / (2 * VGA_MAX_COL); }
int get_offset_col(int offset) { return (offset - (get_offset_row(offset) * 2 * VGA_MAX_COL)) / 2; }

