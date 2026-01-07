#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define NUMERIC  1
#define DECR    2
#define FOLD    4
#define MDIR    8
#define LINES    100
#define MAXLEN    1000
#define MAXSTR    100
#define ALLOCSIZE 10000

int charcmp(char *, char *);
void error(char *);
int numcmp(char *, char *);
void readargs(int argc, char *argv[]);
int readlines(char *lineptr[], int maxlines);
void myqsort(void *v[], int left, int right, int (*comp)(void *, void *));
void writelines(char *lineptr[], int nlines, int order);
void substr(char *s, char *str, int maxstr);
int mgetline(char *, int);
char *alloc(int);
void afree(char *p);

int option = 0;
int pos1 = 0;
int pos2 = 0;

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

int main(int argc, char *argv[]) {
    char *lineptr[LINES];
    int nlines;
    int rc = 0;

    readargs(argc, argv);

    if ((nlines = readlines(lineptr, LINES)) > 0) {
        if (option & NUMERIC)
            myqsort((void **) lineptr, 0, nlines - 1,
                    (int (*)(void *, void *)) numcmp);
        else
            myqsort((void **) lineptr, 0, nlines - 1,
                    (int (*)(void *, void *)) charcmp);

        writelines(lineptr, nlines, option & DECR);
    } else {
        printf("input too big to sort \n");
        rc = -1;
    }

    return rc;
}

void readargs(int argc, char *argv[]) {
    int c;

    while (--argc > 0 && (c = (*++argv)[0]) == '-' || c == '+') {
        if (c == '-' && !isdigit(*(argv[0] + 1)))
            while ((c = *++argv[0]) != '\0')
                switch (c) {
                    case 'd':
                        option |= MDIR;
                        break;
                    case 'f':
                        option |= FOLD;
                        break;
                    case 'n':
                        option |= NUMERIC;
                        break;
                    case 'r':
                        option |= DECR;
                        break;
                    default:
                        printf("sort: illegal option %c \n", c);
                        error("Usage: sort -dfnr [+pos1] [-pos2]");
                        break;
                }
        else if (c == '-')
            pos2 = atoi(argv[0] + 1);
        else if ((pos1 = atoi(argv[0] + 1)) < 0)
            error("Usage: sort -dfnr [+pos1][-pos2]");
    }

    if (argc || pos1 > pos2)
        error("Usage: sort -dfnr [+pos1] [-pos2]");
}

int numcmp(char *s1, char *s2) {
    double v1, v2;
    char str[MAXSTR];

    substr(s1, str, MAXSTR);
    v1 = atof(str);

    substr(s2, str, MAXSTR);
    v2 = atof(str);

    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

int charcmp(char *s, char *t) {
    char a = '\0', b = '\0';
    int i, j, endpos;
    int fold = (option & FOLD) ? 1 : 0;
    int dir = (option & MDIR) ? 1 : 0;

    i = j = pos1;

    if (pos2 > 0)
        endpos = pos2;
    else if ((endpos = strlen(s)) > strlen(t))
        endpos = strlen(t);
    else
        endpos = strlen(s);

    do {
        if (dir) {
            while (i < endpos && !isalnum(s[i]) && s[i] != ' ' && s[i] != '\0')
                i++;
            while (j < endpos && !isalnum(t[j]) && t[j] != ' ' && t[j] != '\0')
                j++;
        }
        if (i < endpos && j < endpos) {
            a = fold ? tolower(s[i]) : s[i];
            i++;
            b = fold ? tolower(t[j]) : t[j];
            j++;

            if (a == b && a == '\0')
                return 0;
        }
    } while (a == b && i < endpos && j < endpos);

    return a - b;
}

void substr(char *s, char *str, int maxstr) {
    int i, j, len;

    len = strlen(s);

    if (pos2 > 0 && len > pos2)
        len = pos2;
    else if (pos2 > 0 && len < pos2)
        error("substr: string too short");

    for (j = 0, i = pos1; i < len && j < maxstr - 1; i++, j++)
        str[j] = s[i];
    str[j] = '\0';
}

void error(char *s) {
    printf("%s \n", s);
    exit(1);
}

void swap(void *v[], int i, int j) {
    void *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

void myqsort(void *v[], int left, int right, int (*comp)(void *, void *)) {
    int i, last;

    if (left >= right)
        return;

    swap(v, left, (left + right) / 2);
    last = left;

    for (i = left + 1; i <= right; i++)
        if ((*comp)(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);

    myqsort(v, left, last - 1, comp);
    myqsort(v, last + 1, right, comp);
}

int readlines(char *lineptr[], int maxlines) {
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = mgetline(line, MAXLEN)) > 0)
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else {
            line[len - 1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    return nlines;
}

void writelines(char *lineptr[], int nlines, int order) {
    int i;

    if (order) {
        for (i = nlines - 1; i >= 0; i--)
            printf("%s\n", lineptr[i]);
    } else {
        for (i = 0; i < nlines; i++)
            printf("%s\n", lineptr[i]);
    }
}

char *alloc(int n) {
    if (allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        return allocp - n;
    } else
        return 0;
}

void afree(char *p) {
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
        allocp = p;
}

int mgetline(char s[], int lim) {
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }

    s[i] = '\0';
    return i;
}
