/*Exercise 6-4. Write a program that prints the distinct words in its input sorted into decreasing
order of frequency of occurrence. Precede each word by its count.*/


#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100

struct tnode {  //the tree node
    char *word; //points to text
    int count; //number of occurrences
    struct tnode *left; //left child
    struct tnode *right; //right child
};
struct words {
    char *words;
    int counts;
};


struct tnode *addtree(struct tnode *, char *);
int getword(char *, int);
void sort(struct words *); //sort array
int countword;
int i = 0;


/* word frequency count */
int main()
{
    struct tnode *root;
    char word[MAXWORD];
    
    root = NULL;
    while(getword(word, MAXWORD) != EOF)
        if(isalpha(word[0]))
            root = addtree(root, word);
    struct words sortword[countword];
    void fillarray(struct tnode *, struct words *); //fill an array 
    fillarray(root, sortword);
    sort(sortword); 
    int j;
    for(j = 0; j < countword; j++)
        printf("%4d %s\n", sortword[j].counts, sortword[j].words);
    return 0;
}

/* fillarray: fill an array of structures */
void fillarray(struct tnode *p, struct words sortword[])
{
    if(p != NULL)
    {
        fillarray(p->left, sortword);
        sortword[i++] = (struct words) {p->word, p->count};
        fillarray(p->right, sortword);
    }
}

/* sort: sort an array by inserting */
void sort(struct words sortword[])
{
    struct words temp;
    int i, j;
    for(i = 1; i<countword; i++)
    {
        temp = sortword[i];
        for(j = i-1; j >=0 && sortword[j].counts > temp.counts; j--)
        {
            sortword[j+1] = sortword[j];
            sortword[j] = temp;
        }
    }
}

struct tnode *talloc(void);
char *s_dup(char *s);

/* adtree: add a node with w, at or below p */ 
struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;
    
    if(p == NULL) //a new word has arrived
    {
        p = talloc(); //make a new node
        p->word = s_dup(w);
        countword++; //count words
        p->count = 1;
        p->left = p->right = NULL;
    }
    else if((cond = strcmp(w, p->word)) == 0)
        p->count++; //repeated word
    else if(cond < 0) //less than into left subtree
    {
        p->left = addtree(p->left, w);
    }
    else  //greater than into right subtree
    {
        p->right = addtree(p->right, w);
    }
    return p;
}

/* talloc: make a tnode */
struct tnode *talloc(void)
{
    return(struct tnode *) malloc(sizeof(struct tnode));
}

/* make a duplicate of s */
char *s_dup(char *s)
{
    char *p;
    
    p = (char *)malloc(strlen(s)+1); // +1 for '\0'
    if(p != NULL)
        strcpy(p, s);
    return p;
}

#define BUFSIZE 100

char buf[BUFSIZE];          //buffer for ungetch;
int bufp = 0;               //next free position in buf

int getch(void) // get a (possibly pushed-back) character  
{
   return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) // push character back on input
{
    if(bufp >= BUFSIZE)
        printf("ungetch: too many characnters\n");
    else
        buf[bufp++] = c;
}

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
    int c, d; 
    int getch(void);
    void ungetch(int);
    int in_comment(void);
    char *w = word;
    
    while(isspace(c = getch()))
        ;
    if(c != EOF)
        *w++ = c;
    else return EOF;
    
    if(isalpha(c) || c == '#')
    {
        for(;--lim > 0; w++)
            if(!isalnum(*w= getch()) && *w != '_')
            {
                ungetch(*w);
                break;
            }
    }
    else if(c=='\'' || c == '"')
    {
        for(; --lim > 0; w++)
            if((*w = getch()) == '\\')
                *++w = getch();
            else if(*w == c)
            {
                w++;
                break;
            }
            else if(*w == EOF)
                break;
    }
    else if(c == '/')
    {
        if(((d = getch()) == '*'))
            c = in_comment();
        else if(d == '/'){
        	while ((c = getch()) != '\n' && c != EOF);
        	if(c == EOF) return c;
        	else if(c == '\n') ungetch(c);
        }
        else 
            ungetch(d);
    }
    *w = '\0';
    return c;
}

/* comment */
int in_comment(void)
{
    int c;
    
    while((c = getch()) != EOF)
        if(c == '*')
        {
            if((c = getch()) == '/')
                break;
            else
                ungetch(c);
        }
    return c;
}
