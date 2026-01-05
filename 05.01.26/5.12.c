/*Exercise 5-12. Extend entab and detab to accept the shorthand
entab -m +n
to mean tab stops every n columns, starting at column m. Choose convenient (for the user)
default behavior.*/

#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>

#define MAXLINE 100
#define TABINC 8
#define YES 1
#define NO 0

void entab(int *tab);
void detab(int *tab);
void _settab(int argc, char *argv[], int* tab);
int tabpos(int pos, int * tab);

int main(int argc, char *argv[])
{
	int tab[MAXLINE];
	_settab(argc, argv, tab);
	entab(tab);
	detab(tab);
	return 0;
}

void _settab(int argc, char* argv[], int *tab)
{
	int i, inc, pos;
	
	if (argc <= 1)
		for(i = 1; i < MAXLINE; i++)
			if(i % TABINC == 0)	tab[i] = YES;
			else tab[i] = NO;
	else if (argc == 3 && *argv[1] == '-' && *argv[2] == '+') {
	        pos = atoi(&(*++argv)[1]);
        	inc = atoi(&(*++argv)[1]);
        	
        	for(i = 1; i < MAXLINE; i++)
        		if(i != pos)	tab[i] = NO;
        		else{
        			tab[i] = YES;
        			pos += inc;
        		}
        }
        else{
		for(i = 1; i < MAXLINE; i++)
			tab[i] = NO;
		while(--argc > 0){
			pos = atoi(*++argv);
			if(pos > 0 && pos < MAXLINE)	tab[pos] = YES;
		}
	}
}
void detab(int *tab)
{
	int c, pos;
	pos = 1;
	while((c = getchar()) != EOF)
	{
		if(c == '\t')
			do	putchar('_');
			while(tabpos(pos++, tab) != YES);
		else if(c == '\n'){
			putchar(c);
			pos = 1;
		}
		else{
			putchar(c);
			pos++;
		}
	}
}

void entab(int *tab)
{
	int c, pos, nb, nt;
	pos = 1;
	nb = nt = 0;
	while((c = getchar()) != EOF)
	{
		if(c == ' ')
			if(tabpos(pos, tab) == YES){
				nb = 0;
				nt++;
			}
			else nb++;
	else
	{
		for(;nt-- > 0; putchar('t'));
		if(c == '\t')
			nb  = 0;
		for(; nb > 0; nb--) putchar('b');
		putchar(c);
		if(c == '\n')	pos = 0;
		if(c == '\t') while(tabpos(pos, tab) != YES) pos++;
	}
	pos++;
}
}

int tabpos(int pos, int * tab)
{
	if(pos > MAXLINE) return YES;
	else return tab[pos];
}

