/*In a two's complement number representation, our version of itoa does not
handle the largest negative number, that is, the value of n equal to -(2wordsize-1). Explain why
not. Modify it to print that value correctly, regardless of the machine on which it runs.*/

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
void itoa(int n, char s[])
{
int i, sign, j;
i = 0;
sign = n < 0? -1 : 1;
do {
s[i++] = (sign)*(n % 10) + '0'; 
} while ((n /= 10) != 0);

if (sign < 0)
s[i++] = '-';  
s[i] = '\0';
reverse(s);
}

void main()
{
  char s[50];
  int n;
  n = -(int)((unsigned int)~0 >> 1) - 1;
  itoa(n, s);
  printf("%s\n", s);
}
