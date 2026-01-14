/*Exercise 7-7. Modify the pattern finding program of Chapter 5 to take its input from a set of
named files or, if no files are named as arguments, from the standard input. Should the file
name be printed when a matching line is found?*/

#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int main(int argc, char *argv[])
{
    FILE *fp;
    char line[MAXLINE];
    int found = 0;
    int i;

    if (argc < 2) {
        printf("INVALID INPUT\n");
        return 1;
    }

    if (argc == 2) {
        while (fgets(line, MAXLINE, stdin) != NULL) {
            if (strstr(line, argv[1]) != NULL) {
                printf("MATCH FOUND: %s", line);
                found++;
            }
        }
    }
    else {
        for (i = 2; i < argc; i++) {
            fp = fopen(argv[i], "r");
            if (fp == NULL) {
                perror(argv[i]);
                continue;
            }

            while (fgets(line, MAXLINE, fp) != NULL) {
                if (strstr(line, argv[1]) != NULL) {
                    printf("%s: %s", argv[i], line);
                    found++;
                }
            }
            fclose(fp);
        }
    }

    if (found==0)
        printf("NO MATCH FOUND\n");
    return found;
}
