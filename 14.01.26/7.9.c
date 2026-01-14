/*Exercise 7-9. Functions like isupper can be implemented to save space or to save time.
Explore both possibilities.*/

#include<stdio.h>

int isupper_space(int c)
{
    return (c >= 'A' && c <= 'Z');
}

int isupper_time(int c) {
    return (strchr("ABCDEFGHIJKLMNOPQRSTUVWXYZ", c) != NULL);
}

int main(){
    printf("%d\n",isupper_time('Z'));
    return 0;
}
