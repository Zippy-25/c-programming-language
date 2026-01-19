/*Write a program to remove all comments from a C program. Don't forget to
handle quoted strings and character constants properly. C comments don't nest.*/

#include <stdio.h>

#define MAX 10000

int main()
{
    int c, next;
    int comment = 0;

    char output[MAX];
    int i = 0;

    while ((c = getchar()) != EOF) {

        if (comment) {
            if (c == '\n') {
                comment = 0;
                output[i++] = c;   
            }
            continue;
        }

        if (c == '/') {
            next = getchar();

            if (next == '/') {
                comment = 1;
            } else {
                output[i++] = c;
                if (next != EOF)
                    output[i++] = next;
            }
        } else {
            output[i++] = c;
        }
    }

    output[i] = '\0';   

    printf("\n\nTHE CODE WIHTOUT SINGLE LINE COMMENTS:\n%s\n\n", output);

    return 0;
}
