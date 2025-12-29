/*Write versions of the library functions strncpy, strncat, and strncmp, which
operate on at most the first n characters of their argument strings. For example,
strncpy(s,t,n) copies at most n characters of t to s.*/

#include<stdio.h>
#include<stdlib.h>

void _strncpy(char *s, char *t, int n)
{
	while(n-- && (*s++ = *t++));
	*s = '\0';
}

int _strncmp(char *s, char *t, int n)
{
	for ( ; --n && *s == *t; s++, t++)
		if (*s == '\0')	return 0;
	return *s - *t;
}

void _strncat(char *s, char *t, char *d, int n)
{
	while(*s)	*d++ = *s++;
	
	while(n-- && (*d++ = *t++));
	*d = '\0';
}

int _strlen(char *s)
{
	char *p = s;
	while (*p != '\0')
	p++;
	return p - s;
}

void main()
{
    char dest[] = "ABCDEF";
    char source[] = "GHIJKLMN";

    _strncpy(dest, source, 4);
    printf("%s\n", dest);

    char s1[] = "ABCD";
    char t1[] = "EFGHIJ";
    char *d;


    if ((d = (char *) malloc(sizeof(char) * (_strlen(s1) + 4 + 1))) == NULL)
        printf("unable to allocate memory \n");

    _strncat(s1, t1, d, 4);
    printf("%s\n", d); 

    free(d);

    char s2[] = "ABCDEF";
    char t2[] = "ABC";

    printf("%d\n", _strncmp(s2, t2, 3));

	
}
