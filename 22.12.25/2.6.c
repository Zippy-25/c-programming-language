/*Write a function setbits(x,p,n,y) that returns x with the n bits that begin at
position p set to the rightmost n bits of y, leaving the other bits unchanged.*/

#include<stdio.h>

unsigned setbits(unsigned x, int p, int n, unsigned y)
{
  unsigned mask = ~(~0 << n);
  y = (y & mask) << p+1-n;
  x = x & ~(mask << p+1-n);
  return x|y;
}

void main()
{
  printf("%b\n", setbits(218, 4, 3, 5));
}
