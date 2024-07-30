#include "utility.h"

void int_to_ascii(int n, char str[])
{
   int i, sign;
   if ((sign = n) < 0) n = -n;
   i = 0;
   do {
       str[i++] = n % 10 + '0';
   } while ((n /= 10) > 0);

   if (sign < 0) str[i++] = '-';
   str[i] = '\0';

   reverse(str);
}

int strlen(char s[]) {
    int i = 0;
    while (s[i] != '\0') ++i;
    return i;
}

void reverse(char s[]) {
    int c, i, j;
    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void memorycpy(char* source, char* dest, int size)
{
   for (int i = 0; i < size; i++)
   {
      *(dest+i) = *(source+i);
   }
}

void memorycpyi(int* source, int* dest, int size)
{
   for (int i = 0; i < size; i++)
   {
      *(dest+i) = *(source+i);
   }
}
