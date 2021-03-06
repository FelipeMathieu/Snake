#define _CRT_SECURE_NO_WARNINGS

#include<malloc.h>
#include<conio.h>
#include<stdlib.h>
#include<stdio.h>
#include<Windows.h>
#include<time.h>
#include<string.h>

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

#define TT 178
#define TY 177

#define ESC 27
#define ENTER 13
#define SETINHA 175

#define TEMA PlaySound(TEXT("TEMA.wav"), NULL, SND_LOOP | SND_ASYNC)
#define HIT PlaySound(TEXT("Hit.wav"), NULL, SND_LOOP | SND_ASYNC)

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

typedef struct seta {
	int x;
}Seta;

void placar(char tela[ALTURA][LARGURA]);
void inicia_valores(char tela[ALTURA][LARGURA], Node *snk, Cobra *c);
void desenha(char tela[ALTURA][LARGURA], Node *Snk);
Node *cria_corpo(void);
Node *insereSnake(char tela[ALTURA][LARGURA], Node *snk, Cobra c);
Node *insereCorpo(char tela[ALTURA][LARGURA], Node *snk, Cobra c);
void gerenciaCobra(char tela[ALTURA][LARGURA], Node *snk, int dir);
void mov_Snake(char tela[ALTURA][LARGURA], Node *snk, int dir, int m);
void mov_SnakeEsquerda(char tela[ALTURA][LARGURA], Node *snk, int dir, int m);
void mov_SnakeCima(char tela[ALTURA][LARGURA], Node *snk, int dir, int m);
void mov_SnakeDireita(char tela[ALTURA][LARGURA], Node *snk, int dir, int m);
void mov_SnakeBaixo(char tela[ALTURA][LARGURA], Node *snk, int dir, int m);
void food(char tela[ALTURA][LARGURA]);
void reset(char tela[ALTURA][LARGURA], Node *snk);
void update(char tela[ALTURA][LARGURA], Node *snk, int dir, int m);
void score(char tela[ALTURA][LARGURA]);
Node *inicia_valores_load(FILE *save, char tela[ALTURA][LARGURA], Node *snk, Cobra *c);
FILE *menuInicial(char tela[ALTURA][LARGURA], Node *snk, int *m);
int menuDificuldade(char tela[ALTURA][LARGURA], Node *snk);
FILE *menuLoad(char tela[ALTURA][LARGURA], Node *snk, int *m);
void saveGame(char tela[ALTURA][LARGURA], Node *snk, int m);

char unidade = '0', dezena = '0', centena = '0';
char s[3];
int x, y;
int loade;

int main(int mM)
{
	char tela[ALTURA][LARGURA];
	int dir, m, pause = 0;
	Cobra c;
	Seta s;
	FILE *save = NULL;

	loade = 0;

	Node *Snk = cria_corpo();

	save = menuInicial(tela, Snk, &m);

	if (save == NULL)
	{
		dir = SETA_DIREITA;
		inicia_valores(tela, Snk, &c);
		Snk = insereSnake(tela, Snk, c);
		Snk = insereSnake(tela, Snk, c);
		Snk = insereSnake(tela, Snk, c);
	}
	else
	{
		Snk = inicia_valores_load(save, tela, Snk, &c);
		dir = Snk->n.d;
		loade = 1;
		fclose(save);
	}

	gerenciaCobra(tela, Snk, dir);
	if (loade == 0)
	{
		food(tela);
	}
	tela[x][y] = FOOD;
	loade = 0;

	TEMA;

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
			if (dir == 'p')
			{
				tela[3][33] = 'P';
				tela[3][34] = 'A';
				tela[3][35] = 'U';
				tela[3][36] = 'S';
				tela[3][37] = 'E';
				tela[3][38] = ':';
				tela[5][32] = SETINHA;
				s.x = 5;
				tela[5][33] = 'S';
				tela[5][34] = 'A';
				tela[5][35] = 'V';
				tela[5][36] = 'E';
				tela[6][33] = 'Q';
				tela[6][34] = 'U';
				tela[6][35] = 'I';
				tela[6][36] = 'T';

				while (pause == 0)
				{
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
					desenha(tela, Snk);

					dir = _getch();
					if (dir == SETA_CIMA && s.x > 5)
					{
						tela[s.x][32] = ESPACO;
						s.x--;
						tela[s.x][32] = SETINHA;
					}
					else if (dir == SETA_BAIXO && s.x < 6)
					{
						tela[s.x][32] = ESPACO;
						s.x++;
						tela[s.x][32] = SETINHA;
					}
					else if (dir == ENTER && s.x == 5)
					{
						tela[3][33] = ' ';
						tela[3][34] = ' ';
						tela[3][35] = ' ';
						tela[3][36] = ' ';
						tela[3][37] = ' ';
						tela[3][38] = ' ';
						tela[5][32] = ' ';
						tela[5][33] = ' ';
						tela[5][34] = ' ';
						tela[5][35] = ' ';
						tela[5][36] = ' ';
						tela[6][33] = ' ';
						tela[6][34] = ' ';
						tela[6][35] = ' ';
						tela[6][36] = ' ';

						saveGame(tela, Snk, m);

						pause++;
						if (Snk->n.d == DIREITA)
						{
							dir = SETA_DIREITA;
						}
						else if (Snk->n.d == ESQUERDA)
						{
							dir = SETA_ESQUERDA;
						}
						else if (Snk->n.d == CIMA)
						{
							dir = SETA_CIMA;
						}
						else if (Snk->n.d == BAIXO)
						{
							dir = SETA_BAIXO;
						}
					}
					else if (dir == ENTER && s.x == 6)
					{
						exit(0);
					}
					else if (dir == 'p')
					{
						tela[3][33] = ' ';
						tela[3][34] = ' ';
						tela[3][35] = ' ';
						tela[3][36] = ' ';
						tela[3][37] = ' ';
						tela[3][38] = ' ';
						tela[s.x][32] = ' ';
						tela[5][33] = ' ';
						tela[5][34] = ' ';
						tela[5][35] = ' ';
						tela[5][36] = ' ';
						tela[6][33] = ' ';
						tela[6][34] = ' ';
						tela[6][35] = ' ';
						tela[6][36] = ' ';
						pause++;
						if (Snk->n.d == DIREITA)
						{
							dir = SETA_DIREITA;
						}
						else if (Snk->n.d == ESQUERDA)
						{
							dir = SETA_ESQUERDA;
						}
						else if (Snk->n.d == CIMA)
						{
							dir = SETA_CIMA;
						}
						else if (Snk->n.d == BAIXO)
						{
							dir = SETA_BAIXO;
						}
					}
				}
				pause = 0;
			}
		}
		update(tela, Snk, dir, m);
		continue;
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

	tela[0][(LARGURA / 2) - 3] = 'S';
	tela[0][(LARGURA / 2) - 2] = 'C';
	tela[0][(LARGURA / 2) - 1] = 'O';
	tela[0][LARGURA / 2] = 'R';
	tela[0][(LARGURA / 2) + 1] = 'E';
	tela[0][(LARGURA / 2) + 2] = ':';
	score(tela);
}

void gerenciaCobra(char tela[ALTURA][LARGURA], Node *snk, int dir)
{
	for (Node *p = snk; p != NULL; p = p->prox)
	{
		tela[p->n.x][p->n.y] = p->n.corpo;
	}
}

void desenha(char tela[ALTURA][LARGURA], Node *Snk)
{
	int i, j;
	HANDLE hConsole;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	for (i = 0; i < ALTURA; i++)
	{
		for (j = 0; j < LARGURA; j++)
		{
			if (Snk != NULL && i == Snk->n.x && j == Snk->n.y)
			{
				SetConsoleTextAttribute(hConsole, 2);
			}
			if (i==x && j==y)
			{
				SetConsoleTextAttribute(hConsole, 3);
			}
			if (i == 0 || j == 0)
			{
				SetConsoleTextAttribute(hConsole, 6);
			}
			if (i == ALTURA - 1 || j == LARGURA - 1)
			{
				SetConsoleTextAttribute(hConsole, 6);
			}
			printf("%c", tela[i][j]);
			SetConsoleTextAttribute(hConsole, 1);
		}
		if (i != ALTURA - 1)
		{
			printf("\n");
		}
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

void mov_Snake(char tela[ALTURA][LARGURA], Node *snk, int dir, int m)
{
	Node *p = snk;

	if (p->n.d == ESQUERDA)
	{
		mov_SnakeEsquerda(tela, p, dir, m);
	}
	else if (p->n.d == CIMA)
	{
		mov_SnakeCima(tela, p, dir, m);
	}
	if (p->n.d == DIREITA)
	{
		mov_SnakeDireita(tela, p, dir, m);
	}
	else if (p->n.d == BAIXO)
	{
		mov_SnakeBaixo(tela, p, dir, m);
	}
}

void mov_SnakeEsquerda(char tela[ALTURA][LARGURA], Node *snk, int dir, int m)
{
	Node *p = snk;
	Node *aux = NULL;

	if (m == 2)
	{
		if ((tela[p->n.x][p->n.y - 1] == ESPACO || tela[p->n.x][p->n.y - 1] == FOOD) && p->n.y != 1)
		{
			tela[p->n.x][p->n.y] = ESPACO;
			p->n.y--;
			tela[p->n.x][p->n.y] = p->n.corpo;

			if (tela[p->n.x][p->n.y - 1] == FOOD)
			{
				for (aux = p; aux->prox != NULL; aux = aux->prox)
				{
					if (aux->prox == NULL)
					{
						mov_Snake(tela, p, dir, m);
						insereCorpo(tela, aux, aux->n);
						gerenciaCobra(tela, p, dir);
						food(tela);
						score(tela);
					}
				}
			}
			if (p->prox != NULL)
			{
				mov_Snake(tela, p->prox, dir, m);
				p->prox->n.d = p->n.d;
			}
		}
		else if (p->n.y == 1)
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
						mov_Snake(tela, p, dir, m);
						insereCorpo(tela, aux, aux->n);
						gerenciaCobra(tela, p, dir);
						food(tela);
						score(tela);
					}
				}
			}
			if (p->prox != NULL)
			{
				mov_Snake(tela, p->prox, dir, m);
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
	else if (m == 3)
	{
		if ((tela[p->n.x][p->n.y - 1] == ESPACO || tela[p->n.x][p->n.y - 1] == FOOD) && p->n.y != 1)
		{
			tela[p->n.x][p->n.y] = ESPACO;
			p->n.y--;
			tela[p->n.x][p->n.y] = p->n.corpo;

			if (tela[p->n.x][p->n.y - 1] == FOOD)
			{
				for (aux = p; aux->prox != NULL; aux = aux->prox)
				{
					if (aux->prox == NULL)
					{
						mov_Snake(tela, p, dir, m);
						insereCorpo(tela, aux, aux->n);
						gerenciaCobra(tela, p, dir);
						food(tela);
						score(tela);
					}
				}
			}
			if (p->prox != NULL)
			{
				mov_Snake(tela, p->prox, dir, m);
				p->prox->n.d = p->n.d;
			}
		}
		else if (p->n.y == 1)
		{
			reset(tela, p);
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
}

void mov_SnakeCima(char tela[ALTURA][LARGURA], Node *snk, int dir, int m)
{
	Node *p = snk;
	Node *aux = NULL;

	if (m == 2)
	{
		if ((tela[p->n.x - 1][p->n.y] == ESPACO || tela[p->n.x - 1][p->n.y] == FOOD) && p->n.x != 1)
		{
			tela[p->n.x][p->n.y] = ESPACO;
			p->n.x--;
			tela[p->n.x][p->n.y] = p->n.corpo;
			if (tela[p->n.x - 1][p->n.y] == FOOD)
			{
				for (aux = p; aux->prox != NULL; aux = aux->prox)
				{
					if (aux->prox == NULL)
					{
						insereCorpo(tela, aux, aux->n);
						mov_Snake(tela, p, dir, m);
						gerenciaCobra(tela, p, dir);
						food(tela);
						score(tela);
					}
				}
			}
			if (p->prox != NULL)
			{
				mov_Snake(tela, p->prox, dir, m);
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
						mov_Snake(tela, p, dir, m);
						insereCorpo(tela, aux, aux->n);
						gerenciaCobra(tela, p, dir);
						food(tela);
						score(tela);
					}
				}
			}
			if (p->prox != NULL)
			{
				mov_Snake(tela, p->prox, dir, m);
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
	else if (m == 3)
	{
		if ((tela[p->n.x - 1][p->n.y] == ESPACO || tela[p->n.x - 1][p->n.y] == FOOD) && p->n.x != 1)
		{
			tela[p->n.x][p->n.y] = ESPACO;
			p->n.x--;
			tela[p->n.x][p->n.y] = p->n.corpo;
			if (tela[p->n.x - 1][p->n.y] == FOOD)
			{
				for (aux = p; aux->prox != NULL; aux = aux->prox)
				{
					if (aux->prox == NULL)
					{
						insereCorpo(tela, aux, aux->n);
						mov_Snake(tela, p, dir, m);
						gerenciaCobra(tela, p, dir);
						food(tela);
						score(tela);
					}
				}
			}
			if (p->prox != NULL)
			{
				mov_Snake(tela, p->prox, dir, m);
				p->prox->n.d = p->n.d;
			}
		}
		else if (p->n.x == 1)
		{
			reset(tela, p);
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
}

void mov_SnakeDireita(char tela[ALTURA][LARGURA], Node *snk, int dir, int m)
{
	Node *p = snk;
	Node *aux = NULL;

	if (m == 2)
	{
		if ((tela[p->n.x][p->n.y + 1] == ESPACO || tela[p->n.x][p->n.y + 1] == FOOD) && p->n.y != LARGURA - 2)
		{
			tela[p->n.x][p->n.y] = ESPACO;
			p->n.y++;
			tela[p->n.x][p->n.y] = p->n.corpo;
			if (tela[p->n.x][p->n.y + 1] == FOOD)
			{
				for (aux = p; aux->prox != NULL; aux = aux->prox)
				{
					if (aux->prox == NULL)
					{
						mov_Snake(tela, p, dir, m);
						insereCorpo(tela, aux, aux->n);
						gerenciaCobra(tela, p, dir);
						food(tela);
						score(tela);
					}
				}
			}
			if (p->prox != NULL)
			{
				mov_Snake(tela, p->prox, dir, m);
				p->prox->n.d = p->n.d;
			}
		}
		else if (p->n.y == LARGURA - 2)
		{
			tela[p->n.x][p->n.y] = ESPACO;
			p->n.y = 1;
			tela[p->n.x][p->n.y] = p->n.corpo;

			if (tela[p->n.x][p->n.y + 1] == FOOD)
			{
				for (aux = p; aux->prox != NULL; aux = aux->prox)
				{
					if (aux->n.y >= 1 && aux->prox == NULL)
					{
						mov_Snake(tela, p, dir, m);
						insereCorpo(tela, aux, aux->n);
						gerenciaCobra(tela, p, dir);
						food(tela);
						score(tela);
					}
				}
			}
			if (p->prox != NULL)
			{
				mov_Snake(tela, p->prox, dir, m);
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
	else if (m == 3)
	{
		if ((tela[p->n.x][p->n.y + 1] == ESPACO || tela[p->n.x][p->n.y + 1] == FOOD) && p->n.y != LARGURA - 2)
		{
			tela[p->n.x][p->n.y] = ESPACO;
			p->n.y++;
			tela[p->n.x][p->n.y] = p->n.corpo;
			if (tela[p->n.x][p->n.y + 1] == FOOD)
			{
				for (aux = p; aux->prox != NULL; aux = aux->prox)
				{
					if (aux->prox == NULL)
					{
						mov_Snake(tela, p, dir, m);
						insereCorpo(tela, aux, aux->n);
						gerenciaCobra(tela, p, dir);
						food(tela);
						score(tela);
					}
				}
			}
			if (p->prox != NULL)
			{
				mov_Snake(tela, p->prox, dir, m);
				p->prox->n.d = p->n.d;
			}
		}
		else if (p->n.y == LARGURA - 2)
		{
			reset(tela, p);
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
}

void mov_SnakeBaixo(char tela[ALTURA][LARGURA], Node *snk, int dir, int m)
{
	Node *p = snk;
	Node *aux = NULL;

	if (m == 2)
	{
		if ((tela[p->n.x + 1][p->n.y] == ESPACO || tela[p->n.x + 1][p->n.y] == FOOD) && p->n.x != ALTURA - 2)
		{
			tela[p->n.x][p->n.y] = ESPACO;
			p->n.x++;
			tela[p->n.x][p->n.y] = p->n.corpo;
			if (tela[p->n.x + 1][p->n.y] == FOOD)
			{
				for (aux = p; aux->prox != NULL; aux = aux->prox)
				{
					if (aux->prox == NULL)
					{
						insereCorpo(tela, aux, aux->n);
						mov_Snake(tela, p, dir, m);
						gerenciaCobra(tela, p, dir);
						food(tela);
						score(tela);
					}
				}
			}
			if (p->prox != NULL)
			{
				mov_Snake(tela, p->prox, dir, m);
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
						mov_Snake(tela, p, dir, m);
						insereCorpo(tela, aux, aux->n);
						gerenciaCobra(tela, p, dir);
						food(tela);
						score(tela);
					}
				}
			}
			if (p->prox != NULL)
			{
				mov_Snake(tela, p->prox, dir, m);
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
	else if (m == 3)
	{
		if ((tela[p->n.x + 1][p->n.y] == ESPACO || tela[p->n.x + 1][p->n.y] == FOOD) && p->n.x != ALTURA - 2)
		{
			tela[p->n.x][p->n.y] = ESPACO;
			p->n.x++;
			tela[p->n.x][p->n.y] = p->n.corpo;
			if (tela[p->n.x + 1][p->n.y] == FOOD)
			{
				for (aux = p; aux->prox != NULL; aux = aux->prox)
				{
					if (aux->prox == NULL)
					{
						insereCorpo(tela, aux, aux->n);
						mov_Snake(tela, p, dir, m);
						gerenciaCobra(tela, p, dir);
						food(tela);
						score(tela);
					}
				}
			}
			if (p->prox != NULL)
			{
				mov_Snake(tela, p->prox, dir, m);
				p->prox->n.d = p->n.d;
			}
		}
		else if (p->n.x == ALTURA - 2)
		{
			reset(tela, p);
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
}

void food(char tela[ALTURA][LARGURA])
{
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

	placar(tela);

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
	desenha(tela, snk);
	c = _getch();

	if (c == 's' || c == 'S')
	{
		unidade = '0';
		dezena = '0';
		centena = '0';
		free(snk);
		main(1);
	}
	else if (c == 'n' || c == 'N')
	{
		free(snk);
		exit(0);
	}
	else
	{
		reset(tela, snk);
	}
}

void update(char tela[ALTURA][LARGURA], Node *snk, int dir, int m)
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
			mov_Snake(tela, p, dir, m);
			gerenciaCobra(tela, p, dir);
			food(tela);
			score(tela);
		}
		else
		{
			p->n.d = ESQUERDA;
			mov_Snake(tela, p, dir, m);
		}
	}
	else if (dir == SETA_CIMA)
	{
		if (tela[p->n.x - 1][p->n.y] == FOOD)
		{
			for (aux = p; aux->prox != NULL; aux = aux->prox);
			insereCorpo(tela, aux, aux->n);
			p->n.d = CIMA;
			mov_Snake(tela, p, dir, m);
			gerenciaCobra(tela, p, dir);
			food(tela);
			score(tela);
		}
		else
		{
			p->n.d = CIMA;
			mov_Snake(tela, p, dir, m);
		}
	}
	else if (dir == SETA_DIREITA)
	{
		if (tela[p->n.x][p->n.y + 1] == FOOD)
		{
			for (aux = p; aux->prox != NULL; aux = aux->prox);
			insereCorpo(tela, aux, aux->n);
			p->n.d = DIREITA;
			mov_Snake(tela, p, dir, m);
			gerenciaCobra(tela, p, dir);
			food(tela);
			score(tela);
		}
		else
		{
			p->n.d = DIREITA;
			mov_Snake(tela, p, dir, m);
		}
	}
	else if (dir == SETA_BAIXO)
	{
		if (tela[p->n.x + 1][p->n.y] == FOOD)
		{
			for (aux = p; aux->prox != NULL; aux = aux->prox);
			insereCorpo(tela, aux, aux->n);
			p->n.d = BAIXO;
			mov_Snake(tela, p, dir, m);
			gerenciaCobra(tela, p, dir);
			food(tela);
			score(tela);
		}
		else
		{
			p->n.d = BAIXO;
			mov_Snake(tela, p, dir, m);
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

	if (unidade <= '9' && dezena <= '9' && centena <= '9')
	{
		if (unidade == '0')
		{
			unidade++;
			for (i = 0; i < 3; i++)
			{
				if (i == 0)
				{
					s[i] = centena;
				}
				if (i == 1)
				{
					s[i] = dezena;
				}
				if (i == 2)
				{
					s[i] = unidade;
				}
			}
			for (i = 0; i < 3; i++)
			{
				tela[0][(LARGURA / 2) + 3 + i] = s[i];
			}
		}
		else if (dezena == '9' && unidade == '9')
		{
			centena++;
			dezena = '0';
			unidade = '0';
			for (i = 0; i < 3; i++)
			{
				if (i == 0)
				{
					s[i] = centena;
				}
				if (i == 1)
				{
					s[i] = dezena;
				}
				if (i == 2)
				{
					s[i] = unidade;
				}
			}
			for (i = 0; i < 3; i++)
			{
				tela[0][(LARGURA / 2) + 3 + i] = s[i];
			}
		}
		else if (unidade == '9')
		{
			dezena++;
			unidade = '0';
			for (i = 0; i < 3; i++)
			{
				if (i == 0)
				{
					s[i] = centena;
				}
				if (i == 1)
				{
					s[i] = dezena;
				}
				if (i == 2)
				{
					s[i] = unidade;
				}
			}
			for (i = 0; i < 3; i++)
			{
				tela[0][(LARGURA / 2) + 3 + i] = s[i];
			}
		}
		else if (unidade > '0' && unidade < '9')
		{
			unidade++;
			for (i = 0; i < 3; i++)
			{
				if (i == 0)
				{
					s[i] = centena;
				}
				if (i == 1)
				{
					s[i] = dezena;
				}
				if (i == 2)
				{
					s[i] = unidade;
				}
			}
			for (i = 0; i < 3; i++)
			{
				tela[0][(LARGURA / 2) + 3 + i] = s[i];
			}
		}
		else if (dezena > '0' && dezena < '9')
		{
			unidade++;
			for (i = 0; i < 3; i++)
			{
				if (i == 0)
				{
					s[i] = centena;
				}
				if (i == 1)
				{
					s[i] = dezena;
				}
				if (i == 2)
				{
					s[i] = unidade;
				}
			}
			for (i = 0; i < 3; i++)
			{
				tela[0][(LARGURA / 2) + 3 + i] = s[i];
			}
		}
	}
}

FILE *menuInicial(char tela[ALTURA][LARGURA], Node *snk, int *m)
{
	int i, j;
	Seta s;
	FILE *save = NULL;

	for (i = 0; i < ALTURA; i += (ALTURA - 1))
	{
		for (j = 0; j < LARGURA; j++)
		{
			tela[i][j] = HORIZONTAL;
		}
	}
	for (i = 0; i < ALTURA - 1; i++)
	{
		for (j = 0; j < LARGURA; j += (LARGURA - 1))
		{
			tela[i][j] = VERTICAL;
		}
	}
	for (i = 1; i < ALTURA - 1; i++)
	{
		for (j = 1; j < LARGURA - 1; j++)
		{
			tela[i][j] = ESPACO;
		}
	}

	tela[0][0] = SUPERIOR_ESQUERDO;
	tela[0][LARGURA - 1] = SUPERIOR_DIREITO;
	tela[ALTURA - 1][0] = INFERIOR_ESQUERDO;
	tela[ALTURA - 1][LARGURA - 1] = INFERIOR_DIREITO;

	//------------S---- --N----------------------------------------------   	-----A--------------------------------------------------------------------------------------------------------------------------------------------------------------------
	tela[3][5] = TT; tela[3][10] = TT; tela[3][11] = TT; tela[3][22] = TT;		tela[3][30] = TT;
	tela[3][6] = TT; tela[4][10] = TT; tela[4][12] = TT; tela[4][22] = TT;		tela[4][29] = TT; tela[4][31] = TT;
	tela[3][7] = TT; tela[5][10] = TT; tela[5][13] = TT; tela[5][22] = TT;		tela[5][28] = TT; tela[5][32] = TT;
	tela[4][4] = TT; tela[6][10] = TT; tela[6][14] = TT; tela[6][22] = TT;		tela[6][27] = TT; tela[6][33] = TT;
	tela[5][3] = TT; tela[7][10] = TT; tela[7][15] = TT; tela[7][22] = TT;		tela[7][26] = TT; tela[7][34] = TT;
	tela[6][3] = TT; tela[8][10] = TT; tela[8][16] = TT; tela[8][22] = TT;		tela[8][26] = TT; tela[8][27] = TT; tela[8][28] = TT; tela[8][29] = TT; tela[8][30] = TT; tela[8][31] = TT; tela[8][32] = TT; tela[8][33] = TT; tela[8][34] = TT;
	tela[7][4] = TT; tela[9][10] = TT; tela[9][17] = TT; tela[9][22] = TT;		tela[9][25] = TT; tela[9][35] = TT;
	tela[8][5] = TT; tela[10][10] = TT; tela[10][18] = TT; tela[10][22] = TT;	tela[10][25] = TT; tela[10][35] = TT;
	tela[8][6] = TT; tela[11][10] = TT; tela[11][19] = TT; tela[11][22] = TT;	tela[11][24] = TT; tela[11][36] = TT;
	tela[9][6] = TY; tela[12][10] = TT; tela[12][20] = TT; tela[12][22] = TT;	tela[12][24] = TT; tela[12][36] = TT;
	tela[9][7] = TT; tela[13][10] = TT; tela[13][21] = TT; tela[13][22] = TT;	tela[13][24] = TT; tela[13][36] = TT;
	tela[10][8] = TT; tela[4][11] = TY;	tela[4][9] = TY;						tela[13][23] = TY;					tela[13][35] = TY;
	tela[10][7] = TY; tela[5][12] = TY; tela[5][9] = TY;						tela[12][23] = TY;					tela[12][35] = TY;
	tela[11][8] = TT; tela[6][13] = TY; tela[6][9] = TY; tela[4][21] = TY;		tela[11][23] = TY;					tela[11][35] = TY;
	tela[11][7] = TY; tela[7][14] = TY; tela[7][9] = TY; tela[5][21] = TY;		tela[10][24] = TY;					tela[10][34] = TY;
	tela[12][7] = TT; tela[8][15] = TY; tela[8][9] = TY; tela[6][21] = TY;		tela[9][24] = TY; tela[8][25] = TY; tela[9][34] = TY; tela[9][33] = TY;
	tela[12][6] = TY; tela[9][16] = TY; tela[9][9] = TY; tela[7][21] = TY;		tela[7][25] = TY;					tela[7][33] = TY;
	tela[13][6] = TT; tela[10][17] = TY; tela[10][9] = TY; tela[8][21] = TY;	tela[6][26] = TY;					tela[6][32] = TY;
	tela[13][5] = TT; tela[11][18] = TY; tela[11][9] = TY; tela[9][21] = TY;	tela[5][27] = TY;					tela[5][31] = TY;
	tela[13][4] = TT; tela[12][19] = TY; tela[12][9] = TY; tela[10][21] = TY;	tela[4][28] = TY;					tela[4][30] = TY;
	tela[4][3] = TY; tela[13][20] = TY; tela[13][9] = TY; tela[11][21] = TY;	tela[3][29] = TY;
	tela[5][2] = TY;									   tela[12][21] = TY;
	tela[6][2] = TY; tela[7][3] = TY;
	tela[13][3] = TY;

	//-------K-------
	tela[3][38] = TT; tela[3][45] = TT;
	tela[4][38] = TT; tela[4][44] = TT;
	tela[5][38] = TT; tela[5][43] = TT;
	tela[6][38] = TT; tela[6][42] = TT;
	tela[7][38] = TT; tela[7][41] = TT;
	tela[8][38] = TT; tela[8][39] = TT; tela[8][40] = TT;
	tela[9][38] = TT; tela[9][41] = TT;
	tela[10][38] = TT; tela[10][42] = TT;
	tela[11][38] = TT; tela[11][43] = TT;
	tela[12][38] = TT; tela[12][44] = TT;
	tela[13][38] = TT; tela[13][45] = TT;

	tela[4][37] = TY;
	tela[5][37] = TY;
	tela[6][37] = TY;
	tela[7][37] = TY;
	tela[8][37] = TY;
	tela[9][37] = TY; tela[9][40] = TY;
	tela[10][37] = TY; tela[10][41] = TY;
	tela[11][37] = TY; tela[11][42] = TY;
	tela[12][37] = TY; tela[12][43] = TY;
	tela[13][37] = TY; tela[13][44] = TY;

	//-------E-------
	tela[3][47] = TT; tela[3][48] = TT; tela[3][49] = TT; tela[3][50] = TT; tela[3][51] = TT; tela[3][52] = TT; tela[3][53] = TT;
	tela[4][47] = TT;
	tela[5][47] = TT;
	tela[6][47] = TT;
	tela[7][47] = TT;
	tela[8][47] = TT; tela[8][48] = TT; tela[8][49] = TT; tela[8][50] = TT;
	tela[9][47] = TT;
	tela[10][47] = TT;
	tela[11][47] = TT;
	tela[12][47] = TT;
	tela[13][47] = TT; tela[13][48] = TT; tela[13][49] = TT; tela[13][50] = TT; tela[13][51] = TT; tela[13][52] = TT; tela[13][53] = TT;

	tela[4][46] = TY; tela[4][48] = TY; tela[4][49] = TY; tela[4][50] = TY; tela[4][51] = TY; tela[4][52] = TY; tela[4][53] = TY;
	tela[5][46] = TY;
	tela[6][46] = TY;
	tela[7][46] = TY;
	tela[8][46] = TY;
	tela[9][46] = TY; tela[9][48] = TY; tela[9][49] = TY; tela[9][50] = TY;
	tela[10][46] = TY;
	tela[11][46] = TY;
	tela[12][46] = TY;
	tela[13][46] = TY;

	tela[17][27] = SETINHA;
	s.x = 17;

	tela[17][28] = 'N';
	tela[17][29] = 'e';
	tela[17][30] = 'w';
	tela[17][31] = ' ';
	tela[17][32] = 'G';
	tela[17][33] = 'a';
	tela[17][34] = 'm';
	tela[17][35] = 'e';

	tela[18][28] = 'L';
	tela[18][29] = 'o';
	tela[18][30] = 'a';
	tela[18][31] = 'd';
	tela[18][32] = ' ';
	tela[18][33] = 'G';
	tela[18][34] = 'a';
	tela[18][35] = 'm';
	tela[18][36] = 'e';


	tela[20][50] = 'F';
	tela[20][51] = 'e';
	tela[20][52] = 'l';
	tela[20][53] = 'i';
	tela[20][54] = 'p';
	tela[20][55] = 'e';
	tela[20][56] = ' ';
	tela[20][57] = 'V';
	tela[20][58] = ' ';
	tela[20][59] = 'M';
	tela[20][60] = 'a';
	tela[20][61] = 't';
	tela[20][62] = 'h';
	tela[20][63] = 'i';
	tela[20][64] = 'e';
	tela[20][65] = 'u';

	tela[21][50] = 'V';
	tela[21][51] = 'i';
	tela[21][52] = 'n';
	tela[21][53] = 'i';
	tela[21][54] = 'c';
	tela[21][55] = 'i';
	tela[21][56] = 'o';
	tela[21][57] = 's';
	tela[21][58] = ' ';
	tela[21][59] = 'C';
	tela[21][60] = 'o';
	tela[21][61] = 'e';
	tela[21][62] = 'l';
	tela[21][63] = 'h';
	tela[21][64] = 'o';

	tela[19][28] = 'Q';
	tela[19][29] = 'u';
	tela[19][30] = 'i';
	tela[19][31] = 't';

	while (*m != ENTER)
	{
		COORD cord;
		cord.X = 0;
		cord.Y = 0;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
		desenha(tela, snk);

		if (_kbhit())
		{
			*m = _getch();

			if (*m == SETA_CIMA && s.x > 17)
			{
				tela[s.x][27] = ESPACO;
				s.x--;
				tela[s.x][27] = SETINHA;
			}
			else if (*m == SETA_BAIXO && s.x < 19)
			{
				tela[s.x][27] = ESPACO;
				s.x++;
				tela[s.x][27] = SETINHA;
			}
		}
	}

	if (*m == ENTER && s.x == 17)
	{
		*m = menuDificuldade(tela, snk);
		save = NULL;
	}
	else if (*m == ENTER && s.x == 18)
	{
		save = menuLoad(tela, snk, m);
	}
	else if (*m == ENTER && s.x == 19)
	{
		exit(0);
	}

	return save;
}

int menuDificuldade(char tela[ALTURA][LARGURA], Node *snk)
{
	int i, j, m = 0;
	Seta s;

	for (i = 0; i < ALTURA; i += (ALTURA - 1))
	{
		for (j = 0; j < LARGURA; j++)
		{
			tela[i][j] = HORIZONTAL;

		}
	}
	for (i = 0; i < ALTURA - 1; i++)
	{
		for (j = 0; j < LARGURA; j += (LARGURA - 1))
		{
			tela[i][j] = VERTICAL;
		}
	}
	for (i = 1; i < ALTURA - 1; i++)
	{
		for (j = 1; j < LARGURA - 1; j++)
		{
			tela[i][j] = ESPACO;
		}
	}

	tela[0][0] = SUPERIOR_ESQUERDO;
	tela[0][LARGURA - 1] = SUPERIOR_DIREITO;
	tela[ALTURA - 1][0] = INFERIOR_ESQUERDO;
	tela[ALTURA - 1][LARGURA - 1] = INFERIOR_DIREITO;

	//------------S---- --N----------------------------------------------   	-----A--------------------------------------------------------------------------------------------------------------------------------------------------------------------
	tela[3][5] = TT; tela[3][10] = TT; tela[3][11] = TT; tela[3][22] = TT;		tela[3][30] = TT;
	tela[3][6] = TT; tela[4][10] = TT; tela[4][12] = TT; tela[4][22] = TT;		tela[4][29] = TT; tela[4][31] = TT;
	tela[3][7] = TT; tela[5][10] = TT; tela[5][13] = TT; tela[5][22] = TT;		tela[5][28] = TT; tela[5][32] = TT;
	tela[4][4] = TT; tela[6][10] = TT; tela[6][14] = TT; tela[6][22] = TT;		tela[6][27] = TT; tela[6][33] = TT;
	tela[5][3] = TT; tela[7][10] = TT; tela[7][15] = TT; tela[7][22] = TT;		tela[7][26] = TT; tela[7][34] = TT;
	tela[6][3] = TT; tela[8][10] = TT; tela[8][16] = TT; tela[8][22] = TT;		tela[8][26] = TT; tela[8][27] = TT; tela[8][28] = TT; tela[8][29] = TT; tela[8][30] = TT; tela[8][31] = TT; tela[8][32] = TT; tela[8][33] = TT; tela[8][34] = TT;
	tela[7][4] = TT; tela[9][10] = TT; tela[9][17] = TT; tela[9][22] = TT;		tela[9][25] = TT; tela[9][35] = TT;
	tela[8][5] = TT; tela[10][10] = TT; tela[10][18] = TT; tela[10][22] = TT;	tela[10][25] = TT; tela[10][35] = TT;
	tela[8][6] = TT; tela[11][10] = TT; tela[11][19] = TT; tela[11][22] = TT;	tela[11][24] = TT; tela[11][36] = TT;
	tela[9][6] = TY; tela[12][10] = TT; tela[12][20] = TT; tela[12][22] = TT;	tela[12][24] = TT; tela[12][36] = TT;
	tela[9][7] = TT; tela[13][10] = TT; tela[13][21] = TT; tela[13][22] = TT;	tela[13][24] = TT; tela[13][36] = TT;
	tela[10][8] = TT; tela[4][11] = TY;	tela[4][9] = TY;						tela[13][23] = TY;					tela[13][35] = TY;
	tela[10][7] = TY; tela[5][12] = TY; tela[5][9] = TY;						tela[12][23] = TY;					tela[12][35] = TY;
	tela[11][8] = TT; tela[6][13] = TY; tela[6][9] = TY; tela[4][21] = TY;		tela[11][23] = TY;					tela[11][35] = TY;
	tela[11][7] = TY; tela[7][14] = TY; tela[7][9] = TY; tela[5][21] = TY;		tela[10][24] = TY;					tela[10][34] = TY;
	tela[12][7] = TT; tela[8][15] = TY; tela[8][9] = TY; tela[6][21] = TY;		tela[9][24] = TY; tela[8][25] = TY; tela[9][34] = TY; tela[9][33] = TY;
	tela[12][6] = TY; tela[9][16] = TY; tela[9][9] = TY; tela[7][21] = TY;		tela[7][25] = TY;					tela[7][33] = TY;
	tela[13][6] = TT; tela[10][17] = TY; tela[10][9] = TY; tela[8][21] = TY;	tela[6][26] = TY;					tela[6][32] = TY;
	tela[13][5] = TT; tela[11][18] = TY; tela[11][9] = TY; tela[9][21] = TY;	tela[5][27] = TY;					tela[5][31] = TY;
	tela[13][4] = TT; tela[12][19] = TY; tela[12][9] = TY; tela[10][21] = TY;	tela[4][28] = TY;					tela[4][30] = TY;
	tela[4][3] = TY; tela[13][20] = TY; tela[13][9] = TY; tela[11][21] = TY;	tela[3][29] = TY;
	tela[5][2] = TY;									   tela[12][21] = TY;
	tela[6][2] = TY; tela[7][3] = TY;
	tela[13][3] = TY;

	//-------K-------
	tela[3][38] = TT; tela[3][45] = TT;
	tela[4][38] = TT; tela[4][44] = TT;
	tela[5][38] = TT; tela[5][43] = TT;
	tela[6][38] = TT; tela[6][42] = TT;
	tela[7][38] = TT; tela[7][41] = TT;
	tela[8][38] = TT; tela[8][39] = TT; tela[8][40] = TT;
	tela[9][38] = TT; tela[9][41] = TT;
	tela[10][38] = TT; tela[10][42] = TT;
	tela[11][38] = TT; tela[11][43] = TT;
	tela[12][38] = TT; tela[12][44] = TT;
	tela[13][38] = TT; tela[13][45] = TT;

	tela[4][37] = TY;
	tela[5][37] = TY;
	tela[6][37] = TY;
	tela[7][37] = TY;
	tela[8][37] = TY;
	tela[9][37] = TY; tela[9][40] = TY;
	tela[10][37] = TY; tela[10][41] = TY;
	tela[11][37] = TY; tela[11][42] = TY;
	tela[12][37] = TY; tela[12][43] = TY;
	tela[13][37] = TY; tela[13][44] = TY;

	//-------E-------
	tela[3][47] = TT; tela[3][48] = TT; tela[3][49] = TT; tela[3][50] = TT; tela[3][51] = TT; tela[3][52] = TT; tela[3][53] = TT;
	tela[4][47] = TT;
	tela[5][47] = TT;
	tela[6][47] = TT;
	tela[7][47] = TT;
	tela[8][47] = TT; tela[8][48] = TT; tela[8][49] = TT; tela[8][50] = TT;
	tela[9][47] = TT;
	tela[10][47] = TT;
	tela[11][47] = TT;
	tela[12][47] = TT;
	tela[13][47] = TT; tela[13][48] = TT; tela[13][49] = TT; tela[13][50] = TT; tela[13][51] = TT; tela[13][52] = TT; tela[13][53] = TT;

	tela[4][46] = TY; tela[4][48] = TY; tela[4][49] = TY; tela[4][50] = TY; tela[4][51] = TY; tela[4][52] = TY; tela[4][53] = TY;
	tela[5][46] = TY;
	tela[6][46] = TY;
	tela[7][46] = TY;
	tela[8][46] = TY;
	tela[9][46] = TY; tela[9][48] = TY; tela[9][49] = TY; tela[9][50] = TY;
	tela[10][46] = TY;
	tela[11][46] = TY;
	tela[12][46] = TY;
	tela[13][46] = TY;

	tela[17][27] = SETINHA;
	s.x = 17;

	tela[17][28] = 'M';
	tela[17][29] = 'e';
	tela[17][30] = 'd';
	tela[17][31] = 'i';
	tela[17][32] = 'u';
	tela[17][33] = 'm';

	tela[18][28] = 'H';
	tela[18][29] = 'a';
	tela[18][30] = 'r';
	tela[18][31] = 'd';

	tela[19][28] = 'Q';
	tela[19][29] = 'u';
	tela[19][30] = 'i';
	tela[19][31] = 't';

	while (m != ENTER)
	{
		COORD cord;
		cord.X = 0;
		cord.Y = 0;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
		desenha(tela, snk);

		if (_kbhit())
		{
			m = _getch();
			if (m == SETA_CIMA && s.x > 17)
			{
				tela[s.x][27] = ESPACO;
				s.x--;
				tela[s.x][27] = SETINHA;
			}
			else if (m == SETA_BAIXO && s.x < 19)
			{
				tela[s.x][27] = ESPACO;
				s.x++;
				tela[s.x][27] = SETINHA;
			}
		}
	}
	if (m == ENTER && s.x == 17)
	{
		m = 2;
	}
	else if (m == ENTER && s.x == 18)
	{
		m = 3;
	}
	else if (m == ENTER && s.x == 19)
	{
		exit(0);
	}

	return m;
}

FILE *menuLoad(char tela[ALTURA][LARGURA], Node *snk, int *m)
{
	FILE *load = fopen("save.txt", "r");
	Seta s;
	int i, j;

	if (load == NULL)
	{
		for (i = 0; i < ALTURA; i += (ALTURA - 1))
		{
			for (j = 0; j < LARGURA; j++)
			{
				tela[i][j] = HORIZONTAL;

			}
		}
		for (i = 0; i < ALTURA - 1; i++)
		{
			for (j = 0; j < LARGURA; j += (LARGURA - 1))
			{
				tela[i][j] = VERTICAL;
			}
		}
		for (i = 1; i < ALTURA - 1; i++)
		{
			for (j = 1; j < LARGURA - 1; j++)
			{
				tela[i][j] = ESPACO;
			}
		}

		tela[0][0] = SUPERIOR_ESQUERDO;
		tela[0][LARGURA - 1] = SUPERIOR_DIREITO;
		tela[ALTURA - 1][0] = INFERIOR_ESQUERDO;
		tela[ALTURA - 1][LARGURA - 1] = INFERIOR_DIREITO;

		//------------S---- --N----------------------------------------------   	-----A--------------------------------------------------------------------------------------------------------------------------------------------------------------------
		tela[3][5] = TT; tela[3][10] = TT; tela[3][11] = TT; tela[3][22] = TT;		tela[3][30] = TT;
		tela[3][6] = TT; tela[4][10] = TT; tela[4][12] = TT; tela[4][22] = TT;		tela[4][29] = TT; tela[4][31] = TT;
		tela[3][7] = TT; tela[5][10] = TT; tela[5][13] = TT; tela[5][22] = TT;		tela[5][28] = TT; tela[5][32] = TT;
		tela[4][4] = TT; tela[6][10] = TT; tela[6][14] = TT; tela[6][22] = TT;		tela[6][27] = TT; tela[6][33] = TT;
		tela[5][3] = TT; tela[7][10] = TT; tela[7][15] = TT; tela[7][22] = TT;		tela[7][26] = TT; tela[7][34] = TT;
		tela[6][3] = TT; tela[8][10] = TT; tela[8][16] = TT; tela[8][22] = TT;		tela[8][26] = TT; tela[8][27] = TT; tela[8][28] = TT; tela[8][29] = TT; tela[8][30] = TT; tela[8][31] = TT; tela[8][32] = TT; tela[8][33] = TT; tela[8][34] = TT;
		tela[7][4] = TT; tela[9][10] = TT; tela[9][17] = TT; tela[9][22] = TT;		tela[9][25] = TT; tela[9][35] = TT;
		tela[8][5] = TT; tela[10][10] = TT; tela[10][18] = TT; tela[10][22] = TT;	tela[10][25] = TT; tela[10][35] = TT;
		tela[8][6] = TT; tela[11][10] = TT; tela[11][19] = TT; tela[11][22] = TT;	tela[11][24] = TT; tela[11][36] = TT;
		tela[9][6] = TY; tela[12][10] = TT; tela[12][20] = TT; tela[12][22] = TT;	tela[12][24] = TT; tela[12][36] = TT;
		tela[9][7] = TT; tela[13][10] = TT; tela[13][21] = TT; tela[13][22] = TT;	tela[13][24] = TT; tela[13][36] = TT;
		tela[10][8] = TT; tela[4][11] = TY;	tela[4][9] = TY;						tela[13][23] = TY;					tela[13][35] = TY;
		tela[10][7] = TY; tela[5][12] = TY; tela[5][9] = TY;						tela[12][23] = TY;					tela[12][35] = TY;
		tela[11][8] = TT; tela[6][13] = TY; tela[6][9] = TY; tela[4][21] = TY;		tela[11][23] = TY;					tela[11][35] = TY;
		tela[11][7] = TY; tela[7][14] = TY; tela[7][9] = TY; tela[5][21] = TY;		tela[10][24] = TY;					tela[10][34] = TY;
		tela[12][7] = TT; tela[8][15] = TY; tela[8][9] = TY; tela[6][21] = TY;		tela[9][24] = TY; tela[8][25] = TY; tela[9][34] = TY; tela[9][33] = TY;
		tela[12][6] = TY; tela[9][16] = TY; tela[9][9] = TY; tela[7][21] = TY;		tela[7][25] = TY;					tela[7][33] = TY;
		tela[13][6] = TT; tela[10][17] = TY; tela[10][9] = TY; tela[8][21] = TY;	tela[6][26] = TY;					tela[6][32] = TY;
		tela[13][5] = TT; tela[11][18] = TY; tela[11][9] = TY; tela[9][21] = TY;	tela[5][27] = TY;					tela[5][31] = TY;
		tela[13][4] = TT; tela[12][19] = TY; tela[12][9] = TY; tela[10][21] = TY;	tela[4][28] = TY;					tela[4][30] = TY;
		tela[4][3] = TY; tela[13][20] = TY; tela[13][9] = TY; tela[11][21] = TY;	tela[3][29] = TY;
		tela[5][2] = TY;									   tela[12][21] = TY;
		tela[6][2] = TY; tela[7][3] = TY;
		tela[13][3] = TY;

		//-------K-------
		tela[3][38] = TT; tela[3][45] = TT;
		tela[4][38] = TT; tela[4][44] = TT;
		tela[5][38] = TT; tela[5][43] = TT;
		tela[6][38] = TT; tela[6][42] = TT;
		tela[7][38] = TT; tela[7][41] = TT;
		tela[8][38] = TT; tela[8][39] = TT; tela[8][40] = TT;
		tela[9][38] = TT; tela[9][41] = TT;
		tela[10][38] = TT; tela[10][42] = TT;
		tela[11][38] = TT; tela[11][43] = TT;
		tela[12][38] = TT; tela[12][44] = TT;
		tela[13][38] = TT; tela[13][45] = TT;

		tela[4][37] = TY;
		tela[5][37] = TY;
		tela[6][37] = TY;
		tela[7][37] = TY;
		tela[8][37] = TY;
		tela[9][37] = TY; tela[9][40] = TY;
		tela[10][37] = TY; tela[10][41] = TY;
		tela[11][37] = TY; tela[11][42] = TY;
		tela[12][37] = TY; tela[12][43] = TY;
		tela[13][37] = TY; tela[13][44] = TY;

		//-------E-------
		tela[3][47] = TT; tela[3][48] = TT; tela[3][49] = TT; tela[3][50] = TT; tela[3][51] = TT; tela[3][52] = TT; tela[3][53] = TT;
		tela[4][47] = TT;
		tela[5][47] = TT;
		tela[6][47] = TT;
		tela[7][47] = TT;
		tela[8][47] = TT; tela[8][48] = TT; tela[8][49] = TT; tela[8][50] = TT;
		tela[9][47] = TT;
		tela[10][47] = TT;
		tela[11][47] = TT;
		tela[12][47] = TT;
		tela[13][47] = TT; tela[13][48] = TT; tela[13][49] = TT; tela[13][50] = TT; tela[13][51] = TT; tela[13][52] = TT; tela[13][53] = TT;

		tela[4][46] = TY; tela[4][48] = TY; tela[4][49] = TY; tela[4][50] = TY; tela[4][51] = TY; tela[4][52] = TY; tela[4][53] = TY;
		tela[5][46] = TY;
		tela[6][46] = TY;
		tela[7][46] = TY;
		tela[8][46] = TY;
		tela[9][46] = TY; tela[9][48] = TY; tela[9][49] = TY; tela[9][50] = TY;
		tela[10][46] = TY;
		tela[11][46] = TY;
		tela[12][46] = TY;
		tela[13][46] = TY;

		tela[17][28] = 'N';
		tela[17][29] = 'a';
		tela[17][30] = 'o';
		tela[17][31] = ' ';
		tela[17][32] = 'e';
		tela[17][33] = 'x';
		tela[17][34] = 'i';
		tela[17][35] = 's';
		tela[17][36] = 't';
		tela[17][37] = 'e';
		tela[17][38] = ' ';
		tela[17][39] = 's';
		tela[17][40] = 'a';
		tela[17][41] = 'v';
		tela[17][42] = 'e';

		tela[18][28] = 'N';
		tela[18][29] = 'e';
		tela[18][30] = 'w';
		tela[18][31] = ' ';
		tela[18][32] = 'G';
		tela[18][33] = 'a';
		tela[18][34] = 'm';
		tela[18][35] = 'e';

		tela[19][28] = 'Q';
		tela[19][29] = 'u';
		tela[19][30] = 'i';
		tela[19][31] = 't';

		tela[18][27] = SETINHA;
		s.x = 18;

		while (*m != ENTER)
		{
			COORD cord;
			cord.X = 0;
			cord.Y = 0;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
			desenha(tela, snk);

			if (_kbhit())
			{
				*m = _getch();
			}
			if (*m == SETA_CIMA && s.x > 18)
			{
				tela[s.x][27] = ESPACO;
				s.x--;
				tela[s.x][27] = SETINHA;
			}
			else if (*m == SETA_BAIXO && s.x < 19)
			{
				tela[s.x][27] = ESPACO;
				s.x++;
				tela[s.x][27] = SETINHA;
			}
		}
		if (*m == ENTER && s.x == 18)
		{
			*m = menuDificuldade(tela, snk);
		}
		else if (*m == ENTER && s.x == 19)
		{
			exit(0);
		}
	}
	else
	{
		for (i = 0; i < ALTURA; i++)
		{
			for (j = 0; j < LARGURA; j++)
			{
				tela[i][j] = fgetc(load);

				if (tela[i][j] >= '0' && tela[i][j] <= '9')
				{
					if (tela[i][j - 2] >= '0' && tela[i][j - 2] <= '9' && tela[i][j - 1] >= '0' && tela[i][j - 1] <= '9')
					{
						unidade = tela[i][j];
						unidade--;
					}
					else if (tela[i][j - 1] >= '0' && tela[i][j - 1] <= '9')
					{
						dezena = tela[i][j];
					}
					else
					{
						centena = tela[i][j];
					}
				}
			}
			tela[i][j] = fgetc(load);
		}
		fscanf(load, "%d", m);
	}

	return load;
}

void saveGame(char tela[ALTURA][LARGURA], Node *snk, int m)
{
	FILE *save;
	Node *p;
	int i, j;

	save = fopen("save.txt", "w");

	if (save == NULL)
	{
		printf("ERRO! Nao foi possivel criar um save.\n");
		system("pause");
		exit(0);
	}
	else
	{
		for (i = 0; i < ALTURA; i++)
		{
			for (j = 0; j < LARGURA; j++)
			{
				fputc(tela[i][j], save);
			}
			fputc('\n', save);
		}
		fprintf(save, "%d\n", m);
		fprintf(save, "%d %d\n", x, y);
		for (p = snk; p != NULL; p = p->prox)
		{
			fprintf(save, "%d %d %d\n", p->n.x, p->n.y, p->n.d);
		}
	}
	fclose(save);
}

Node *inicia_valores_load(FILE *save, char tela[ALTURA][LARGURA], Node *Snk, Cobra *c)
{
	int i, j;
	int x1, y1, d1;

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

	tela[0][(LARGURA / 2) - 3] = 'S';
	tela[0][(LARGURA / 2) - 2] = 'C';
	tela[0][(LARGURA / 2) - 1] = 'O';
	tela[0][LARGURA / 2] = 'R';
	tela[0][(LARGURA / 2) + 1] = 'E';
	tela[0][(LARGURA / 2) + 2] = ':';

	score(tela);
	fscanf(save, "%d %d\n", &x, &y);
	while ((i = fscanf(save, "%d %d %d\n", &x1, &y1, &d1)) == 3)
	{
		c->x = x1;
		c->y = y1;
		c->d = (Direcao)d1;

		Snk = insereSnake(tela, Snk, *c);
	}

	return Snk;
}

void placar(char tela[ALTURA][LARGURA])
{
	FILE *rank;
	int ponto, aux_num = 0;
	int pontos[5];
	char nomes[5];
	char nome = '\n', aux_nome = 0;
	int i = 0;

	if ((rank = fopen("rank.txt", "r")) == NULL)
	{
		system("CLS");
		puts("Erro ao abrir ranking.");
		system("PAUSE");
		exit(0);
	}
	else
	{
		ponto = (centena - 48) * 100 + (dezena - 48) * 10 + (unidade - 48);

		while ((fscanf(rank, "%c %d\n", &nomes[i], &pontos[i])) == 2)
		{
			i++;
		}

		for (i = 0; i < 5; i++)
		{
			if (ponto > pontos[i])
			{
				if (aux_num == 0)
				{
					do
					{
						system("CLS");
						puts("Escreva uma letra para lhe identificar:");
						nome = getchar();
					} while (nome == '\n');
				}

				aux_num = pontos[i];
				pontos[i] = ponto;
				ponto = aux_num;
				aux_nome = nomes[i];
				nomes[i] = nome;
				nome = aux_nome;
			}
		}

		fclose(rank);
		if ((rank = fopen("rank.txt", "w")) == NULL)
		{
			system("CLS");
			puts("Erro ao abrir ranking.");
			system("PAUSE");
			exit(0);
		}
		else
		{
			system("CLS");

			for (i = 0; i < 5; i++)
			{
				printf("\t%c\t%d\n", nomes[i], pontos[i]);
				fprintf(rank, "%c %d\n", nomes[i], pontos[i]);
			}
			system("PAUSE");
			fclose(rank);
		}
	}
}