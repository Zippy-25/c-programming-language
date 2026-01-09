/*Exercise 6-2. Write a program that reads a C program and prints in alphabetical order each
group of variable names that are identical in the first 6 characters, but different somewhere
thereafter. Don't count words within strings and comments. Make 6 a parameter that can be
set from the command line.*/

#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

const char *keywords[] = {
    "auto","break","case","char","const","continue","default","do",
    "double","else","enum","extern","float","for","goto","if","int",
    "long","register","return","short","signed","sizeof","static",
    "struct","switch","typedef","union","unsigned","void","volatile","while"
};

#define MAXWORD 100
#define NKEYS (sizeof keywords / sizeof keywords[0])

struct tnode{
	char *word;
	struct wnode *list;
	int count;
	struct tnode* left;
	struct tnode*right;
};

struct tnode* addtree(struct tnode*, char *word); 
void printtree(struct tnode*);
int getword(char*, int lim);
struct tnode* talloc();
char* _strdup(char* word);
struct wnode *addword(struct wnode *head, char *word);
int iskeyword(const char *word);

int strn;

void main(int argc, char*argv[])
{	
	if (argc > 1)
	    strn = atoi(argv[1]);
	else
	    strn = 6;
	struct tnode* root;
	root = NULL;
	char word[MAXWORD];
	while(getword(word, MAXWORD) != EOF)
		if(isalpha(word[0]) || word[0] == '_')
			if (strlen(word)>strn && iskeyword(word) == 0)	root = addtree(root, word);
	
	printtree(root);
}

struct wnode {
    char *word;
    struct wnode *next;
};

struct tnode* addtree(struct tnode* p, char* word)
{
	char prefix[MAXWORD];
	strncpy(prefix, word, strn);
	prefix[strn] = '\0';

	int cond;
	
	if(p == NULL){
		p = talloc();
		p->left = NULL;
		p->right = NULL;
		p->count = 1;
		p->word = _strdup(prefix);
		p->list = addword(NULL, word);
	}
	else if((cond = strcmp(p->word, prefix)) > 0)
		p-> left = addtree(p->left, word);
	else if(strn && cond < 0)
		p->right = addtree(p->right, word);
	else if(strn){
		p->list = addword(p->list, word);
		p->count++;
	}
	return p;
}

struct wnode *addword(struct wnode *head, char *word) //new nodes are added to the front
{
    struct wnode *p;

    for (p = head; p != NULL; p = p->next)
        if (strcmp(p->word, word) == 0)
            return head;

    p = malloc(sizeof(*p));
    p->word = _strdup(word);
    p->next = head;
    return p;
}

void printtree(struct tnode* p)
{
	if(p!=NULL)
	{
			printtree(p->left);
			if(p->count > 1){
				printf("%s: ", p->word);
				for (struct wnode *w = p->list; w != NULL; w = w->next)
		        		printf("%s ", w->word);
		        	printf("\n");
                	}
			printtree(p->right);
	}
}

struct tnode* talloc()
{
	return (struct tnode*)(malloc(sizeof(struct tnode)));
}

char* _strdup(char* word)
{
	char *s = (char*)(malloc(strlen(word)+1));
	if(s!=NULL) 
		strcpy(s, word);
	return s;
}

int getword(char* word, int lim)
{
	int c, c1, getch(void);
	void ungetch(int c);
	char *w = word;
	
	for(c = getch(); c == ' '|| c == '\n' || c == '\t'; c = getch()) ;
	
	if(c != EOF)	*w++ = c;
	else return EOF;
	
	if(c == '/')
	{
		if((c1 = getch()) == '*'){
			int ok = 1;
			while(ok){
				while((c = getch()) != EOF && c!='*');
			if(c == EOF)	return EOF;
			if((c = getch()) == '/')	ok = 0;
			else ungetch(c);
		}
		return word[0]; 
		}
		else if(c1 == '/'){
			while((c = getch()) != EOF && c!= '\n');
			if(c == EOF)	return EOF;
			return word[0];
		}
	}
	else if(c == '\"')
	{
		while((c = getch()) != EOF && c!= '\"');
		if(c == EOF)	return EOF;
		return word[0];
	}	
	else if (c != '_' && !isalpha(c)) {
        	while ((c = getch()) != EOF && !isspace(c));
                    if (c == EOF)
            		return EOF;
       		return c; //returns if c is a number or any other continuous non alphabets
	}
	
	for(;--lim;w++)
		if(!isalnum(*w = getch()) && *w!= '_'){
			ungetch(*w);
			break;
		}
	*w = '\0';
	return word[0];
}

#define BUFSIZE 100
char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp < BUFSIZE)
        buf[bufp++] = c;
}

int iskeyword(const char *word)
{
    int low = 0, high = NKEYS - 1, mid;

    while (low <= high) {
        mid = (low + high) / 2;
        int cmp = strcmp(word, keywords[mid]);
        if (cmp < 0)
            high = mid - 1;
        else if (cmp > 0)
            low = mid + 1;
        else
            return 1;   
    }
    return 0;           
}
