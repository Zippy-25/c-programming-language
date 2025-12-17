#include<stdio.h>

void main()
{
  float fahr, celsius;
  float lower, upper, step;
  
  lower = 0;
  upper = 300;
  step = 20;
  
  fahr = lower;
  printf("Fahrenheit Celsius\n");
  while(fahr <= upper)
  {
    celsius = (5.0/9.0) * (fahr - 32.0);
    printf("%5.0f %10.1f\n", fahr, celsius);
    fahr = fahr + step;
  }
}
