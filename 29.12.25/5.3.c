/*Exercise 5-3. Write a pointer version of the function strcat that we showed in Chapter 2:
strcat(s,t) copies the string t to the end of s.*/

#include<stdio.h>

void _strcat(char *s, char *t)
{
	while(*s++);
	
	--s;
	
	while(*s++ = *t++);
}

void main()
{
	char s[100] = "Auto tune";
	char t[100] = "the rythym";
	_strcat(s, t);
	printf("%s\n", s);
}
