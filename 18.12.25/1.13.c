/*Write a program to print a histogram of the lengths of words in its input - horizontal histogram*/
#include<stdio.h>

#define MAXLENGTH 20

void main()
{
  int c, i, j, overflow, len, max;
  int length[MAXLENGTH];
  
  len = overflow = max = 0;
  
  for(i = 0; i < MAXLENGTH; i++)
    length[i] = 0;
  
  while((c = getchar()) != EOF){
    if (c == ' ' || c == '\n' || c == '\t'){
      if(len > 0 && len <= MAXLENGTH)
        ++length[len-1];
      else if (len > 0 && len > MAXLENGTH)
        ++overflow;
      len = 0;
    }
    else
      ++len;
  }
  
  if(len != 0)
    ++length[len-1];
    
  for(i=0; i < MAXLENGTH; i++){
    printf("\n%4d |", i+1);
    for(j = 0; j < length[i]; j++)  printf("*");
  }
  
  printf("\n>%3d |", MAXLENGTH);
  for(i = 0; i < overflow; i++) printf("*");
  printf("\n");
}
