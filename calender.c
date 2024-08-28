#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

#define SPACE 32
#define HL 196
#define VL 179
#define TT 194
#define LST 195
#define RST 180
#define BT 193
#define LT 218
#define RT 191
#define LB 192
#define RB 217
#define CROSS 197
#define BS 8
#define TOTCOLS 80
#define TOTROWS 25
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define WIDTH 5
#define DIM 7
void gotoxy(int x, int y)
{
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
int isLeap(int yr)
{
    return ( ( (yr%4==0) && (yr%100!=0) ) || (yr%400==0) ) ? TRUE : FALSE;
}
void colHeadings(void)
{
    int row;
    int col;
    char * dayNames[ ] = {"SUN","MON","TUE","WED","THU","FRI","SAT"};
    col = (TOTCOLS - ( (WIDTH * DIM ) + (DIM + 1)) )/ 2;
    row = ( TOTROWS - (DIM + (DIM + 1)) ) /2;
    row+=1;
    col += 2;
    int ctr;
    for( ctr = 0; ctr < DIM; ctr +=1)
    {
     gotoxy(col + (ctr * (WIDTH+1)) , row);
     printf("%s",dayNames[ ctr ]);
    }
}
int DayOfWeek( int y, int m, int d ) /* returns Day of Week:
0 = Sunday, 1= Monday...
*/
{
static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
y -= m < 3;
return (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
} /*--DayOfWeek( )--------*/
void calendar(  int month, int year)
{
    int days_in_month [] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    char *monthName [] = {"","January","February","March","April",\
    "May","June","July","August","September","October","November","December"};
    int row;
    int col;
    col = (TOTCOLS - ( (WIDTH * DIM ) + (DIM + 1)) )/ 2;
    row = ( TOTROWS - (DIM + (DIM + 1)) ) /2;
    row += 3;
    col += 3;
    int ctr;
    int day;
    gotoxy(30,3);
    printf("%10s, %d", monthName[ month ], year);
    cleaner();
    if ( isLeap(year) == TRUE)
    {
        days_in_month [2 ] = 29;
    }
    else
        days_in_month [ 2 ] = 28;
    for ( day = 1, ctr = DayOfWeek(year,month, 1); day <= days_in_month[month]; day +=1)
    {
     gotoxy(col + (ctr * (WIDTH+1)) , row);
     printf("%02d",day);
     ctr+=1;
     if ( ctr == DIM)
     {
         row+=2;
         ctr =0;
     }
    }
}
void cleaner(  )
{
    int row;
    int col;
    col = (TOTCOLS - ( (WIDTH * DIM ) + (DIM + 1)) )/ 2;
    row = ( TOTROWS - (DIM + (DIM + 1)) ) /2;
    row += 3;
    col += 3;
    int ctr;
    int week;
    for (week = 0; week < 6; week += 1)
    {
    for(ctr = 0; ctr < DIM; ctr += 1)
    {
     gotoxy(col + (ctr * (WIDTH+1)) , row);
     printf("  ");
    }
    }
}

void drawDabba(void )
{
        int row;
    int col;
    int ctr1;
    int ctr2;
    int ctr3;
    int ctr4;
    col = (TOTCOLS - ( (WIDTH * DIM ) + (DIM + 1)) )/ 2;
    row = ( TOTROWS - (DIM + (DIM + 1)) ) /2;
    gotoxy ( col, row);
    printf("%c", LT);
    for( ctr2=0; ctr2 <  DIM; ctr2 += 1)
    {
    for( ctr1 = 0; ctr1 < WIDTH; ctr1+=1)
    {
    printf("%c", HL);

    }
    printf("%c", TT);

    }
    printf("%c%c", BS, RT);
    // first line ends here
    for( ctr3 = 0; ctr3 < DIM ; ctr3 += 1)
    {
    row+=1;
    gotoxy(col, row);
    for( ctr2 = 0;ctr2 <= DIM; ctr2 += 1)
    {
    printf("%c", VL);
    for( ctr1 = 0; ctr1 < WIDTH; ctr1+=1)
    {
    printf("%c", SPACE);
    }
    }
    row+=1;
    gotoxy(col, row);
    printf("%c", LST);
    for( ctr2 = 0; ctr2 < DIM; ctr2 +=1)
    {
    for( ctr1 = 0; ctr1 < WIDTH; ctr1+=1)
    {
    printf("%c", HL);

    }
    printf("%c", CROSS);
    }
    printf("%c%c", BS, RST);
    }
    gotoxy(col, row);
    printf("%c", LB);
    for( ctr2=0; ctr2 <  DIM; ctr2 += 1)
    {
    for( ctr1 = 0; ctr1 < WIDTH; ctr1+=1)
    {
    printf("%c", HL);

    }
    printf("%c", BT);

    }
    printf("%c%c", BS, RB);


}
int main()
{
    int month;
    int year;
    int key;
    month = 2;
    year = 2005;
    drawDabba();
    colHeadings();

    do
    {
    calendar(month , year);
    key = getch();
    if ( key != 27)
    key = getch();
    switch ( key )
    {
        case LEFT : month-=1; break;
        case RIGHT : month += 1; break;
        case DOWN : year -=1; break;
        case UP : year +=1;
    }
    if ( month == 0)
    {
        year -= 1;
        month = 12;
    } else if (month > 12)
    {
        year += 1;
        month = 1;
    }


    }while( key != 27);
    getch();

    return EXIT_SUCCESS;
}
