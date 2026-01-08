/*Exercise 6-1. Our version of getword does not properly handle underscores, string constants,
comments, or preprocessor control lines. Write a better version.*/

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#define MAXWORD 100
#define NKEYS (sizeof(keytab) / sizeof(keytab[0]))
  
struct key {
    char *word;
    int count;
} keytab[] = {"auto", 0, "break", 0, "case", 0, "char", 0,
              "const", 0, "continue", 0, "default", 0, "do", 0,
              "double", 0, "else", 0, "enum", 0, "extern", 0,
              "float", 0, "for", 0, "goto", 0, "if", 0,
              "int", 0, "long", 0, "register", 0, "return", 0,
              "short", 0, "signed", 0, "sizeof", 0, "static", 0,
              "struct", 0, "switch", 0, "typedef", 0, "union", 0,
              "unsigned", 0, "void", 0, "volatile", 0, "while", 0};
       
int binsearch(char*, struct key*, int);
int getword(char*, int);     

void main()
{
	char word[MAXWORD];
	int n;
	while(getword(word, MAXWORD) != EOF){
		if(isalpha(word[0]))
			if((n = binsearch(word, keytab, NKEYS)) >= 0){
				printf("%s\n", word);
				keytab[n].count++;}
	}
	for(n = 0; n < NKEYS; n++)
		if(keytab[n].count > 0)
			printf("%4d %s\n", keytab[n].count, keytab[n].word);
}

int binsearch(char* word, struct key tab[], int lim)
{
	int left, right, mid, cond;
	left = 0;
	right = lim - 1;
	
	while(left<=right){
	
		mid = (left+right)/2;
		if((cond = strcmp(tab[mid].word, word)) == 0)
			return mid;
		else if(cond < 0)
			left = mid + 1;
		else if (cond > 0)
			right = mid - 1;
	}
	return -1;
}

#define BUFMAX 100

char buf[BUFMAX];
int bufp = 0;

int getch(){
	return (bufp == 0)? getchar(): buf[--bufp];
}

void ungetch(int c){
	if(bufp >= BUFMAX)	{printf("buffer overflow\n"); return;}
	buf[bufp++] = c;
}

int getword(char *word, int lim)
{
    int c, c1;
    char *w = word;
    while (isspace(c = getch()))
        ;
    if (c != EOF)
        *w++ = c;
    else    
        return EOF;
   // handle comments: /* */ 
    if ( c == '/') {
        if ((c1 = getch()) == '*') {
            int ok = 1;
            while (ok) {
                // skip characters in comment lines
                while ((c = getch()) != EOF && c != '*')
                    ;
                if (c == EOF)
                    return EOF;
                if ((c = getch()) == '/')
                    ok = 0;
            }
            return 1;  //returned 1 for comment
        }
         // handle comments : //
        else if (c1 == '/') {
            while ((c = getch()) != EOF && c != '\n')
                ;
            if (c == EOF)
                return EOF;
            return 1;   //returned 1 for comment
        }
        else
            return c;
    }
    // handle preprocessor control lines, start with '#'
    if (c == '#') {
        while ((c = getch()) != EOF && c != '\n')
            ;
        if (c == EOF)
            return EOF;
        return '#';
    }
    // handle string constants, " "
    else if (c == '\"') {
        while ((c1 = getch()) != EOF && c1 != '\"')
            ;
        if (c1 == EOF)
            return EOF;
        return 2;   //returned 2 for constant
    }
    else if (c != '_' && !isalpha(c)) {
        while ((c = getch()) != EOF && !isspace(c))
            ;
        if (c == EOF)
            return EOF;
        return c;	//return not if c is number
    }
    // c is '_' or letter , scan characters until EOF or space, or punctuation
    // to get a complete word
    for ( ; --lim > 0; w++)
        if ((*w = getch()) == EOF || isspace(*w) || ispunct(*w)) {
            ungetch(*w);
            break;
        }
    *w = '\0';
    return word[0]; 
}
