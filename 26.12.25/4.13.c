/*Exercise 4-13. Write a recursive version of the function reverse(s), which reverses the
string s in place.*/

#include<stdio.h>

void reverse(char s[])
{
	static int i = -1;
	static int j = 0;
	char c;
	
	if(s[++i] != '\0')
	{
		c = s[i];
		reverse(s);
	}
	
	s[j++] = c;	 
	printf("%c\n", s[j-1]);
}

void main()
{
	char s[] = "twinkle twinkle";
	reverse(s);
	printf("%s\n", s);
}

