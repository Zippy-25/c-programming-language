#include <stdio.h>
 
 void main()
 {
 int c, nl, nb, nt;
 nl = 0; nb = 0; nt = 0;
 while ((c = getchar()) != EOF){
  if (c == '\n')
  ++nl;
  if (c == ' ')
  ++nb;
  if (c == '\t')
  ++nt;}
 printf("Number of new lines:%d, blanks:%d, tabs:%d\n", nl, nb, nt);
 } 
