/*Exercise 1-22. Write a program to "fold" long input lines into two or more shorter lines after
the last non-blank character that occurs before the n-th column of input. Make sure your
program does something intelligent with very long lines, and if there are no blanks or tabs
before the specified column.*/

#include <stdio.h>

#define MAXLINE 1000
#define FOLD_COL 10

int my_getline(char s[], int lim)
{
    int c, i = 0;

    while (i < lim - 1 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;

    if (c == '\n')
        s[i++] = c;

    s[i] = '\0';
    return i;
}

void fold(char s[])
{
    int col = 0;          
    int last_blank = -1; 
    int i = 0;
    int start = 0;       

    while (s[i] != '\0') {

        if (s[i] == ' ' || s[i] == '\t')
            last_blank = i;

        col++;

        if (col > FOLD_COL) {
            if (last_blank >= start) {
                int j;
                for (j = start; j < last_blank; j++)
                    putchar(s[j]);
                putchar('\n');
                start = last_blank + 1;
                i = start;
            } else {
                int j;
                for (j = start; j < i; j++)
                    putchar(s[j]);
                putchar('\n');
                start = i;
            }
            col = 0;
            last_blank = -1;
            continue;
        }

        i++;
    }

    for (i = start; s[i] != '\0'; i++)
        putchar(s[i]);
}

int main(void)
{
    char line[MAXLINE];

    while (my_getline(line, MAXLINE) > 0)
        fold(line);

    return 0;
}
