/*Exercise 5-4. Write the function strend(s,t), which returns 1 if the string t occurs at the
end of the string s, and zero otherwise.*/

#include<stdio.h>

int strend(char *s, char *t)
{
	char *d = t;
	while(*s)
	{
		if(*s == *d)
		{
			d++;
		} 	
		else if(d!=t && *(d = t) == *s ) d++; //this line checks the mismatched character of s again with the resetted d
		s++;				
	}
	if(!(*s) && !(*d)) return 1;
	else return 0;
}

void main()
{
	char s[] = "ababab";
	char t[] = "abab";
	printf("%d\n", strend(s,t));
}
