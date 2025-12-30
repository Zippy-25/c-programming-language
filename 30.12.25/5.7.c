/*Exercise 5-7. Rewrite readlines to store lines in an array supplied by main, rather than
calling alloc to maintain storage. How much faster is the program?*/

#include<stdio.h>
#include<string.h>

#define MAXLINES 5000
#define MAXLEN 1000

char *lineptr[MAXLINES];
char str_line[MAXLINES*MAXLEN];
static char* str_last = str_line;

int readlines(char *lineptr[], char *str_line, int nlines);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

void main()
{
	int nlines;
	
	if((nlines = readlines(lineptr, str_line, MAXLINES)) >= 0)
	{
		qsort(lineptr, 0, nlines-1);
		writelines(lineptr, nlines);
	}
	else
		printf("Input is too big to sort\n");
}

int get_line(char *line, int max)
{
	int n, c;
	n = 0;
	while(n < max && (c = getchar()) != EOF && c!= '\n')	line[n++] = c;
	if(c == '\n') line[n++] = '\n';
	line[n]='\0';
	return n;
}

int readlines(char *lineptr[], char *str_line, int nlines)
{
	int len, n;
	char line[MAXLEN];
	n = 0;
	
	while((len = get_line(line, MAXLEN-1)) > 0)
		if(n > nlines || (str_last+len - str_line) >= MAXLINES*MAXLEN)
			return -1;
		else{
			line[len-1] = '\0';
			strcpy(str_last, line);
			lineptr[n++] = str_last;
			str_last+=len;
		}
	return n;
}

void writelines(char* lineptr[], int nlines)
{
	int i;
	for(i = 0; i < nlines; i++)
		printf("%s\n", lineptr[i]);
}

void qsort(char *v[], int left, int right)
{
	void swap(char **, int, int);
	int i, last;
	
	if (left>=right) return;
	
	swap(v, left, (left+right)/2);
	
	last = left;
	for(i = left+1; i<=right; i++)
		if(strcmp(v[i], v[left]) < 0)
			swap(v, ++left, i);
	swap(v, left, last);
	
	qsort(v, left, last - 1);
	qsort(v, last+1, right);
}

void swap(char *v[], int i, int j)
{
	char *temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

/*
#define ALLOCLEN 1000

static char allocbuf[ALLOCLEN];
static char *allocp = allocbuf;

char* alloc(int n)
{
	if(allocbuf+ALLOCLEN-allocp >= n){
		allocp+=n;
		return allocp - n;}
	else	return NULL;	
}

void _free(char *p)
{
	if(p >= allocbuf && p < allocbuf+ALLOCLEN )
		allocp = p;
}
*/
