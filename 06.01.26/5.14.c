/*Exercise 5-14. Modify the sort program to handle a -r flag, which indicates sorting in reverse
(decreasing) order. Be sure that -r works with -n.*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXLINES 1000
#define MAXLEN 1000
#define ALLOCSIZE 10000 

static char allocbuf[ALLOCSIZE]; 
static char *allocp = allocbuf; 

void _qsort(void* v[], int left, int right, int(*comp)(void*, void*));
void swap(void* v[], int i, int j);
int readlines(char* lineptr[], int lim);
void writelines(char* lineptr[], int lim, int reverse);
int _getline(char *line, int lim);
int numcmp(char* s1, char* s2);
char *alloc(int n);

void main(int argc, char *argv[])
{
	int nlines;
	int numeric = 0, reverse = 0;
	char *lineptr[MAXLINES];
	
	if(argc > 1 && argv[1][0] == '-'){
		if(argv[1][1] == 'n')	numeric = 1;
		else if(argv[1][1] == 'r')	reverse = 1;
		
		if(argv[1][2] == 'n')	numeric = 1;
		else if(argv[1][2] == 'r')	reverse = 1;
		
	}
		
	if((nlines = readlines(lineptr, MAXLINES)) > 0){
		_qsort((void**)lineptr, 0, nlines-1, (int(*)(void*, void*))(numeric? numcmp:strcmp));
		writelines(lineptr, nlines, reverse);
	}
	else	printf("input too large\n");
}

void _qsort(void* v[], int left, int right, int(*comp)(void*, void*))
{
	int i, last;
	if(left>=right) return;
	swap(v, left, (left+right)/2);
	last = left;
	for(i = left+1; i<=right; i++)
		if((*comp)(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	_qsort(v, left, last-1, comp);
	_qsort(v, last+1, right, comp);
}

void swap(void* v[], int i, int j)
{
	void* temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

int readlines(char* lineptr[], int lim)
{
	int nlines, len;
	nlines = 0;
	char *p;
	char line[MAXLEN];
	while((len = _getline(line, MAXLEN-1)) > 0)
	{
		if(nlines >= lim || (p = alloc(len)) == NULL)	return -1;
		else{
			line[len-1] = '\0';
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	}
	printf("%d\n", nlines);
	return nlines;
}

int _getline(char *line, int lim)
{
	int i = 0;
	int c;
	while(--lim && (c = getchar()) != EOF && c!='\n')	line[i++] = c;
	if(c == '\n')	line[i++] = '\n';
	line[i] = '\0';
	return i;
}

void writelines(char* lineptr[], int lim, int reverse)
{
	int i;
	for(i = 0; !reverse && i<lim; i++)	printf("%s\n", lineptr[i]);
	for(i = lim-1; reverse && i>=0; i--)	printf("%s\n", lineptr[i]);
}

int numcmp(char* s1, char* s2)
{
	double v1, v2;
	v1 = atof(s1);
	v2 = atof(s2);
	if(v1>v2)	return 1;
	else if(v1<v2) return -1;
	else return 0;
}

char *alloc(int n)
{
	if (allocbuf + ALLOCSIZE - allocp >= n) { 
	allocp += n;
	return allocp - n; 
	} else return 0;
}
