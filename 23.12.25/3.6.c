/*Write a version of itoa that accepts three arguments instead of two. The third
argument is a minimum field width; the converted number must be padded with blanks on the
left if necessary to make it wide enough.*/

#include <stdio.h>
#include <string.h>

void reverse(char s[])
{
  char c;
  int i, j, k;
  for(i = 0, j = strlen(s) - 1; i < j; i++, j--){
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}

/* itoa: convert n to characters in s */
void itoa(int n, char s[], int w)
{
int i, sign, j;
i = 0;
sign = n < 0? -1 : 1;
do {
s[i++] = (sign)*(n % 10) + '0'; 
} while ((n /= 10) != 0);

if (sign < 0)
s[i++] = '-';
w -= i;
while(w--)  s[i++] = ' ';
s[i] = '\0';
reverse(s);
}

void main()
{
  char s[50];
  int n;
  n = -(int)((unsigned int)~0 >> 1) - 1;
  itoa(n, s, 35);
  printf("%s\n", s);
}
