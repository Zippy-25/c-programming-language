/*Exercise 2.2
Write a loop equivalent to the for loop of printing the longest line(from previous example) without using && or ||*/

#include<stdio.h>

#define MAX 1000

int get_line(char line[], int lim);
void copy(char to[], char from[]);

void main()
{
  int len, max = 0;
  char line[MAX], longest[MAX];
  
  while((len = get_line(line, MAX-1)) > 0){
    printf("%d\n", len);
    if(len > max){
      max = len;
      copy(longest, line);
    }
  }
  if(max > 0)  printf("%s", longest);
}

int get_line(char line[], int lim)
{
  int c, i;
  for(i = 0; i < lim - 1; i++)
  {
    c = getchar();
    if(c == '\n') break; 
    if(c == EOF) break; 
    line[i] = c;
  }
  if(c == '\n') line[i] = '\n';
  if (i > 0) line[++i] = '\0';
  printf("Leaving the get line: %d\n", i);
  return i;
}

void copy(char to[], char from[])
{
  int i = 0;
  while((to[i] = from[i]) != '\0') ++i;
}
