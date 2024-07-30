
#define VGA 0x0A0000

#define RED 0x28
#define YELLOW 0x2c
#define GREEN 0x30

void DrawPixel(int x, int y, char color)
{
   int i = x + 320 * y;
   char* g = (char*)VGA+i;
   *g = color;
}

void EightWaySymmetricPlot(int xc,int yc,int x,int y)  
{  
    DrawPixel(x+xc,y+yc,0x0f);  
    DrawPixel(x+xc,-y+yc,0x0f);  
    DrawPixel(-x+xc,-y+yc,0x0f);  
    DrawPixel(-x+xc,y+yc,0x0f);  
    DrawPixel(y+xc,x+yc,0x0f);  
    DrawPixel(y+xc,-x+yc,0x0f);  
    DrawPixel(-y+xc,-x+yc,0x0f);  
    DrawPixel(-y+xc,x+yc,0x0f);  
}  

void DrawX(int x, int y, int r)
{
   int xc = 0, yc = r, d = 3 - (2 * r);
   EightWaySymmetricPlot(x, y, xc, xc);

   while (xc <= yc)
   {
      if (d <= 0)
      {
         d = d + (4*xc) + 6;
      }
      else {
         d = d + (4*xc)-(4*yc) + 10;
         yc--;
      }
      xc++;
      EightWaySymmetricPlot(x, y, xc, xc);
   }
}

void main()
{
   //VGA_clear_screen();


   /*
   char s[5];
   for (int i = 0; i < 1; ++i)
   {
      int_to_ascii(i, s);
      VGA_print_at(s, -1, i);
   }
   */
   
   DrawX(160, 100, 60);

   char* video = (char*)0x0A0000;
   *video = 0x0B;
}
