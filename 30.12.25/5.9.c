/*Exercise 5-9. Rewrite the routines day_of_year and month_day with pointers instead of
indexing.*/

#include<stdio.h>

static char daytab[2][12] =
{ {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}, 
  {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
}; 

int day_of_year(int year, int month, int day)
{
	int i, leap;
	leap = (year%4 == 0)&&(year%100 != 0)||(year%400 == 0);
	
	if(year<1 || month<1 || month>12 || day<1 || day>daytab[leap][month])	return -1;
	
	char *p = daytab[leap];	
	while(month--)
		day += *p++;
	return day;
}
void month_day(int year, int yrday, int *month, int* day)
{
	int i, leap;
	*month = 0;
	
	leap = (year%4 == 0)&&(year%100 != 0)||(year%400 == 0);
	
	if(yrday<1 || yrday>(leap? 366:365) || year<1){
		*month = -1;
		*day = -1;
		return;
	}
	
	char* p = daytab[leap];
	while(yrday > *p){
		yrday-=*p++;
		(*month)++;
	}
	*day = yrday;
}

void main()
{
	int yrday, month, day;
	
	yrday = day_of_year(1988, 2, 29);
	printf("yearday of 29th Feb 1988: %d\n", yrday);
	
	month_day(1988, yrday, &month, &day);
	printf("Actual date of %dth day %d is %d.%d\n", yrday, 1988, day, month);
}
