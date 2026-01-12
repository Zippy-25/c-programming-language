#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100
#define HASHSIZE 101
#define BUFSIZE 100

struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
};

static struct nlist *hashtab[HASHSIZE]; /* pointer table */

/* function prototypes */
void error(int, char *);
int getch(void);
void ungetch(int);
int getword(char *, int);
void getdef(void);
void undef(char *);
void ungets(char *);
struct nlist *lookup(char *);
struct nlist *install(char *, char *);
void skipspace(void);
unsigned hash(char *);

int main(void)
{
    char word[MAXWORD];
    struct nlist *np;

    while (getword(word, MAXWORD) != EOF) {
        if (strcmp(word, "#") == 0)
            getdef();
        else if (!isalpha(word[0]))
            printf("%s", word);
        else if ((np = lookup(word)) == NULL)
            printf("%s", word);
        else
            ungets(np->defn);
    }
    return 0;
}

unsigned hash(char *s)
{
    unsigned hashval = 0;
    while (*s)
        hashval = *s++ + 31 * hashval;
    return hashval % HASHSIZE;
}

struct nlist *lookup(char *s)
{
    struct nlist *np;
    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;
    return NULL;
}

struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) {
        np = (struct nlist *)malloc(sizeof(*np));
        if (np == NULL)
            return NULL;
        np->name = strdup(name);
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else {
        free(np->defn);
    }

    np->defn = strdup(defn);
    return np;
}

void undef(char *name)
{
    struct nlist *np, *prev = NULL;
    unsigned hashval = hash(name);

    for (np = hashtab[hashval]; np != NULL; prev = np, np = np->next) {
        if (strcmp(name, np->name) == 0) {
            if (prev == NULL)
                hashtab[hashval] = np->next;
            else
                prev->next = np->next;

            free(np->name);
            free(np->defn);
            free(np);
            return;
        }
    }
}

void getdef(void)
{
    int i;
    char def[MAXWORD], dir[MAXWORD], name[MAXWORD];

    skipspace();
    getword(dir, MAXWORD);

    if (strcmp(dir, "define") == 0) {
        skipspace();
        getword(name, MAXWORD);

        skipspace();
        for (i = 0; i < MAXWORD - 1; i++) {
            if ((def[i] = getch()) == EOF || def[i] == '\n')
                break;
        }
        def[i] = '\0';
        install(name, def);
    }
    else if (strcmp(dir, "undef") == 0) {
        skipspace();
        getword(name, MAXWORD);
        undef(name);
    }
}

void error(int c, char *s)
{
    printf("Error: %s\n", s);
    while (c != EOF && c != '\n')
        c = getch();
}

void skipspace(void)
{
    int c;
    while ((c = getch()) == ' ' || c == '\t')
        ;
    ungetch(c);
}

void ungets(char *s)
{
    int len = strlen(s);
    while (len > 0)
        ungetch(s[--len]);
}

static char buf[BUFSIZE];
static int bufp = 0;

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp < BUFSIZE)
        buf[bufp++] = c;
}

int getword(char *word, int lim)
{
    int c;
    char *w = word;

    while (isspace(c = getch()))
        ;

    if (c != EOF)
        *w++ = c;

    if (!isalpha(c) && c != '_') {
        *w = '\0';
        return c;
    }

    for (; --lim > 0; w++) {
        if (!isalnum(*w = getch()) && *w != '_') {
            ungetch(*w);
            break;
        }
    }

    *w = '\0';
    return word[0];
}

