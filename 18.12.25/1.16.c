/*Revise the main routine of the longest-line program so it will correctly print
the length of arbitrary long input lines, and as much as possible of the text*/
#include<stdio.h>

#define MAX 1000

int get_line(char line[], int lim);
void copy(char to[], char from[]);

void main()
{
  int max, len;
  char line[MAX+1];
  char longest[MAX+1];
  max = 0;
  while((len = get_line(line, MAX)) > 0) 
    if(len > max){
    max = len;
    copy(line, longest);
  }
  if(max > 0) printf("%s", longest);
}

int get_line(char line[], int lim)
{
  int i, c;
  for(i = 0; i < MAX-1 && (c = getchar()) != EOF && c != '\n' ; i++)
    line[i] = c;
  if(c == '\n') line[i] = '\n';
  else 
  {
    while((c = getchar()) != EOF && c!= '\n') ++i;
  }
  if(i > 0) line[++i] = '\0';
  return i;
}

void copy(char from[], char to[])
{
int i = 0;
  while((to[i] = from[i]) != '\0') ++i;
}

