/*Write a function expand(s1,s2) that expands shorthand notations like a-z in
the string s1 into the equivalent complete list abc...xyz in s2. Allow for letters of either
case and digits, and be prepared to handle cases like a-b-c and a-z0-9 and -a-z. Arrange
that a leading or trailing - is taken literally.*/

#include<stdio.h>

void expand(char s1[], char s2[])
{
  int i, j, c;
  i = j = 0;
  while((c = s1[i++]) != '\0')
  {
    if(s1[i] == '-' && s1[i+1] > c){
      i++;
      while(s1[i] > c)
        s2[j++] = c++;
    }
    else
      s2[j++] = s1[i];
  }
  s2[j] = '\0';
}

void getstring(char s1[])
{
  int c, i;
  i = 0;
  while((c = getchar()) != EOF){
    s1[i] = c; i++;
  }
  s1[i] = '\0';
}

void main()
{
  char s1[25], s2[25];
  getstring(s1);
  expand(s1, s2);
  printf("%s\n", s2);
}
