/*Write a program to print all input lines that are longer than 80 characters*/
#include<stdio.h>

#define MAX 1000
#define LIMIT 80

int get_line(char line[], int lim);

void main()
{
  int len;
  char line[MAX+1];

  while((len = get_line(line, MAX)) > 0) {
  if(len > LIMIT)
    printf("%s", line);
  }
}

int get_line(char line[], int lim)
{
  int i, c;
  for(i = 0; (i < MAX && (c = getchar()) != EOF && c != '\n') ; i++)
    line[i] = c;
  if(c == '\n') line[i] = '\n';
  if(i > 0) line[++i] = '\0';
  return i;
}


