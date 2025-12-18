/*Write a program to remove trailing blanks and tabs from each line of input,
and to delete entirely blank lines*/
#include<stdio.h>

#define MAX 1000

int get_line(char line[], int lim);
int _remove(char line[], int lim);

void main()
{
  int len, rlen;
  char line[MAX];

  while((len = get_line(line, MAX)) > 0) {
    printf("Length with trailing tabs and blank spaces: %d\n", len);
    if((rlen = _remove(line, len)) > 0){
      printf("Length without trailing tabs and blank spaces: %d\n", rlen);
      printf("%s", line);
    }
  }
}

int get_line(char line[], int lim)
{
  int i, c;
  for(i = 0; (i < MAX - 1 && (c = getchar()) != EOF && c != '\n') ; i++)
    line[i] = c;
  if(i > 0) line[i] = '\0';
  return i;
}

int _remove(char line[], int lim)
{
  int i = lim - 2;
  while(line[i] == ' ' || line[i] == '\t') --i;
  line[++i] = '\n';
  line[++i] = '\0';
  return i;
}

