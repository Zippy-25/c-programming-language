/*Exercise 4-12. Adapt the ideas of printd to write a recursive version of itoa; that is, convert
an integer into a string by calling a recursive routine.*/


#include<stdio.h>
#include<stdlib.h>

#define MOD(n) abs(n)%10

void itoa(int n, char s[])
{
	
	static int i = 0;
	
	if(n/10) itoa(n/10, s);
	else if(n < 0) s[i++] = '-';
	
	s[i++] = MOD(n) + '0';
	//printf("%c\n", s[i-1]);
	s[i] = '\0'; 
}

void main()
{
	int i;
	i = -529;
	char s[30];
	
	itoa(i, s);
	printf("%s\n", s);
}
