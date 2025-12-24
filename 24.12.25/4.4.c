/*Exercise 4-4. Add the commands to print the top elements of the stack without popping, to
duplicate it, and to swap the top two elements. Add a command to clear the stack.*/

#include<stdio.h>
#include<ctype.h>
#include<math.h>

#define MAXVAL 100
#define MAXOP 100
#define MAXBUF 100
#define NUMBER '0'

int getop(char s[]);

int getch(void);
void ungetch(int);

double _atof(char s[]);

void push(double);
double pop(void);
void duplicate_top(void);
void swap_stack(void);
void clear_stack(void);

double val[MAXVAL];
int sp = 0;
int bufp;
int buf[MAXBUF];

void main()
{
	int type;
	char s[MAXOP];
	double op2;
	
	while((type = getop(s)) != EOF)
	{
		switch(type){
			case NUMBER:
				push(_atof(s));
				break;
			case '+':
				push(pop() + pop());
				break;
			case '*':
				push(pop() * pop());
				break;
			case '-':
				op2 = pop();
				push(pop() - op2);
				break;
			case '/':
				op2 = pop();
				if(op2 != 0) push(pop() / op2);
				else printf("Error: zero divisor\n");
				break;
			case '%':
				op2 = pop();
				if(op2 != 0) push(fmod(pop() , op2));
				else printf("Error: zero divisor\n");
				break;
			case 't':
				if(sp > 0) printf("\t%.8g\n", val[sp-1]);
				else printf("No elements in stack\n");
				break;
			case 'd':
				duplicate_top();
				break;
			case 's':
				swap_stack();
				break;
			case 'c':
				clear_stack();
				break;
			case '\n':
				if(sp > 0) printf("\t%.8g\n", pop());
				break;
			default:
				printf("Not supported type %s\n", s);
				break;
		}
	}
}

double _atof(char s[])
{
	int c, i, sign; 
	i = 0; sign = 1;
	double val, pow;
	pow = 1.0;
	val = 0.0;
	
	while((c = s[i]) == ' ' || c == '\t') i++;
	
	if (s[i] == '-') sign = -1;
	if(s[i] == '-' || s[i] == '+') i++;
	
	while(isdigit(s[i])){
		val = val*10.0 + (s[i] - '0');
		i++;
	}
	
	if(s[i] == '.'){
		i++;
		while(isdigit(s[i])){
			val = val*10.0 + (s[i] - '0');
			pow*=10.0;
			i++;
		}
	}
	printf("inside atof: %g\n", (val * sign) / pow);
	return (val * sign) / pow;
}

void push(double f)
{
	if(sp < MAXVAL)	val[sp++] = f;
	else	printf("Stack overflow: can't push %g\n", f);
	printf("pushed content: %g\n", val[sp - 1]);
}

double pop(void)
{
	if(sp > 0) return val[--sp];
	else{	printf("stack underflow: can't pop\n");
	return 0.0;}
}

void duplicate_top(void)
{
	if(sp < MAXVAL && sp > 0) push(val[sp-1]);
	else	printf("Can't perfrom duplication operation\n");
}

void swap_stack(void)
{
	if(sp > 1){
		double op3;
		op3 = val[sp - 1];
		val[sp - 1] = val[sp - 2];
		val[sp - 2] = op3;
	}
	else printf("Can't perform swap\n");
}

void clear_stack(void)
{
	sp = 0;
}

int getop(char s[])
{
	int i, c, flag;
	i = flag = 0;
	while((s[0] = c = getch()) == ' ' || c == '\t') ;
	
	s[1] = '\0';
	
	if(!isdigit(c) && c != '.' && c!= '-')	return c;
	
	i = 0;
	
	
	if(c == '-')	
	{		
		if( isdigit(s[++i] = c = getch())){
			flag = 1;
			while(isdigit(s[++i] = c = getch()));
		}
		
		if(c == '.'){
			flag = 1;
			while(isdigit(s[++i] = c = getch()));
		}
		
		if(flag != 1){
			ungetch(c);
			return '-';
		}
		
		else{
			s[i] = '\0';
			if(c != EOF)
				ungetch(c);
			return NUMBER;
		}	
	}
	
	if(isdigit(c))
		while(isdigit(s[++i] = c = getch()));
	
	if(c == '.')
		while(isdigit(s[++i] = c = getch()));
	
	s[i] = '\0';
	
	if(c != EOF)
		ungetch(c);
	return NUMBER;
}

int getch(void)
{
	return (bufp > 0)? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	buf[bufp ++] = c;
}
