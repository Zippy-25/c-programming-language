/*Write a program to compare two files, printing the first line where they differ.*/

#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int main(int argc, char *argv[])
{
    FILE *fp1, *fp2;
    char line1[MAXLINE], line2[MAXLINE];
    int lineno = 1;

    if (argc != 3) {
        printf("INVALID INPUT");
        return 1;
    }

    fp1 = fopen(argv[1], "r");
    fp2 = fopen(argv[2], "r");

    if (fp1 == NULL || fp2 == NULL) {
        perror("File open error");
        return 1;
    }

    while (fgets(line1, MAXLINE, fp1) != NULL &&
           fgets(line2, MAXLINE, fp2) != NULL) {

        if (strcmp(line1, line2) != 0) {
            printf("Files differ at line %d\n", lineno);
            printf("File1: %s", line1);
            printf("File2: %s", line2);
            fclose(fp1);
            fclose(fp2);
            return 0;
        }
        lineno++;
    }

    if (fgets(line1, MAXLINE, fp1) != NULL ||
        fgets(line2, MAXLINE, fp2) != NULL) {

        printf("Files differ at line %d\n", lineno);
        printf("One file ended before the other\n");
    } else {
        printf("Files are identical\n");
    }

    fclose(fp1);
    fclose(fp2);
    return 0;
}
