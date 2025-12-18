/*Write a program to print a histogram of the lengths of words in its input - vertical histogram*/
#include<stdio.h>
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
  
  max = length[0];
  for(i = 1; i < MAXLENGTH; i++){
    if(max < length[i]) max = length[i];
  }
  
  for(i = max; i >0; i--){
  printf("\n%3d |", i);
    for(j = 0; j < MAXLENGTH; j++){
      if(length[j] >= i) printf("* ");
      else printf("  ");
    }
    if(overflow >= i) printf("* ");
  }
  printf("\n");
  for(i = 0; i < MAXLENGTH; i++) printf("---");
  printf("\n%6d ", 1);
  for(i = 2; i < MAXLENGTH; i++)
  printf("%d ", i);
  printf(">%d", MAXLENGTH);
  printf("\n");
}
