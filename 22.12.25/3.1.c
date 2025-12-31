/*Our binary search makes two tests inside the loop, when one would suffice (at
the price of more tests outside.) Write a version with only one test inside the loop and
measure the difference in run-time.*/

#include<stdio.h>

int binsearch(int x, int v[], int n)
{
  int low, high, mid;
  low = 0;
  high = n -1;
  mid = (low + high) / 2;
  while(low <= high && x != v[mid])
  {
    if (x < v[mid]) high = mid - 1;
    else low = mid + 1;
    mid = (low + high) / 2;
  }
  if(v[mid] == x) return mid;
  return -1;
}

void main()
{
  int v[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  printf("%d\n", binsearch(5, v, 9));
}
