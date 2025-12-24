/*Write a routine ungets(s) that will push back an entire string onto the input.
Should ungets know about buf and bufp, or should it just use ungetch?*/

#include<stdio.h>
#include<string.h>

#define MAXLINE 1000
#define MAXBUF 100

int getch(void);
void ungetch(int);

void get_line(char s[], int);
void ungets(char s[]);

int bufp = 0;
int buf[MAXBUF];

void main()
{
	char s[MAXLINE]; 
	int c;

	    get_line(s, MAXLINE-1);

	    ungets(s);

	    while ((c = getch()) != EOF)
		putchar(c);
}

void get_line(char s[], int lim)
{
	int c, i;
	i = 0;
	while(lim -- && (c = getch()) != EOF && c != '\n'){
		s[i] = c;
		i++;
	}
	if(c == '\n') s[i++] = c;
	s[i] = '\0';
}

int getch(void)
{
	return (bufp > 0)? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if(bufp < MAXBUF)	buf[bufp++] = c;
	else printf("Buffer size exceeded\n");
}

void ungets(char s[])
{
	int i;
	i = strlen(s);
	while(i--)	ungetch(s[i]);
}

