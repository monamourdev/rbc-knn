#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define DISTANCIA_MINIMA 0.6
#define DISTANCIA_MAXIMA 1.6

#define NUM_ATRIBUTOS 4
#define NUM_CLASSES 5
#define NUM_AMOSTRAS 5

typedef struct {
    float atributo[NUM_ATRIBUTOS];
    float classe;
} Instancia;

void imprimeInstancias(Instancia *instancia, int n);
float distanciaEuclidiana(Instancia a, Instancia b);
void criaNovaClasse(Instancia *instancia, int *n, Instancia *teste, int k);
void descobreClasse(Instancia *instancia, int n);
void criaListaSemRuido(Instancia *instancia, int n);
void compara(Instancia *instancia, int n);
void criaAmostras(char *arquivo, Instancia *instancia, int n);
void capturaInstancias(char *arquivo, int *n, Instancia **vetInstancia);

void imprimeInstancias(Instancia *instancia, int n) {
    int i;
    for (i = 0; i < n; i++) {
        if (instancia[i].classe != -1) {
            printf("%.1f,%.1f,%.1f,%.1f,%.0f\n", instancia[i].atributo[0], instancia[i].atributo[1], instancia[i].atributo[2], instancia[i].atributo[3], instancia[i].classe);
        }
    }
    printf("\n\n");
}

float distanciaEuclidiana(Instancia a, Instancia b) {
    float soma = 0;
    for (int i = 0; i < NUM_ATRIBUTOS; i++) {
        soma += pow((a.atributo[i] - b.atributo[i]), 2);
    }
    return sqrt(soma);
}

void criaNovaClasse(Instancia *instancia, int *n, Instancia *teste, int k) {
    int novo;
    for (int i = *n; i < *n + k; i++) {
        instancia[i] = teste[k - 1];
        novo = k;
        novo++;
    }
    // imprimeInstancias(instancia, *n + k);
}

void descobreClasse(Instancia *instancia, int n) {
    int i, j;
    Instancia teste[NUM_AMOSTRAS];
    float menor, distanciaInstancias;

    teste[0].atributo[0] = 6.6;
    teste[0].atributo[1] = 3.3;
    teste[0].atributo[2] = 6.0;
    teste[0].atributo[3] = 2.5;
    
    srand((unsigned)time(NULL));
    for (i = 1; i < NUM_AMOSTRAS; i++) {
        teste[i].atributo[0] = (50 + rand() % 70) / 10.0;
        teste[i].atributo[1] = (20 + rand() % 44) / 10.0;
        teste[i].atributo[2] = (10 + rand() % 45) / 10.0;
        teste[i].atributo[3] = (2 + rand() % 25) / 10.0;
    }

    menor = distanciaEuclidiana(instancia[0], teste[0]);

    for (j = 0; j < NUM_AMOSTRAS; j++) {
        for (i = 1; i < n; i++) {
            distanciaInstancias = distanciaEuclidiana(instancia[i], teste[j]);

            if (distanciaInstancias < menor) {
                teste[j].classe = instancia[i].classe;
                menor = distanciaInstancias;
            }
        }
        if (menor > DISTANCIA_MAXIMA) {
            teste[j].classe = NUM_CLASSES;
            criaNovaClasse(instancia, &n, teste, NUM_AMOSTRAS);
            printf("\nInstancia muito distante\n");
        }
        printf("\nA instancia %.1f,%.1f,%.1f,%.1f, pertence a classe: %.0f\nsua distancia eh: %.1f\n",
               teste[j].atributo[0],
               teste[j].atributo[1],
               teste[j].atributo[2],
               teste[j].atributo[3],
               teste[j].classe, menor);
        menor = 9999;
    }

    printf("\n\nA primeira instancia teste foi criada numa variavel global para facilitar a manipulacao.\nAs demais sao criadas aleatoriamente\n");

    // nova lista gerada com mais classes
    printf("\n==========================================\n");
    printf("LISTA DE INSTANCIAS COM NOVAS CLASSES");
    printf("\n==========================================\n");
    imprimeInstancias(instancia, n + NUM_AMOSTRAS);
}

void criaListaSemRuido(Instancia *instancia, int n) {
    Instancia *listaSemRuido = (Instancia *)malloc(sizeof(Instancia) * 50);
    int k = 0;

    for (int i = 0; i < n; i++) {
        if (instancia[i].classe != -1) {
            listaSemRuido[k] = instancia[i];
            k++;
        }
    }
    printf("\n===============================\n");
    printf("\t2.LISTA SEM RUIDO");
    printf("\n===============================\n");
    imprimeInstancias(listaSemRuido, k);
    descobreClasse(listaSemRuido, k);
    free(listaSemRuido);
}

void compara(Instancia *instancia, int n) {
    float distanciaInstancias;

    for (int i = 0; i < n; i++) {
        if (instancia[i].classe != -1) {
            for (int j = i + 1; j < n; j++) {
                if (instancia[j].classe != -1) {
                    distanciaInstancias = distanciaEuclidiana(instancia[i], instancia[j]);

                    if (distanciaInstancias < DISTANCIA_MINIMA) {
                        instancia[j].classe = -1;
                    }
                }
            }
        }
    }
    criaListaSemRuido(instancia, n);
}

void criaAmostras(char *arquivo, Instancia *instancia, int n) {
    int raffle;
    FILE *fp = fopen(arquivo, "r");
    
    if (fp == NULL) {
        printf("\nNao Abriu\n");
        return;
    }

    srand((unsigned)time(NULL));
    for (int i = 0; i < NUM_AMOSTRAS; i++) {
        raffle = rand() % n;
        fscanf(fp, "%f,%f,%f,%f,%f", &instancia[raffle].atributo[0], &instancia[raffle].atributo[1], &instancia[raffle].atributo[2], &instancia[raffle].atributo[3], &instancia[raffle].classe);
    }

    // imprimeInstancias(instancia, NUM_AMOSTRAS);

    printf("\n\n");
    fclose(fp);
}

void capturaInstancias(char *arquivo, int *n, Instancia **vetInstancia) {
    Instancia *instancia = (Instancia *)malloc(sizeof(Instancia) * (*n));
    
    FILE *fp = fopen(arquivo, "r");
    if (fp == NULL) {
        printf("\nNao Abriu\n");
        exit(1);
    }

    for (int i = 0; i < *n; i++) {
        fscanf(fp, "%f,%f,%f,%f,%f", &instancia[i].atributo[0], &instancia[i].atributo[1], &instancia[i].atributo[2], &instancia[i].atributo[3], &instancia[i].classe);
    }
    printf("\n=============================================\n");
    printf("\t1.INSTANCIAS DO ARQUIVO IRIS.DATA");
    printf("\n=============================================\n");
    imprimeInstancias(instancia, *n);
    criaAmostras(arquivo, instancia, *n);

    printf("\n\n");
    compara(instancia, *n);

    *vetInstancia = instancia;
    fclose(fp);
}

int main(int argc, char *argv[]) {
    int n = 1;
    Instancia *vetInstancia;

    char caiu;
    FILE *fp = fopen(argv[1], "r");
    
    if (fp == NULL) {
        printf("\nNao Abriu\n");
        return 0;
    }
    
    while (fscanf(fp, "%c", &caiu) != EOF) {
        if (caiu == '\n') {
            n++;
        }
    }

    vetInstancia = (Instancia *)malloc(sizeof(Instancia) * (6 * n));

    capturaInstancias(argv[1], &n, &vetInstancia);

    free(vetInstancia);
    return 0;
}

