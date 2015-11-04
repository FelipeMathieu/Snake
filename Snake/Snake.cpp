#include<malloc.h>
#include<conio.h>
#include<stdlib.h>
#include<stdio.h>
#include<Windows.h>
#include "Header.h"

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
void desenha(char tela[ALTURA][LARGURA], Node *snk);
Node *cria_corpo(void);
Node *insereFim(char tela[ALTURA][LARGURA], Node *snk, Cobra c);
void mov_Snake(char tela[ALTURA][LARGURA], Node *snk, Cobra *c);

int main()
{
	char tela[ALTURA][LARGURA];
	Cobra c;
	int dir;
	
	Node *Snk = cria_corpo();

	inicia_valores(tela, Snk, &c);
	Snk = insereFim(tela, Snk, c);
	Snk = insereFim(tela, Snk, c);
	Snk = insereFim(tela, Snk, c);
	
	while (1)
	{
		COORD cord;
		cord.X = 0;
		cord.Y = 0;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
		desenha(tela, Snk);

		if (_kbhit())
		{
			dir = _getch();
		}
	}
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
	tela[ALTURA / 2][LARGURA / 2] = c->corpo;
	c->x = ALTURA / 2;
	c->y = LARGURA / 2;
	tela[ALTURA/2][(LARGURA + 2)/2] = FOOD;
	c->d = DIREITA;
}

void desenha(char tela[ALTURA][LARGURA], Node *snk)
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

Node *insereFim(char tela[ALTURA][LARGURA], Node *snk, Cobra c)
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
		snk->n.y--;
	}

	tela[novo->n.x][snk->n.y] = novo->n.corpo;

	return snk;
}
