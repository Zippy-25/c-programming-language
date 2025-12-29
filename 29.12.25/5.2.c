/*Exercise 5-2. Write getfloat, the floating-point analog of getint. What type does
getfloat return as its function value?*/

#include<stdio.h>
#include<ctype.h>
#define MAXBUF 100
#define SIZE 100

int getch(void);
void ungetch(int);
int bufp = 0;
int buf[MAXBUF];

int getfloat(float* f)
{
	int c, sign, pow;
	pow = 1;
	
	while(isspace(c = getch()));
	
	if(!isdigit(c) && c!=EOF && c!= '+' && c!= '-' && c!= '.'){
		ungetch(c);
		return 0; // return 0 if a non valid character is entered
	}
	
	sign = (c == '-')? -1:1;
	
	if(c == '+' || c == '-')
		c = getch();
	
	for(*f = 0; isdigit(c); c = getch())
		*f = *f*10 + (c - '0');
	if(c == '.'){
		c = getch();
		for(; isdigit(c); c = getch()){
			pow *= 10;
			*f = *f*10 + (c - '0');
		}
	}
	
	*f = *f * sign / pow;
	if(c != EOF)	ungetch(c);
	return c; //return f if a valid number is entered
}

void main()
{
	int n, i;
	float array[SIZE];
	for (n = 0; n < SIZE && getfloat(&array[n]) != EOF; n++) ;
	
	for (i = 0; i < n; i++)	printf("\n%f", array[i]);
	
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
