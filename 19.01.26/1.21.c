/*1.21.Write a program entab that replaces strings of blanks by the minimum
number of tabs and blanks to achieve the same spacing. Use the same tab stops as for detab.
When either a tab or a single blank would suffice to reach a tab stop, which should be given
preference?*/

#include <stdio.h>

#define MAX 1000
#define n 8


int my_getline(char line[], int limit)
{
    int c, i = 0;

    while ((c = getchar()) != EOF && c != '\n') {
        if (i < limit - 1)
            line[i] = c;
        i++;
    }

    if (c == '\n') {
        if (i < limit - 1)
            line[i] = c;
        i++;
    }

    line[i] = '\0';
    return i;
}

void entab(char line[])
{
    int i = 0;
    int col = 0;         
    int space_count = 0; 

    while (line[i] != '\0') {

        if (line[i] == ' ') {
            space_count++;
            col++;
        }
        else {
            while (space_count > 0) {

                int spaces_to_tab = n - (col - space_count) % n;

                if (space_count >= spaces_to_tab && spaces_to_tab > 1) {
                    putchar('\t');
                    space_count -= spaces_to_tab;
                } else {
                    putchar(' ');
                    space_count--;
                }
            }

            putchar(line[i]);
            col++;

        }

        i++;
    }
}

int main()
{
    char line[MAX];

    while (my_getline(line, MAX) > 0) {
        entab(line);
    }

    return 0;
}
