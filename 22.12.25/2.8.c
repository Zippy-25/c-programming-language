/*Write a function rightrot(x,n) that returns the value of the integer x rotated
to the right by n positions.*/

#include<stdio.h>

unsigned rightrot(unsigned x, int n)
{
  return x << (sizeof(unsigned)*8 - n) | x >> n;
}

void main()
{
  printf("%b\n", rightrot(0b11011110, 3));
}
