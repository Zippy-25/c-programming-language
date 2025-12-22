/*Write a function for the other direction as well, converting escape sequences into the real characters.*/

#include<stdio.h>

void escape_r(char s[], char t[])
{
  int i, j;
  i = j = 0; 
  while(s[i] != '\0')
  {
    switch(s[i]){
      case('\\'): 
        switch(s[++i]){
          case('n'):
            t[j++] = '\n';
            break;
          case('t'):
            t[j++] = '\t';
            break;
        }
      break;
      default:
        t[j++] = s[i];
    }
    i++;
  }
  t[j] = '\0';
}

void getstring(char s[])
{
  int c, i;
  i = 0;
  while((c = getchar()) != EOF){
    s[i] = c; i++;
  }
  s[i] = '\0';
}
void main()
{
  char s[50], t[50];
  getstring(s);
  escape_r(s, t);
  printf("%s\n", t);
}
