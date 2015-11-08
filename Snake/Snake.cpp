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
void gerenciaCobra(char tela[ALTURA][LARGURA], Node *snk);
void mov_Snake(char tela[ALTURA][LARGURA], Node *snk, int dir);
void mov_SnakeEsquerda(char tela[ALTURA][LARGURA], Node *snk, int dir);
void mov_SnakeCima(char tela[ALTURA][LARGURA], Node *snk, int dir);
void mov_SnakeDireita(char tela[ALTURA][LARGURA], Node *snk, int dir);
void mov_SnakeBaixo(char tela[ALTURA][LARGURA], Node *snk, int dir);
void food(char tela[ALTURA][LARGURA]);


int main()
{
	char tela[ALTURA][LARGURA];
	Cobra c;
	int dir;

	Node *Snk = cria_corpo();

	inicia_valores(tela, Snk, &c);
	Snk = insereSnake(tela, Snk, c);
	Snk = insereSnake(tela, Snk, c);
	Snk = insereSnake(tela, Snk, c);

	gerenciaCobra(tela, Snk);
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
		if (dir == SETA_ESQUERDA)
		{
			Snk->n.d = ESQUERDA;
			mov_Snake(tela, Snk, dir);
		}
		else if (dir == SETA_CIMA)
		{
			Snk->n.d = CIMA;
			mov_Snake(tela, Snk, dir);
		}
		if (dir == SETA_DIREITA)
		{
			Snk->n.d = DIREITA;
			mov_Snake(tela, Snk, dir);
		}
		else if (dir == SETA_BAIXO)
		{
			Snk->n.d = BAIXO;
			mov_Snake(tela, Snk, dir);
		}
		else if (dir == ESC)
		{
			exit(0);
		}
	}

	free(Snk);
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
}

void gerenciaCobra(char tela[ALTURA][LARGURA], Node *snk)
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

Node *insereSnake(char tela[ALTURA][LARGURA], Node *snk, Cobra c)
{
	Node *novo = (Node *)malloc(sizeof(Node));
	Node *ant = NULL;
	Node *p;

	int i, j;

	for (p = snk; p != NULL; p = p->prox)
	{
		p->n.y++;
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

	if (tela[p->n.x][p->n.y - 1] == ESPACO || tela[p->n.x][p->n.y - 1] == FOOD)
	{
		tela[p->n.x][p->n.y] = ESPACO;
		p->n.y--;
		tela[p->n.x][p->n.y] = p->n.corpo;
		if (tela[p->n.x][p->n.y - 1] == FOOD)
		{
			food(tela);
		}
		if (p->prox != NULL)
		{
			mov_Snake(tela, p->prox, dir);
			p->prox->n.d = p->n.d;
		}
	}
	else if (p->n.y == 1)
	{
		tela[p->n.x][p->n.y] = ESPACO;
		p->n.y = LARGURA - 2;
		tela[p->n.x][p->n.y] = p->n.corpo;
		if (p->prox != NULL)
		{
			mov_Snake(tela, p->prox, dir);
			p->prox->n.d = p->n.d;
		}
	}
}

void mov_SnakeCima(char tela[ALTURA][LARGURA], Node *snk, int dir)
{
	Node *p = snk;

	if (tela[p->n.x - 1][p->n.y] == ESPACO || tela[p->n.x - 1][p->n.y] == FOOD)
	{
		tela[p->n.x][p->n.y] = ESPACO;
		p->n.x--;
		tela[p->n.x][p->n.y] = p->n.corpo;
		if (tela[p->n.x - 1][p->n.y] == FOOD)
		{
			food(tela);
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
		if (p->prox != NULL)
		{
			mov_Snake(tela, p->prox, dir);
			p->prox->n.d = p->n.d;
		}
	}
}

void mov_SnakeDireita(char tela[ALTURA][LARGURA], Node *snk, int dir)
{
	Node *p = snk;

	if (tela[p->n.x][p->n.y + 1] == ESPACO || tela[p->n.x][p->n.y + 1] == FOOD)
	{
		tela[p->n.x][p->n.y] = ESPACO;
		p->n.y++;
		tela[p->n.x][p->n.y] = p->n.corpo;
		if (tela[p->n.x][p->n.y + 1] == FOOD)
		{
			food(tela);
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
		if (p->prox != NULL)
		{
			mov_Snake(tela, p->prox, dir);
			p->prox->n.d = p->n.d;
		}
	}
}

void mov_SnakeBaixo(char tela[ALTURA][LARGURA], Node *snk, int dir)
{
	Node *p = snk;

	if (tela[p->n.x + 1][p->n.y] == ESPACO || tela[p->n.x + 1][p->n.y] == FOOD)
	{
		tela[p->n.x][p->n.y] = ESPACO;
		p->n.x++;
		tela[p->n.x][p->n.y] = p->n.corpo;
		if (tela[p->n.x + 1][p->n.y] == FOOD)
		{
			food(tela);
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
		if (p->prox != NULL)
		{
			mov_Snake(tela, p->prox, dir);
			p->prox->n.d = p->n.d;
		}
	}
}

void food(char tela[ALTURA][LARGURA])
{
	int x, y;

	srand(time(NULL));
	x = 1 + (rand() % 23);
	y = 1 + (rand() % 68);

	tela[x][y] = FOOD;
}