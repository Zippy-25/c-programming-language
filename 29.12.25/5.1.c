/*Exercise 5-1. As written, getint treats a + or - not followed by a digit as a valid
representation of zero. Fix it to push such a character back on the input.*/

/*Answer: so, here the motive is to push the extra character read like + or - back to buffer. so if we have an example like ++var, then reading + and then reading the next + we rule out that this is not a digit and thus return 0, but then continue reading var, leaving out the both ++, which is not preferred in real cases. so wehn we encounter non integers, we push them back to the buffer and return 0 indicating the input is not a number*/

#include<stdio.h>
#include<ctype.h>

#define MAXBUF 100
#define SIZE 100

int getch(void);
void ungetch(int);

int bufp = 0;
int buf[MAXBUF];

int getint(int *pn){

	int c, sign, next;
	
	while(isspace(c = getch())) ;
	
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c);
		return 0;
	}
	
	sign = (c == '-')? -1: 1;
	
	if(c == '+' || c == '-')
	{
		next = getch();
		
		if(!isdigit(next)){
			if(next != EOF)	ungetch(next);
				ungetch(c); //sign remains in the top of te stack
			return 0; 
		}
		c = next;
		 
	}
	
	for(*pn = 0; isdigit(c); c = getch())
		*pn = *pn*10 + (c - '0');
	*pn *= sign;
	if(c != EOF)
		ungetch(c);
	return c;
}

void main()
{
	int n, array[SIZE], i;
	for (n = 0; n < SIZE && getint(&array[n]) != EOF; n++) ;
	
	for (i = 0; i < n; i++)	printf("\n%d", array[i]);
	
}

int getch(void)
{
	return (bufp == 0)? getchar():buf[--bufp];
}

void ungetch(int c)
{
	if(bufp >= MAXBUF) printf("Buffer limit exceeded\n");
	else	buf[bufp++] = c;
} 
