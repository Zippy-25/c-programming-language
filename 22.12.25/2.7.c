/*Write a function invert(x,p,n) that returns x with the n bits that begin at
position p inverted (i.e., 1 changed into 0 and vice versa), leaving the others unchanged.*/

#include<stdio.h>

unsigned invert(unsigned x, int p, int n)
{
  unsigned int mask = ~(~0 << n) << p+1-n;
  return x & ~mask | ~x & mask;
}

void main()
{
  printf("%b\n", 218);
  printf("%b\n", invert(218, 4, 3));
}

