/*Exercise 4-11. Modify getop so that it doesn't need to use ungetch. Hint: use an internal
static variable.*/


#include<stdio.h>
#include<ctype.h>
#include<math.h>
#include<string.h>

#define MAXVAL 100
#define MAXOP 100
#define NUMBER '0'
#define STRING '1'
#define VARIABLES 26

int getop(char s[]);

int getch(void);
int static last = 0;

double _atof(char s[]);

void push(double);
double pop(void);
void print_top(void);
void duplicate_top(void);
void swap_stack(void);
void clear_stack(void);

void string_call(char s[]);

double val[MAXVAL];
int sp = 0;

void main()
{
	int i, type, var;
	char s[MAXOP];
	double op2, variable[VARIABLES], last;
	
	for(i = 0; i < VARIABLES; i++)	variable[i] = 0.0;
	last = 0.0;
	
	while((type = getop(s)) != EOF)
	{
		switch(type){
			case NUMBER:
				push(_atof(s));
				break;
			case STRING:
				string_call(s);
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
			case '=':
				pop();
				if(var >= 'A' && var<= 'Z')	variable[var - 'A'] = pop();
				else	printf("incorrect variable name\n");
				break;
			case 't':
				print_top();
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
				if(sp > 0) printf("\t%.8g\n", (last = pop()));
				break;
			default:
				if(type >= 'A' && type <= 'Z')	push(variable[type - 'A']);
				else  printf("Not supported type %s\n", s);
				break;
		}
		var = type;
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

void print_top(void)
{
	if(sp > 0) printf("\t%.8g\n", val[sp-1]);
	else printf("No elements in stack\n");
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
	
	i = 0;
	s[1] = '\0';
	
	if(!isalpha(c) && !isdigit(c) && c != '.' && c!= '-') return c;
	
	if(isalpha(c)){
		while(isalpha(s[++i] = c = getch()));
		s[i] = '\0';
		if(c != EOF)
			last = c;
		if(strlen(s) > 1) return STRING;	
		return s[0];
	}
	
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
			last = c;
			return '-';
		}
		
		else{
			s[i] = '\0';
			if(c != EOF)
				last = c;
			return NUMBER;
		}	
	}
	
	if(isdigit(c))
		while(isdigit(s[++i] = c = getch()));
	
	if(c == '.')
		while(isdigit(s[++i] = c = getch()));
	
	s[i] = '\0';
	
	if(c != EOF)
		last = c;
	return NUMBER;
}

int getch(void)
{
	int temp;
	temp = last;
	if(!last)	return getchar();
	
	last = 0;
	return temp;
}

void string_call(char s[])
{
	if(strcmp(s, "sin") == 0)	push(sin(pop()));
	else if(strcmp(s, "cos") == 0)	push(cos(pop()));
	else if(strcmp(s, "exp") == 0)	push(exp(pop()));
	else if(strcmp(s, "pow") == 0){
	double op3 =  pop();
	push(pow(pop(), op3));
	}
	else
		printf("Operation %s not supported\n", s);
}
