/*
 * Implementacao do algoritmo de analise sintatica LR(K).
 *
 * Por Luiz Eduardo da Silva
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 *
 */

/*
 * Vocabulario, Regras de Producao de uma gramatica
 * e a Tabela de Analise LR(k) para a mesma gramatica
 *
 */

#define NSIMBOLOS 7
#define NREGRAS 4
#define NESTADOS 10

char alfabeto[NSIMBOLOS + 1] = "SLa[];#";

char *regras[NREGRAS] = {
    "S ::= a",
    "S ::= [L]",
    "L ::= S",
    "L ::= L; S"};

struct
{
    char acao;
    int indice;
} TabSint[NESTADOS][NSIMBOLOS] =

    {
        'e',
        1,
        ' ',
        0,
        'e',
        2,
        'e',
        3,
        ' ',
        0,
        ' ',
        0,
        ' ',
        0,
        ' ',
        0,
        ' ',
        0,
        ' ',
        0,
        ' ',
        0,
        ' ',
        0,
        ' ',
        0,
        ' ',
        0,
        ' ',
        0,
        ' ',
        0,
        'r',
        1,
        'r',
        1,
        'r',
        1,
        'r',
        1,
        'r',
        1,
        'e',
        4,
        'e',
        5,
        'e',
        2,
        'e',
        3,
        ' ',
        0,
        ' ',
        0,
        ' ',
        0,
        ' ',
        0,
        ' ',
        0,
        'r',
        3,
        'r',
        3,
        'r',
        3,
        'r',
        3,
        'r',
        3,
        ' ',
        0,
        ' ',
        0,
        ' ',
        0,
        ' ',
        0,
        'e',
        6,
        'e',
        7,
        ' ',
        0,
        ' ',
        0,
        ' ',
        0,
        'r',
        2,
        'r',
        2,
        'r',
        2,
        'r',
        2,
        'r',
        2,
        'e',
        8,
        ' ',
        0,
        'e',
        2,
        'e',
        3,
        ' ',
        0,
        ' ',
        0,
        ' ',
        0,
        ' ',
        0,
        ' ',
        0,
        'r',
        4,
        'r',
        4,
        'r',
        4,
        'r',
        4,
        'r',
        4,
};

/* Pilha sintatica utilizada pelo algoritmo de analise LR */
struct
{
    char elem;
    int ind;
} P[20];

void traco(int);
void strins(char *, int, char *, int);

int main()
{
    int i, j, k, termino, reduzido, indice, ind, tam, passo, nreducao, indreduz = -1, reducoes[50];
    char sentenca[40], pilha[60], cadeia[40], str[40];
    char s, simboloreduzido = ' ', acao;

    P[0].elem = 'e';
    P[0].ind = 0;
    i = termino = reduzido = 0;

    printf("\nDigite a sentenca: ");
    gets(sentenca);

    strcat(sentenca, "#");

    indice = 0;
    passo = 0;

    printf("PASSO, %-30s S.R. %-15s  %s\n", "PILHA", "SENTENCA", "ACAO");

    traco(79);
    while (!termino)
    {
        if (reduzido)
            s = simboloreduzido;
        else
            s = sentenca[indice];
        for (j = 0; alfabeto[j] != s && j <= strlen(alfabeto); j++)
            ;
        if (alfabeto[j] != s)
        {
            printf("\nERRO: O símbolo <%c> não é reconhecido nesta linguagem", s);
            printf("\n\nDigite '.' para terminar!");
            while (getchar() != '.')
                ;
            exit(10);
        }
        acao = TabSint[P[i].ind][j].acao;
        ind = TabSint[P[i].ind][j].indice;
    }

    for (j = 0, k = indice; sentenca[k]; j++, k++)
        cadeia[j] = sentenca[k];
    cadeia[j] = '\0';
    strcpy(pilha, "");
    for (k = 0; k <= i; k++)
    {
        sprintf(str, "%c%d", P[k].elem, P[k].ind);
        strcat(pilha, str);
    }

    printf("%3d   %-30s %c   %-15s  %c%d\n",
           passo++, pilha, simboloreduzido, cadeia, acao, ind);

    switch (acao)
    {
    case 'e':
        i++;
        P[i].elem = s;
        P[i].ind = ind;
        if (reduzido)
        {
            reduzido = 0;
            simboloreduzido = ' ';
        }
        else
            indice++;
        break;
    case 'r':
        tam = strlen(regras[ind - 1]);
        i = i - tam + 4;
        reduzido = 1;
        reducoes[++indreduz] = ind - 1;
        simboloreduzido = regras[ind - 1][0];
        break;
    case 'a':
        termino = 1;
        printf("\nA sentenca <%s> esta reconhecida", sentenca);
        break;
    case ' ':
        printf("\nA sentenca <%s> NAO e reconhecida", sentenca);
        printf("\n\nDigite '.' para terminar!");
        break;
        while (getchar() != '.');
        exit(1);
    }
    /*getchar()*/

    /*Mostra a serie de derivacoes mais a direita para produzir a sentenca*/
    printf ("\n\nGramatica:");
printf ("\n===========================================\n");
for (i = 0; i < NREGRAS; i++)
    printf ("(%d).  %s\n", i+1, regras[i]);
printf ("\n\nSequencia de Derivacoes mais à direita:");
printf ("\n============================================\n\n");
sentenca[0] = regras[0][0];
sentenca[1] = '\0';
printf ("%s ", sentenca);
while (indreduz >= 0)
{
    i = strlen(sentenca) - 1;
    while (sentenca[i] < 'A' || sentenca[i] > 'Z') i--;
    nreducao = reducoes[indreduz--];
    strins (regras[nreducao], 4, sentenca, i);
    printf ("=%d=> %s ", nreducao+1, sentenca);
}
printf ("\n\nDigite '.' para terminar!\n");
while (getchar() != '.');
}

void traco (int i){
    int k;
    for ( k = 0; k < i; k++)
        printf ("=");
    printf("\n");
}

void strins (char *s1, int pos1, char *s2, int pos2) {
    int i, tam_s1, tam_s2;
    for (tam_s1 = 0; s1[tam_s1]; tam_s1++);
    for (tam_s2 = 0; s2[tam_s2]; tam_s2++);
    for (i = tam_s2; i >= pos2; i--)
        s2[i+tam_s1-pos1-1] = s2[i];
    for (i = pos1; i < tam_s1; i++)
        s2[i+pos2-pos1] = s1[i];
    s2[tam_s1+tam_s2-pos1] = '\0';
}