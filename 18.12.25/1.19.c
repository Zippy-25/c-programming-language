/*Write a function reverse(s) that reverses the character string s. Use it to
write a program that reverses its input a line at a time*/
#include<stdio.h>

#define MAX 1000

int get_line(char line[], int lim);
void _reverse(char line[]);

void main()
{
  int len;
  char line[MAX+1];

  while((len = get_line(line, MAX)) > 0) {
    _reverse(line);
    printf("%s", line);
  }
}

int get_line(char line[], int lim)
{
  int i, c;
  for(i = 0; (i < MAX-1 && (c = getchar()) != EOF && c != '\n') ; i++)
    line[i] = c;
  if(c == '\n') line[i] = '\n';
  if(i > 0) line[++i] = '\0';
  return i;
}

void _reverse(char line[])
{
  int i, j, len;
  for(len = 0; line[len] != '\0'; ++len);
  if (line[len-1] == '\n') --len;
  for(i = 0, j = len-1; i < len/2 && i < j; i++, j--)
  {
    int t;
    t = line[i];
    line[i] = line[j];
    line[j] = t;
  }
}


