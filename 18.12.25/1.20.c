/*Write a program detab that replaces tabs in the input with the proper number
of blanks to space to the next tab stop. Assume a fixed set of tab stops, say every n columns.
Should n be a variable or a symbolic parameter*/
#include<stdio.h>

#define tab 8

void main()
{
  int c, pos, ntabs;
  pos = 0;
  while((c = getchar()) != EOF)
  {
    if(c == '\t')
    {
      ntabs = tab - (pos % tab);
      while(ntabs--){
        pos++;
        printf("#");
      }
    }
    else if(c == '\n')
      pos = 1;
    else{
      pos++;
      putchar(c);
      }
  }
}
