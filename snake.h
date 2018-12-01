#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#define HD 20
#define TD 40
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
int ef = 5;
int point = 35;
struct snake
{
	int x, y;
	struct snake *next;
};
struct food
{
	int x, y;
	int S;
	struct food *next;
};
struct Hero_List
{
	int point;
	char name[100];
	struct Hero_List *next;
};
