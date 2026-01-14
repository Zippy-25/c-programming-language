/*Exercise 7-8. Write a program to print a set of files, starting each new one on a new page,
with a title and a running page count for each file.*/

#include <stdio.h>

#define MAXLINE 1000
#define PAGELEN 5  

int main(int argc, char *argv[])
{
    FILE *fp;
    char line[MAXLINE];
    int page, linecount;
    int i;

    if (argc < 2) {
        printf("INSUFFICIENT NUMBER OF FILES\n");
        return 1;
    }

    for (i = 1; i < argc; i++) {
        fp = fopen(argv[i], "r");
        if (fp == NULL) {
            perror(argv[i]);
            continue;
        }

        page = 1;
        linecount = 0;

        printf("\n--- %s --- Page %d ---\n\n", argv[i], page);

        while (fgets(line, MAXLINE, fp) != NULL) {
            if (linecount == PAGELEN) {
                page++;
                linecount = 0;
                printf("\n--- %s --- Page %d ---\n\n", argv[i], page);
            }
            fputs(line, stdout);
            linecount++;
        }

        fclose(fp);
    }

    return 0;
}
