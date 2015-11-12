#include<malloc.h>
#include<conio.h>
#include<stdlib.h>
#include<stdio.h>
#include<Windows.h>
#include<time.h>

#define LARGURA 70
#define ALTURA 25
#define ESPACO ' '

#define VERTICAL 186
#define HORIZONTAL 205
#define SUPERIOR_DIREITO 187
#define INFERIOR_DIREITO 188
#define SUPERIOR_ESQUERDO 201
#define INFERIOR_ESQUERDO 200

#define SETA_CIMA 72
#define SETA_BAIXO 80
#define SETA_ESQUERDA 75
#define SETA_DIREITA 77

#define SNAKE 254
#define FOOD 1

#define ESC 27

typedef enum direcao {
	CIMA,
	BAIXO,
	ESQUERDA,
	DIREITA
}Direcao;

typedef struct cobra {
	int x, y;
	int corpo = SNAKE;
	Direcao d;
}Cobra;

typedef struct Node {
	Cobra n;
	struct Node *prox;
};

void inicia_valores(char tela[ALTURA][LARGURA], Node *snk, Cobra *c);
void desenha(char tela[ALTURA][LARGURA]);
Node *cria_corpo(void);
Node *insereSnake(char tela[ALTURA][LARGURA], Node *snk, Cobra c);
Node *insereCorpo(char tela[ALTURA][LARGURA], Node *snk, Cobra c);
void gerenciaCobra(char tela[ALTURA][LARGURA], Node *snk, int dir);
void mov_Snake(char tela[ALTURA][LARGURA], Node *snk, int dir);
void mov_SnakeEsquerda(char tela[ALTURA][LARGURA], Node *snk, int dir);
void mov_SnakeCima(char tela[ALTURA][LARGURA], Node *snk, int dir);
void mov_SnakeDireita(char tela[ALTURA][LARGURA], Node *snk, int dir);
void mov_SnakeBaixo(char tela[ALTURA][LARGURA], Node *snk, int dir);
void food(char tela[ALTURA][LARGURA]);
void reset(char tela[ALTURA][LARGURA], Node *snk);
void update(char tela[ALTURA][LARGURA], Node *snk, int dir);
void score(char tela[ALTURA][LARGURA]);

char u = '0', d = '0', c = '0';
char s[3];

int main(void)
{
	char tela[ALTURA][LARGURA];
	Cobra c;
	int dir = SETA_DIREITA;

	Node *Snk = cria_corpo();

	inicia_valores(tela, Snk, &c);
	Snk = insereSnake(tela, Snk, c);
	Snk = insereSnake(tela, Snk, c);
	Snk = insereSnake(tela, Snk, c);

	gerenciaCobra(tela, Snk, dir);
	food(tela);

	while (1)
	{
		COORD cord;
		cord.X = 0;
		cord.Y = 0;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
		desenha(tela);

		if (_kbhit())
		{
			dir = _getch();
		}
		update(tela, Snk, dir);
	}

	printf("\n");
	system("pause");
	return 0;
}

Node *cria_corpo(void)
{
	return NULL;
}

void inicia_valores(char tela[ALTURA][LARGURA], Node *snk, Cobra *c)
{
	int i, j;

	for (i = 0; i < ALTURA; i++)
	{
		for (j = 0; j < LARGURA; j++)
		{
			if (i == 0 || i == ALTURA - 1)
			{
				tela[i][j] = HORIZONTAL;
			}
			else if (j == 0 || j == LARGURA - 1)
			{
				tela[i][j] = VERTICAL;
			}
			else
			{
				tela[i][j] = ESPACO;
			}
		}
	}

	tela[0][0] = SUPERIOR_ESQUERDO;
	tela[0][LARGURA - 1] = SUPERIOR_DIREITO;
	tela[ALTURA - 1][0] = INFERIOR_ESQUERDO;
	tela[ALTURA - 1][LARGURA - 1] = INFERIOR_DIREITO;
	c->x = ALTURA / 2;
	c->y = LARGURA / 2;
	c->d = DIREITA;

	tela[0][(LARGURA/2)-3] = 'S';
	tela[0][(LARGURA/2)-2] = 'C';
	tela[0][(LARGURA/2)-1] = 'O';
	tela[0][LARGURA/2] = 'R';
	tela[0][(LARGURA/2) + 1] = 'E';
	tela[0][(LARGURA/2) + 2] = ':';
	score(tela);
}

void gerenciaCobra(char tela[ALTURA][LARGURA], Node *snk, int dir)
{
	for (Node *p = snk; p != NULL; p = p->prox)
	{
		tela[p->n.x][p->n.y] = p->n.corpo;
	}
}

void desenha(char tela[ALTURA][LARGURA])
{
	int i, j;

	for (i = 0; i < ALTURA; i++)
	{
		for (j = 0; j < LARGURA; j++)
		{
			printf("%c", tela[i][j]);
		}
		printf("\n");
	}
}

Node *insereCorpo(char tela[ALTURA][LARGURA], Node *snk, Cobra c)
{
	Node *novo = (Node *)malloc(sizeof(Node));
	Node *ant = NULL;
	Node *p = snk;

	for (p; p != NULL; p = p->prox)
	{
		ant = p;
	}

	novo->n = c;

	if (ant->prox == NULL && ant->n.d == ESQUERDA)
	{
		novo->prox = ant->prox;
		ant->prox = novo;
	}
	if (ant->prox == NULL && ant->n.d == DIREITA)
	{
		novo->prox = ant->prox;
		ant->prox = novo;
	}
	if (ant->prox == NULL && ant->n.d == CIMA)
	{
		novo->prox = ant->prox;
		ant->prox = novo;
	}
	if (ant->prox == NULL && ant->n.d == BAIXO)
	{
		novo->prox = ant->prox;
		ant->prox = novo;
	}

	return p;
}

Node *insereSnake(char tela[ALTURA][LARGURA], Node *snk, Cobra c)
{
	Node *novo = (Node *)malloc(sizeof(Node));
	Node *ant = NULL;
	Node *p;
	
	for (p = snk; p != NULL; p = p->prox)
	{
		ant = p;
	}

	novo->n = c;

	if (ant == NULL)
	{
		novo->prox = snk;
		snk = novo;
	}
	else
	{
		novo->prox = ant->prox;
		ant->prox = novo;
	}

	return snk;
}

void mov_Snake(char tela[ALTURA][LARGURA], Node *snk, int dir)
{
	Node *p = snk;

	if (p->n.d == ESQUERDA)
	{
		mov_SnakeEsquerda(tela, p, dir);
	}
	else if (p->n.d == CIMA)
	{
		mov_SnakeCima(tela, p, dir);
	}
	if (p->n.d == DIREITA)
	{
		mov_SnakeDireita(tela, p, dir);
	}
	else if (p->n.d == BAIXO)
	{
		mov_SnakeBaixo(tela, p, dir);
	}
}

void mov_SnakeEsquerda(char tela[ALTURA][LARGURA], Node *snk, int dir)
{
	Node *p = snk;
	Node *aux = NULL;

	if ((tela[p->n.x][p->n.y - 1] == ESPACO || tela[p->n.x][p->n.y - 1] == FOOD) && p->n.y != 1)
	{
		tela[p->n.x][p->n.y] = ESPACO;
		p->n.y--;
		tela[p->n.x][p->n.y] = p->n.corpo;

		if (tela[p->n.x][p->n.y - 1] == FOOD)
		{
			for (aux = snk; aux->prox != NULL; aux = aux->prox);
			mov_Snake(tela, p, dir);
			insereCorpo(tela, aux, aux->n);
			gerenciaCobra(tela, p, dir);
			food(tela);
			score(tela);
		}
		if (p->prox != NULL)
		{
			mov_Snake(tela, p->prox, dir);
			p->prox->n.d = p->n.d;
		}
	}
	else if(p->n.y == 1)
	{
		tela[p->n.x][p->n.y] = ESPACO;
		p->n.y = LARGURA - 2;
		tela[p->n.x][p->n.y] = p->n.corpo;

		if (tela[p->n.x][p->n.y - 1] == FOOD)
		{
			for (aux = p; aux->prox != NULL; aux = aux->prox)
			{
				if (aux->n.y <= LARGURA - 2 && aux->prox == NULL)
				{
					//for (aux = snk; aux->prox != NULL; aux = aux->prox);
					mov_Snake(tela, p, dir);
					insereCorpo(tela, aux, aux->n);
					gerenciaCobra(tela, p, dir);
					food(tela);
					score(tela);
				}
			}
		}
		if (p->prox != NULL)
		{
			mov_Snake(tela, p->prox, dir);
			p->prox->n.d = p->n.d;
		}
	}
	else
	{
		for (aux = p; aux->prox != NULL; aux = aux->prox)
		{
			if ((aux->n.y - 1) == aux->prox->n.y)
			{
				reset(tela, p);
			}
			else
			{
				for (p; p->prox != NULL; p = p->prox)
				{
					if ((aux->n.y - 1) == p->prox->n.y)
					{
						reset(tela, p);
					}
				}
			}
		}
	}
}

void mov_SnakeCima(char tela[ALTURA][LARGURA], Node *snk, int dir)
{
	Node *p = snk;
	Node *aux = NULL;

	if ((tela[p->n.x - 1][p->n.y] == ESPACO || tela[p->n.x - 1][p->n.y] == FOOD) && p->n.x != 1)
	{
		tela[p->n.x][p->n.y] = ESPACO;
		p->n.x--;
		tela[p->n.x][p->n.y] = p->n.corpo;
		if (tela[p->n.x - 1][p->n.y] == FOOD)
		{
			for (aux = snk; aux->prox != NULL; aux = aux->prox);
			insereCorpo(tela, aux, aux->n);
			mov_Snake(tela, p, dir);
			gerenciaCobra(tela, p, dir);
			food(tela);
			score(tela);
		}
		if (p->prox != NULL)
		{
			mov_Snake(tela, p->prox, dir);
			p->prox->n.d = p->n.d;
		}
	}
	else if (p->n.x == 1)
	{
		tela[p->n.x][p->n.y] = ESPACO;
		p->n.x = ALTURA - 2;
		tela[p->n.x][p->n.y] = p->n.corpo;
		if (tela[p->n.x - 1][p->n.y] == FOOD)
		{
			for (aux = p; aux->prox != NULL; aux = aux->prox)
			{
				if (aux->n.x <= ALTURA - 2 && aux->prox == NULL)
				{
					//for (aux = snk; aux->prox != NULL; aux = aux->prox);
					mov_Snake(tela, p, dir);
					insereCorpo(tela, aux, aux->n);
					gerenciaCobra(tela, p, dir);
					food(tela);
					score(tela);
				}
			}
		}
		if (p->prox != NULL)
		{
			mov_Snake(tela, p->prox, dir);
			p->prox->n.d = p->n.d;
		}
	}
	else
	{
		for (aux = p; aux->prox != NULL; aux = aux->prox)
		{
			if ((aux->n.x - 1) == aux->prox->n.x)
			{
				reset(tela, p);
			}
			else
			{
				for (p; p->prox != NULL; p = p->prox)
				{
					if ((aux->n.x - 1) == p->prox->n.x)
					{
						reset(tela, p);
					}
				}
			}
		}
	}
}

void mov_SnakeDireita(char tela[ALTURA][LARGURA], Node *snk, int dir)
{
	Node *p = snk;
	Node *aux = NULL;

	if ((tela[p->n.x][p->n.y + 1] == ESPACO || tela[p->n.x][p->n.y + 1] == FOOD)  && p->n.y != LARGURA - 2)
	{
		tela[p->n.x][p->n.y] = ESPACO;
		p->n.y++;
		tela[p->n.x][p->n.y] = p->n.corpo;
		if (tela[p->n.x][p->n.y + 1] == FOOD)
		{
			for (aux = snk; aux->prox != NULL; aux = aux->prox);
			mov_Snake(tela, p, dir);
			insereCorpo(tela, aux, aux->n);
			gerenciaCobra(tela, p, dir);
			food(tela);
			score(tela);
		}
		if (p->prox != NULL)
		{
			mov_Snake(tela, p->prox, dir);
			p->prox->n.d = p->n.d;
		}
	}
	else if (p->n.y == LARGURA - 2)
	{
		tela[p->n.x][p->n.y] = ESPACO;
		p->n.y = 1;
		tela[p->n.x][p->n.y] = p->n.corpo;
		tela[p->n.x][0] = VERTICAL;
		tela[p->n.x][LARGURA] = VERTICAL;
		if (tela[p->n.x][p->n.y + 1] == FOOD)
		{
			for (aux = p; aux->prox != NULL; aux = aux->prox)
			{
				if (aux->n.y >= 1 && aux->prox == NULL)
				{
					//for (aux = snk; aux->prox != NULL; aux = aux->prox);
					mov_Snake(tela, p, dir);
					insereCorpo(tela, aux, aux->n);
					gerenciaCobra(tela, p, dir);
					food(tela);
					score(tela);
				}
			}
		}
		if (p->prox != NULL)
		{
			mov_Snake(tela, p->prox, dir);
			p->prox->n.d = p->n.d;
		}
	}
	else
	{
		for (aux = p; aux->prox != NULL; aux = aux->prox)
		{
			if ((aux->n.y + 1) == aux->prox->n.y)
			{
				reset(tela, p);
			}
			else
			{
				for (p; p->prox != NULL; p = p->prox)
				{
					if ((aux->n.y + 1) == p->prox->n.y)
					{
						reset(tela, p);
					}
				}
			}
		}
	}
}

void mov_SnakeBaixo(char tela[ALTURA][LARGURA], Node *snk, int dir)
{
	Node *p = snk;
	Node *aux = NULL;

	if ((tela[p->n.x + 1][p->n.y] == ESPACO || tela[p->n.x + 1][p->n.y] == FOOD) && p->n.x != ALTURA - 2)
	{
		tela[p->n.x][p->n.y] = ESPACO;
		p->n.x++;
		tela[p->n.x][p->n.y] = p->n.corpo;
		if (tela[p->n.x + 1][p->n.y] == FOOD)
		{
			for (aux = snk; aux->prox != NULL; aux = aux->prox);
			insereCorpo(tela, aux, aux->n);
			mov_Snake(tela, p, dir);
			gerenciaCobra(tela, p, dir);
			food(tela);
			score(tela);
		}
		if (p->prox != NULL)
		{
			mov_Snake(tela, p->prox, dir);
			p->prox->n.d = p->n.d;
		}
	}
	else if (p->n.x == ALTURA - 2)
	{
		tela[p->n.x][p->n.y] = ESPACO;
		p->n.x = 1;
		tela[p->n.x][p->n.y] = p->n.corpo;
		if (tela[p->n.x + 1][p->n.y] == FOOD)
		{
			for (aux = p; aux->prox != NULL; aux = aux->prox)
			{
				if (aux->n.x >= 1 && aux->prox == NULL)
				{
					//for (aux = snk; aux->prox != NULL; aux = aux->prox);
					mov_Snake(tela, p, dir);
					insereCorpo(tela, aux, aux->n);
					gerenciaCobra(tela, p, dir);
					food(tela);
					score(tela);
				}
			}
		}
		if (p->prox != NULL)
		{
			mov_Snake(tela, p->prox, dir);
			p->prox->n.d = p->n.d;
		}
	}
	else
	{
		for (aux = p; aux->prox != NULL; aux = aux->prox)
		{
			if ((aux->n.x + 1) == aux->prox->n.x)
			{
				reset(tela, p);
			}
			else
			{
				for (p; p->prox != NULL; p = p->prox)
				{
					if ((aux->n.x + 1) == p->prox->n.x)
					{
						reset(tela, p);
					}
				}
			}
		}
	}
}

void food(char tela[ALTURA][LARGURA])
{
	int x, y;

	x = rand() % ALTURA;
	y = rand() % LARGURA;

	if (x > 1 && x < ALTURA - 2 && y > 1 && y < LARGURA - 2 && tela[x][y] == ESPACO)
	{
		tela[x][y] = FOOD;
	}
	else
	{
		food(tela);
	}
}

void reset(char tela[ALTURA][LARGURA], Node *snk)
{
	int c;

	for (int i = 0; i < ALTURA; i++)
	{
		for (int j = 0; j < LARGURA; j++)
		{
			if (i == 0 || i == ALTURA - 1)
			{
				tela[i][j] = HORIZONTAL;
			}
			else if (j == 0 || j == LARGURA - 1)
			{
				tela[i][j] = VERTICAL;
			}
			else
			{
				tela[i][j] = ESPACO;
			}
		}
	}

	tela[0][0] = SUPERIOR_ESQUERDO;
	tela[0][LARGURA - 1] = SUPERIOR_DIREITO;
	tela[ALTURA - 1][0] = INFERIOR_ESQUERDO;
	tela[ALTURA - 1][LARGURA - 1] = INFERIOR_DIREITO;

	tela[ALTURA / 2][(LARGURA / 2) - 3] = 'V';
	tela[ALTURA / 2][(LARGURA / 2) - 2] = 'O';
	tela[ALTURA / 2][(LARGURA / 2) - 1] = 'C';
	tela[ALTURA / 2][(LARGURA / 2)] = 'E';
	tela[ALTURA / 2][(LARGURA / 2) + 1] = ESPACO;
	tela[ALTURA / 2][(LARGURA / 2) + 2] = 'P';
	tela[ALTURA / 2][(LARGURA / 2) + 3] = 'E';
	tela[ALTURA / 2][(LARGURA / 2) + 4] = 'R';
	tela[ALTURA / 2][(LARGURA / 2) + 5] = 'D';
	tela[ALTURA / 2][(LARGURA / 2) + 6] = 'E';
	tela[ALTURA / 2][(LARGURA / 2) + 7] = 'U';

	tela[(ALTURA / 2) + 1][(LARGURA / 2) - 5] = 'C';
	tela[(ALTURA / 2) + 1][(LARGURA / 2) - 4] = 'O';
	tela[(ALTURA / 2) + 1][(LARGURA / 2) - 3] = 'N';
	tela[(ALTURA / 2) + 1][(LARGURA / 2) - 2] = 'T';
	tela[(ALTURA / 2) + 1][(LARGURA / 2) - 1] = 'I';
	tela[(ALTURA / 2) + 1][(LARGURA / 2)] = 'N';
	tela[(ALTURA / 2) + 1][(LARGURA / 2) + 1] = 'U';
	tela[(ALTURA / 2) + 1][(LARGURA / 2) + 2] = 'A';
	tela[(ALTURA / 2) + 1][(LARGURA / 2) + 3] = 'R';
	tela[(ALTURA / 2) + 1][(LARGURA / 2) + 4] = '?';
	tela[(ALTURA / 2) + 1][(LARGURA / 2) + 5] = '(';
	tela[(ALTURA / 2) + 1][(LARGURA / 2) + 6] = 'S';
	tela[(ALTURA / 2) + 1][(LARGURA / 2) + 7] = '/';
	tela[(ALTURA / 2) + 1][(LARGURA / 2) + 8] = 'N';
	tela[(ALTURA / 2) + 1][(LARGURA / 2) + 9] = ')';


	COORD cord;
	cord.X = 0;
	cord.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
	desenha(tela);
	c = _getch();

	if (c == 's' || c == 'S')
	{
		u = '0';
		d = '0';
		c = '0';
		free(snk);
		main();
	}
	else if(c == 'n' || c == 'N')
	{
		free(snk);
		exit(0);
	}
	else
	{
		reset(tela, snk);
	}
}

void update(char tela[ALTURA][LARGURA], Node *snk, int dir)
{
	Node *p = snk;
	Node *aux = NULL;

	if (dir == SETA_ESQUERDA)
	{
		if (tela[p->n.x][p->n.y - 1] == FOOD)
		{
			for (aux = p; aux->prox != NULL; aux = aux->prox);
			insereCorpo(tela, aux, aux->n);
			p->n.d = ESQUERDA;
			mov_Snake(tela, p, dir);
			gerenciaCobra(tela, p, dir);
			food(tela);
			score(tela);
		}
		else
		{
			p->n.d = ESQUERDA;
			mov_Snake(tela, p, dir);
		}
	}
	else if (dir == SETA_CIMA)
	{
		if (tela[p->n.x - 1][p->n.y] == FOOD)
		{
			for (aux = p; aux->prox != NULL; aux = aux->prox);
			insereCorpo(tela, aux, aux->n);
			p->n.d = CIMA;
			mov_Snake(tela, p, dir);
			gerenciaCobra(tela, p, dir);
			food(tela);
			score(tela);
		}
		else
		{
			p->n.d = CIMA;
			mov_Snake(tela, p, dir);
		}
	}
	if (dir == SETA_DIREITA)
	{
		if (tela[p->n.x][p->n.y + 1] == FOOD)
		{
			for (aux = p; aux->prox != NULL; aux = aux->prox);
			insereCorpo(tela, aux, aux->n);
			p->n.d = DIREITA;
			mov_Snake(tela, p, dir);
			gerenciaCobra(tela, p, dir);
			food(tela);
			score(tela);
		}
		else
		{
			p->n.d = DIREITA;
			mov_Snake(tela, p, dir);
		}
	}
	else if (dir == SETA_BAIXO)
	{
		if (tela[p->n.x + 1][p->n.y] == FOOD)
		{
			for (aux = p; aux->prox != NULL; aux = aux->prox);
			insereCorpo(tela, aux, aux->n);
			p->n.d = BAIXO;
			mov_Snake(tela, p, dir);
			gerenciaCobra(tela, p, dir);
			food(tela);
			score(tela);
		}
		else
		{
			p->n.d = BAIXO;
			mov_Snake(tela, p, dir);
		}
	}
	else if (dir == ESC)
	{
		exit(0);
	}
}

void score(char tela[ALTURA][LARGURA])
{	
	int i;

	if (u <= '9' && d <= '9' && c <= '9')
	{
		if (u == '0')
		{
			u++;
			for (i = 0; i < 3; i++)
			{
				if (i == 0)
				{
					s[i] = c;
				}
				if (i == 1)
				{
					s[i] = d;
				}
				if (i == 2)
				{
					s[i] = u;
				}
			}
			for (i = 0; i < 3; i++)
			{
				tela[0][(LARGURA / 2) + 3 + i] = s[i];
			}
		}
		else if (u == '9')
		{
			d++;
			u = '0';
			for (i = 0; i < 3; i++)
			{
				if (i == 0)
				{
					s[i] = c;
				}
				if (i == 1)
				{
					s[i] = d;
				}
				if (i == 2)
				{
					s[i] = u;
				}
			}
			for (i = 0; i < 3; i++)
			{
				tela[0][(LARGURA / 2) + 3 + i] = s[i];
			}
		}
		else if (d == '9')
		{
			c++;
			d = '0';
			u = '0';
			for (i = 0; i < 3; i++)
			{
				if (i == 0)
				{
					s[i] = c;
				}
				if (i == 1)
				{
					s[i] = d;
				}
				if (i == 2)
				{
					s[i] = u;
				}
			}
			for (i = 0; i < 3; i++)
			{
				tela[0][(LARGURA / 2) + 3 + i] = s[i];
			}
		}
		else if(u > '0' && u < '9')
		{
			u++;
			for (i = 0; i < 3; i++)
			{
				if (i == 0)
				{
					s[i] = c;
				}
				if (i == 1)
				{
					s[i] = d;
				}
				if (i == 2)
				{
					s[i] = u;
				}
			}
			for (i = 0; i < 3; i++)
			{
				tela[0][(LARGURA / 2) + 3 + i] = s[i];
			}
		}
	}
}
