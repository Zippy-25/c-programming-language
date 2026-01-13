/*Exercise 7-2. Write a program that will print arbitrary input in a sensible way. As a
minimum, it should print non-graphic characters in octal or hexadecimal according to local
custom, and break long text lines.*/

#include<stdio.h>
#include<ctype.h>
#define MAXLINE 100 
#define OCTLEN 6 

/* print arbitrary input in a sensible way */
int main()
{
    int c, pos;
   
    pos = 0; //position in string    
    while((c = getchar()) != EOF)
        if(iscntrl(c) || isspace(c))
        {
            if(pos + OCTLEN < MAXLINE)
                pos = pos + OCTLEN;
            else
            {
                putchar('\n');
                pos = OCTLEN;
            }
            printf(" \\%03o ", c);
            if(c == '\n')
            {
                pos = 0;
                putchar('\n');
            }
        }
        else
        {
            if(pos + 1 < MAXLINE)
                pos = pos + 1;
            else
            {
                putchar('\n');
                pos = 1;
            }
            putchar(c);
        }
    return 0; }
