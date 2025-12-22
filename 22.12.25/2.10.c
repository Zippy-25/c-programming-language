/*Rewrite the function lower, which converts upper case letters to lower case,
with a conditional expression instead of if-else.*/

#include<stdio.h>

int lower(int c)
{
  c = (c >= 'A' && c <= 'Z')? c + 'a' - 'A' : c;
  return c;
}

void main()
{
  printf("%c\n", lower('M'));
}
