/*Write a function escape(s,t) that converts characters like newline and tab
into visible escape sequences like \n and \t as it copies the string t to s. Use a switch.*/

#include<stdio.h>

void escape(char s[], char t[])
{
  int i, j;
  i = j = 0; 
  while(s[i] != '\0')
  {
    switch(s[i]){
      case('\n'): 
        t[j++] =  '\\';
        t[j++] = 'n';
        break;
      case('\t'):
        t[j++] = '\\';
        t[j++] = 't';
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
  escape(s, t);
  printf("%s\n", t);
}
