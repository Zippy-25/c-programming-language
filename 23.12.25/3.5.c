/*Write the function itob(n,s,b) that converts the integer n into a base b
character representation in the string s. In particular, itob(n,s,16) formats s as a
hexadecimal integer in s.*/

#include<stdio.h>
#include<string.h>

void reverse(char s[])
{
  int c, i, j;
  i = j = 0;
  for(i = 0, j = strlen(s) - 1; i < j; i++, j--)
  {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}

void itob(int n, char s[], int b)
{
  int i, j, sign;
  i = 0;
  sign = (n < 0)? -1:1;
  do
  {
    j = sign*(n % b);
    s[i++] = j < 10 ? j + '0' : j + 'a' - 10;
  }
  while((n /= b) != 0);
  if(sign == -1)  s[i++] = '-';
  s[i] = '\0';
  reverse(s);
}

void main()
{
  char s[50];
  int n;
  n = -(int)((unsigned int)~0 >> 1) - 1;
  itob(n, s, 16);
  printf("%s\n", s);
}
