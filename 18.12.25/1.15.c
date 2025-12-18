/*Rewrite the temperature conversion program of Section 1.2 to use a function
for conversion*/
#include<stdio.h>

float temp_conv(float);

void main()
{
  float fahr, celsius, i;
  float lower, upper, step;
  lower = 0;
  upper = 300;
  step = 20;
  
  fahr = lower;
  for (i = lower; i <= upper; i = i + 20)
    printf("%3.0f %6.1f\n", i, temp_conv(i));
}

float temp_conv(float f)
{
  return (5.0/9.0) * (f - 32.0);
}
