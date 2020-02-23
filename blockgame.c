#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

typedef struct node{int x,y,xt,yt,type,i,c; struct node *next;}NODE;
typedef NODE *LIST;
typedef struct q{LIST front,rear;}Q;

#define size 10

void gotoxy(int x,int y)
{
	printf("%c[%d;%df",0x1B,y,x);
}

Q createQ()
{
	Q q;
	q.front=q.rear=NULL;
	return q;
}

LIST makeNode(int x, int y, int xt, int yt, int type,int i)
{
	LIST t;
	t = (LIST)malloc(sizeof(NODE));
	t->x = x;
	t->y = y;
	t->xt = xt;
	t->yt = yt;
	t->type = type;
	t->c=1;
	t->next = NULL;
	return t;
}

LIST insert(LIST l,int x,int y,int type,int i)
{
	LIST temp,t=l;
	temp=NULL;
	int xt,yt;
	switch(type)
	{
		case 1:	xt=2;yt=2;break;
		case 2: xt=2;yt=1;break;
		case 3: xt=1;yt=2;break;
	}
	temp = makeNode(x,y,xt,yt,type,i);
	if(!l)
		return temp;

	while(t->next)
		{t=t->next;}
	t->next = temp;
	return l;
}

Q insertq(Q q,int x,int y,int type,int i)
{
	int xt,yt;
	switch(type)
	{
		case 1:	xt=2;yt=2;break;
		case 2: xt=2;yt=1;break;
		case 3: xt=1;yt=2;break;
	}
	LIST newNode=makeNode(x,y,xt,yt,type,i);
	if(!(q.rear) || !(q.front))
	{
		q.rear=newNode;
		q.front=q.rear;
	}
	else
	{
		(q.rear)->next=newNode;
		q.rear=(q.rear)->next;
	}
	//printf("%d",q.front->x);
	return q;
}

void display(LIST l)
{
	if(!l)	return;
	gotoxy(10,10);
	while(l)
	{printf("[%d:%d]:[%d:%d]:%d: \n",l->x,l->y,l->xt,l->yt,l->type);l=l->next;}
}

void displayqq(Q l)
{
	if(!l.front)	return;
	gotoxy(40,10);
	while(l.front)
	{printf("[%d:%d]:[%d:%d]:%d: \n",l.front->x,l.front->y,l.front->xt,l.front->yt,l.front->type);l.front=l.front->next;}
}

int count(LIST l)
{
	int i=1;
	while(l->next)
		{i++;l=l->next;}
	return i;
}

int search(LIST l, int x, int y)
{
	if(!l)	return 0;
	LIST l1;
	l1=l;
	int i;
	while(l1)
		{
			if(l1->x == x )//&& l1->y == y)// || (l1->x)+(l1->type) == x || (l1->y)+(l1->type) == y)
				{i=1;break;}
			i=0;l1=l1->next;
		}
	return i;
}

LIST score(LIST l, int x, int y)
{
	if(!l)	return NULL;
	LIST l1;
	l1=l;
	while(l1)
		{
			if(l1->x == x )//&& l1->y == y)// || (l1->x)+(l1->type) == x || (l1->y)+(l1->type) == y)
				{l1->c+=1;break;}
			l1=l1->next;
		}
	return l;
}

void block_create(int x,int y,int type)
{
	switch(type)
	{
		case 1:	gotoxy(x,y);
				printf("▆ ▆");
				gotoxy(x,y-1);
				printf("▆ ▆");
				gotoxy(0,0);
				break;
		case 2:	gotoxy(x,y);
				printf("▆ ▆");
				gotoxy(0,0);
				break;
		case 3:	gotoxy(x,y);
				printf("▆ ");
				gotoxy(x,y-1);
				printf("▆ ");
				gotoxy(0,0);
				break;
	}
}

void displaym(LIST l)
{
	if(!l)	return;
	while(l)
	{
		block_create(l->x,l->y,l->type);
		l = l->next;
	}
}

void displayq(Q q)
{
	if(!q.front)	return;
	while(q.front)
	{
		block_create(q.front->x,q.front->y,q.front->type);
		q.front = q.front->next;
	}
}

Q updateq(Q t)
{
	Q q;
	q=t;
	while(q.front)
	{
		if(q.front->type==2)
			q.front->y +=1;
		else
			q.front->y +=2;
		q.front = q.front->next;
	}
	return t;
}

LIST updatel(LIST t)
{
	LIST l;
	l=t;
	if(!l)
	return NULL;

	while(l)
	{
		if(l->type==2)
			l->y = (l->y) +1;
		else
			l->y = (l->y) +2;
		l=l->next;
	}
	return t;
}

LIST check(LIST l, Q q[])
{
	LIST t;
	t=NULL;
	int x,y,type;
	int i;
	if(!l)	return NULL;
	if(count(l)==9)
		{
			for(i=0;i<9;i++)
			{
				if(q[i].front)
				{
				x = (q[i].front)->x;
				y = (q[i].front)->y;
				type = (q[i].front)->type;
				t = insert(t,x,y,type,0);
				q[i]=updateq(q[i]);
				q[i].front = q[i].front->next;
				}
			}
		t=updatel(t);
		return t;
		}
	else
	return l;
}

void gameover()
{
	gotoxy(35,10);
	printf("GAME OVER!");
}

void scoredisp(LIST l)
{
	gotoxy(65,3);
	int score=0;
	if(!l)	return;
	while(l)
	{
		score+=2*(l->c);
		l=l->next;
	}
	printf("Score:%d",score);
}

void createhud(LIST l, Q q[])
{
	int x=20,y=3,Y[20],i=0,j,k;
	char c;
	int type;
	for(i=0;i<20;i++)	Y[i]=22;
	i=0;
	while(1)
	{
	start:type=1;//(rand()%3)+1;
	while(x>=20 && x<=55)
	{
		system("clear");
		if(Y[i]==size)
			{scoredisp(l);gameover();goto stop;}
		LIST t=l;
		scoredisp(l);
		l = check(l,q);
		if(t!=l)
			for(k=0;k<20;k++)
				{
					Y[k]+=2;
				}
		/*
		if(l)
			if(count(l)==8)
				for(k=0;k<9;k++)
					if(q[k].front)
					{
						q[k] = updateq(q[k]);printf("\n%d\n",k);
						//Y[k]+=2;
						q[k].front=q[k].front->next;
					}
		*/
		displaym(l);
		for(j=0;j<20;j++)
			displayq(q[j]);

		//display(l);
		//displayqq(q[i]);
		//printf("\n%d\n",i);
		//printf("%d%d",x,y);

		gotoxy(x,y);
		printf("˅˅˅");
		block_create(x,y+1,type);
		if(c!='.')
		system ("/bin/stty raw");
		c = getchar();
		system ("/bin/stty cooked");
		if(c=='d')
		{
			x+=4;
			i++;
		}
		else if(c=='a')
		{
			x-=4;
			i--;
		}
		else if(c=='s')
			{
				system("clear");
				system("cls");
				if(search(l,x,Y[i])==0)
				{
					l=score(l,x,Y[i]);
					l = insert(l,x,Y[i],type,0);
					display(l);
					block_create(x,Y[i],type);
					if(type==2)
					{
						Y[i]--;
						break;
					}
					Y[i]-=2;
					break;
				}
				else
				{
					q[i]=insertq(q[i],x,Y[i],type,0);
					block_create(x,Y[i],type);
					if(type==2)
					{
						Y[i]--;
						break;
					}
					Y[i]-=2;

				}

			}
	}
	system ("/bin/stty cooked");
	x=20;
	i=0;
	goto start;
	}
	stop:i=0;
}

void menu()
{
	gotoxy(30,5);
	printf("凸");
	gotoxy(30,6);
	printf("PLAY TETRIS!");
	getchar();
}
int main()
{
	LIST l;
	Q q[20];
	int i;
	for(i=0;i<20;i++)
		q[i]=createQ();
	l = NULL;
	system("cls");
	system("clear");
	menu();
	createhud(l,q);
	getchar();
}
