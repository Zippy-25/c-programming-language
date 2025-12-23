/*Extend atof to handle scientific notation of the form
123.45e-6
where a floating-point number may be followed by e or E and an optionally signed exponent.*/

#include <ctype.h>
#include <stdio.h>

#define MAXLINE 100

int power(int base, int exp) {
    int power;
    power = 1;
    while (exp-- > 0)
        power *= base;

    return power;
}

double atof(char s[]) {
    double val, pow;
    int sign, i, esign, exp;
    int power(int base, int exp);

    for (i = 0; isspace(s[i]); i++);

    sign = (s[i] == '-') ? -1 : 1;

    if (s[i] == '+' || s[i] == '-')
        i++;

    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');

    if (s[i] == '.')
        i++;

    for (pow = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        pow *= 10.0;
    }

    if (s[i] == 'e' || s[i] == 'E')
        i++;
    if (s[i] == '+' || s[i] == '-') {
        esign = s[i];
        i++;
    }

    for (exp = 0; isdigit(s[i]); i++)
        exp = 10.0 * exp + (s[i] - '0');

    if (esign == '-')
        return sign * (val / pow) / power(10, exp);
    else

        return sign * (val / pow) * power(10, exp);
}

int get_line(char line[], int lim) {
    int i, c;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        line[i] = c;

    if (c == '\n')
        line[i++] = c;

    line[i] = '\0';
}

int main(void) {
    char str[MAXLINE];
    double num;
    get_line(str, MAXLINE);

    num = atof(str);
    printf("%f", num);

    return 0;
}
