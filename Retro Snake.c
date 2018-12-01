#include "snake.h"
struct snake *M_D_Snake(struct snake *head0, struct food *head1,char ward);
int Food_Deter_n(struct snake *head0, struct food *head1, char ward);
void Food_Deter_f(struct food *head1, struct snake *head0);
void Print_map(struct snake *head0, struct food *head1);
int Death_Deter(struct snake *head0, char ward);
void Start_Game_m(struct snake *head0, struct food *head1);
char Con_snake(char a, char b);
struct snake *Start_Game_n();
struct food *Start_Game_f();
int Point_op(char a);
struct Hero_List *Insert_Linklist(struct Hero_List *p, struct Hero_List *head);
struct Hero_List *filePrint();
int main()
{
	int choice;
	to3:
	printf("1.开始游戏     ||2.难度选择\n");
	printf("3.排行榜       ||0.退出\n");
	scanf("%d", &choice);
	point = 0;
	system("cls");
	switch (choice)
	{
	case 1:
	{
		int cu = 0, Death_flag = 0;
		char ward = 'd', ch;
		struct snake *head_n;
		struct food *head_f;
		head_n = Start_Game_n();
		head_f = Start_Game_f();
		Start_Game_m(head_n, head_f);
		printf("\033[21;15H\033[43mpiont: %d\033[0m", point);
		do
		{
			to2:
			while (!_kbhit()) {
				Sleep(5);
				if (cu == (ef * 10))
				{
					if (Death_Deter(head_n, ward)) goto to3;
					head_n = M_D_Snake(head_n, head_f, ward);
					Food_Deter_f(head_f, head_n);
					cu = 0;
				}
				cu++;
			}
			ch = _getch();
			ward = Con_snake (ward, ch);
			goto to2;
		} while (1);
	}break;
	case 2:
	{
		to1:
		printf("1.S级 ||2.A级 ||3.B级 ||4.C级 ||5.D级\n");
		if (choice == 1) printf("当前等级S级\n");
		else printf("当前等级%c\n", ef + 63);
		scanf("%d", &choice);
		switch (choice)
		{
		case 1: ef = 1; break;
		case 2: ef = 2; break;
		case 3: ef = 3; break;
		case 4: ef = 4; break;
		case 5: ef = 5; break;
		default: 
		{
			printf("重新输入\n"); 
			goto to1;
		}break;
		}
		system("cls");
		goto to3;
	}
	}
}
struct snake *Start_Game_n()
{
	int i = 3;
	struct snake *head, *p, *ptr;
	head = NULL;
	do
	{
		ptr = (struct snake *)malloc(sizeof(struct snake));
		ptr->x = i--;
		ptr->y = 2;
		if (i == 2) 
		{
			head = ptr;
			p = head;
		}
		else
		{
			p->next = ptr;
			p = p->next;
		}
	} while (i >= 1);
	ptr->next = NULL;
	return head;
}
struct food *Start_Game_f()
{
	int i = 1;
	struct food *head, *p, *ptr;
	head = NULL;
	srand(time(NULL));
	do
	{
	to1:
		ptr = (struct food *)malloc(sizeof(struct food));
		ptr->x = rand() % ((TD - 2) / 2) + 1;
		ptr->y = rand() % (HD - 4) + 3;
		ptr->S = 1;
		if (i == 1)
		{
			head = ptr;
			p = head;
		}
		else
		{
			if (ptr->x == p->x && ptr->y == p->y)
			{
				goto to1;
			}
			p->next = ptr;
			p = p->next;
		}
		i++;
	} while (i <= (6 - ef));
	ptr->next = NULL;
	return head;
}
void Start_Game_m(struct snake *head0, struct food *head1)
{
	int i, j;
	for (i = 1; i <= HD; i++)
	{
		for (j = 1; j <= TD; j++)
		{
			if (j == 1 || j == TD || i == 1 || i == HD) printf("\033[47m \033[0m");
			else printf(" ");
		}
		printf("\n");
	}
	Print_map(head0, head1);
	struct food *ps;
	ps = head1;
	do
	{
		printf("\033[%d;%dH\033[45m \033[0m", ps->y + 1, 2 * ps->x + 1);
		printf("\033[%d;%dH\033[45m \033[0m", ps->y + 1, 2 * ps->x);
		ps = ps->next;
	} while (ps != NULL);
}
void Print_map(struct snake *head0, struct food *head1)
{
	struct snake *ps, *pf;
	int i, j;
	ps = head0;
	pf = head1;
	do
	{
		printf("\033[%d;%dH\033[41m \033[0m", ps->y + 1, 2 * ps->x + 1);
		printf("\033[%d;%dH\033[41m \033[0m", ps->y + 1, 2 * ps->x);
		ps = ps->next;
	} while (ps != NULL);
}
char Con_snake(char a, char b)
{
	if (b == '\0') return a;
	if (a != b)
	{
		if (a == 'w' && (b == 'a' || b == 'd')) return b;
		if (a == 's' && (b == 'a' || b == 'd')) return b;
		if (a == 'd' && (b == 'w' || b == 's')) return b;
		if (a == 'a' && (b == 'w' || b == 's')) return b;
	}
	return a;
}
struct snake *M_D_Snake(struct snake *head0, struct food *head1, char ward)
{
	struct snake *ptr, *ptr1, *head;
	if (Food_Deter_n(head0, head1, ward))
	{
		ptr = head0;
		ptr1 = ptr;
		ptr = ptr->next;
		do
		{
			if (ptr->next == NULL)
			{
				printf("\033[%d;%dH ", ptr->y + 1, 2 * ptr->x + 1);
				printf("\033[%d;%dH ", ptr->y + 1, 2 * ptr->x);
				free(ptr);
				ptr1->next = NULL;
				break;
			}
			ptr = ptr->next;
			ptr1 = ptr1->next;
		} while (1);
	}
	ptr1 = head0;
	ptr = (struct snake *)malloc(sizeof(struct snake));
	switch (ward)
	{
	case 'w': {ptr->y = (head0->y) - 1; ptr->x = head0->x; } break;
	case 's': {ptr->y = (head0->y) + 1; ptr->x = head0->x; } break;
	case 'd': {ptr->x = (head0->x) + 1; ptr->y = head0->y; } break;
	case 'a': {ptr->x = (head0->x) - 1; ptr->y = head0->y; } break;
	}
	ptr->next = head0;
	printf("\033[%d;%dH\033[41m \033[0m", ptr->y + 1, 2 * ptr->x + 1);
	printf("\033[%d;%dH\033[41m \033[0m", ptr->y + 1, 2 * ptr->x);
	return ptr;
}
int Food_Deter_n(struct snake *head0, struct food *head1, char ward)
{
	int x, y;
	struct food *ptr;
	ptr = head1;
	switch (ward)
	{
	case 'w': {y = (head0->y) - 1; x = head0->x; } break;
	case 's': {y = (head0->y) + 1; x = head0->x; } break;
	case 'd': {x = (head0->x) + 1; y = head0->y; } break;
	case 'a': {x = (head0->x) - 1; y = head0->y; } break;
	}
	for (; ptr != NULL; ptr = ptr->next)
		if (ptr->x == x && ptr->y == y)
		{
			ptr->S = 0;
			return 0;
		}
	return 1;
}
void Food_Deter_f(struct food *head1, struct snake *head0)
{
	int flag = 0;
	struct food *p0, *p1, *p3;
	struct snake *p2;
	p3 = (struct food *)malloc(sizeof(struct food));
	p0 = head1;
	p1 = head1;
	srand(time(NULL));
	for(p0 = head1; p0 != NULL; p0 = p0->next)
		if (p0->S == 0)
		{
			to0:
			p3->x = rand() % ((TD - 2) / 2) + 1;
			p3->y = rand() % (HD - 4) + 3;
			for (p1 = head1; p1 != NULL; p1 = p1->next)
			if (p1->x == p3->x && p1->y == p3->y)
					goto to0;
			for(p2 = head0; p2 != NULL; p2 = p2->next)
				if (p2->x == p3->x && p2->y == p3->y)
					goto to0;
			printf("\033[%d;%dH\033[45m \033[0m", p3->y + 1, 2 * p3->x + 1);
			printf("\033[%d;%dH\033[45m \033[0m", p3->y + 1, 2 * p3->x);
			for (p0 = head1; p0 != NULL; p0 = p0->next)
				if (p0->S == 0)
				{
					p0->x = p3->x;
					p0->y = p3->y;
					p0->S = 1;
					flag = 1;
					Point_op('f');
				}
			if (flag)
				break;
		}
}
int Death_Deter(struct snake *head0, char ward)
{
	int x, y;
	struct snake *ptr;
	ptr = head0;
	switch (ward)
	{
	case 'w': {y = (head0->y) - 1; x = head0->x; } break;
	case 's': {y = (head0->y) + 1; x = head0->x; } break;
	case 'd': {x = (head0->x) + 1; y = head0->y; } break;
	case 'a': {x = (head0->x) - 1; y = head0->y; } break;
	}
	if (x == 0 || y == 0 || y == HD - 1 || x == TD / 2)
		return Point_op('d');
	for (ptr = head0; ptr != NULL; ptr = ptr->next)
		if (x == ptr->x && y == ptr->y)
			return Point_op('d');
	return 0;
}
int Point_op(char a)
{
	int flag = 0;
	if (a == 'f')
	{
		point++;
		printf("\033[21;15H\033[43mpiont: %d\033[0m", point);
	}
	if (a == 'd')
	{
		struct Hero_List *head, *p, *ptr;
		ptr = (struct Hero_List *)malloc(sizeof(struct Hero_List));
		int i;
		system("cls");
		printf("\033[10;13H\033[35mGame over\033[0m");
		printf("\033[13;13H\033[43mpiont: %d\033[0m", point);
		Sleep(3000);
		system("cls");
		head = filePrint();
		if (head->point == 30)
		{
			if (point >= head->point)
			{
				ptr->point = point;
				printf("高分榜留名：");
				scanf("%s", ptr->name);
				head = Insert_Linklist(ptr, head);
			}
		}
		else
		{
			for (p = head, i = 0; i <= 5 && p->point != 30; i++, p = p->next)
				if (point <= p->point)
				{
					ptr->point = point;
					printf("高分榜留名：");
					scanf("%s", ptr->name);
					head = Insert_Linklist(ptr, head);
					break;
				}
		}
		return 1;
	}
}
struct Hero_List *filePrint()
{
	FILE *fp;
	int num, sum, point0 = 0;
	char name[100];
	fp = fopen("hero.txt", "r");
	int size = sizeof(struct Hero_List);
	struct Hero_List *p, *head;
	head = NULL;
	fscanf(fp, "%d %s", &point0, name);
	do
	{
		p = (struct Hero_List *)malloc(size);
		p->point = point0;
		strcpy(p->name, name);
		head = Insert_Linklist(p, head);
		fscanf(fp, "%d%s", &point0, name);
	} while (point0 != 30);
	fclose(fp);
	return head;
}
struct Hero_List *Insert_Linklist(struct Hero_List *p, struct Hero_List *head)
{
	struct Hero_List *ptr, *ptr1, *ptr2;
	ptr = p;
	ptr2 = head;
	if (head == NULL)
	{
		head = ptr;
		p->next = NULL;
	}
	else
	{
		while (ptr->point <= ptr2->point && ptr2->next != NULL)
		{
			ptr1 = ptr2;
			ptr2 = ptr2->next;
		}
		if (ptr->point >= ptr2->point)
		{
			if (ptr2 == head)  head = p;
			else ptr1->next = ptr;
			ptr->next = ptr2;
		}
		else
		{
			ptr2->next = ptr;
			ptr->next = NULL;
		}
	}
		FILE *fp;
		fp = fopen("hero.txt", "w");
		ptr = head;
		do
		{
			fprintf(fp, "%d %s\n", ptr->point, ptr->name);
			ptr = ptr->next;
		} while (ptr != NULL);
		fclose(fp);
	return head;
}





