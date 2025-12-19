/*Exercise 2-4. 
Write an alternative version of squeeze(s1,s2) that deletes each character in s1 that matches any character in the string s2.*/

#include<stdio.h>

void rsqueeze (char s1[], char s2[])
{
  int i, j, k;
  for(i = 0, k = 0; s1[i] != '\0'; i++){
    for(j = 0; s2[j] != '\0' && s1[i] != s2[j]; j++);
    if(s2[j] == '\0') s1[k++] = s1[i];}
  s1[k] = '\0';
}

void main()
{
  char s1[] = "alphabet";
  char s2[] = "above";
  rsqueeze(s1, s2);
  printf("%s", s1);
}
