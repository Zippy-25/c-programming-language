#include<stdio.h>

void main()
{
  float fahr, celsius;
  float lower, upper, step;
  
  lower = 0;
  upper = 300;
  step = 20;
  
  celsius = lower;
  printf("Celsius Fahrenheit\n");
  while(celsius <= upper)
  {
    fahr = ((5.0/9.0) * celsius) + 32.0;
    printf("%5.0f %10.1f\n", celsius, fahr);
    celsius = celsius + step;
  }
}
