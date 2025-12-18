/*How would you test the word count program? What kinds of input are most
likely to uncover bugs if there are any?*/

#include<stdio.h>

#define IN 1
#define OUT 0

void main()
{
  int c, nl, nw, nc, state;
  nl = nw = nc = 0;
  while((c = getchar()) != EOF){
    ++nc;
    if(c == '\n')
      ++nl;
    if(c == ' ' || c == '\t' || c == '\n')
      state = OUT;
    else if( state == OUT){
      state = IN;
      ++nw;
    }
  }
  printf("%d %d %d\n", nc, nw, nl);
}
