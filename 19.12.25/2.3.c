/*Exercise 2.3
Write a function htoi(s), which converts a string of hexadecimal digits (including an optional 0x or 0X) into its equivalent integer value. The allowable digits are 0 through 9, a through f, and A through F.*/

#include<stdio.h>

int htoi(char s[])
{
  int i, j, p, n, len;
  n = 0;
  p = 1;
  
  for(i = 0; s[i] != '\0'; i++);
  len = i;
  if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
    i = 2;
  
  for(j = len - 1; j >= i; j--)
  {
    if(s[j] >= '0' && s[j] <= '9')
      n = n + p*(s[j] - '0');
    else if(s[j] >= 'A' && s[j] <= 'F')
      n = n + p*(s[j] - 55);
    else if(s[j] >= 'a' && s[j] <= 'f')
      n = n + p*(s[j] - 87);
    else return 0;
    p = p * 16;
  }
  return n;
}

void main()
{
  char a[] = "0xA5";
  printf("%d", htoi(a));
}

