#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Struct do território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;


// Cadastro dos territórios
void cadastrar(Territorio *mapa, int n) {
    for (int i = 0; i < n; i++) {
        printf("\n--- Territorio %d ---\n", i + 1);

        printf("Nome: ");
        scanf(" %29[^\n]", mapa[i].nome);

        printf("Cor do exercito: ");
        scanf(" %9s", mapa[i].cor);

        printf("Tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}


// Mostra todos os territórios
void exibir(Territorio *mapa, int n) {
    printf("\n=== TERRITORIOS ===\n");
    for (int i = 0; i < n; i++) {
        printf("\n[%d] %s\n", i, mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
    }
}


// Função do ataque
void atacar(Territorio *atacante, Territorio *defensor) {
    // Dado aleatório 1–6
    int dadoA = (rand() % 6) + 1;
    int dadoD = (rand() % 6) + 1;

    printf("\nAtaque!\n");
    printf("%s (A) tirou: %d\n", atacante->nome, dadoA);
    printf("%s (D) tirou: %d\n", defensor->nome, dadoD);

    if (dadoA > dadoD) {
        printf("Atacante venceu!\n");

        // defensor muda de cor
        strcpy(defensor->cor, atacante->cor);

        // novas tropas do defensor
        defensor->tropas = atacante->tropas / 2;

    } else {
        printf("Defensor venceu!\n");

        // atacante perde 1 tropa
        if (atacante->tropas > 0)
            atacante->tropas--;
    }
}


// Libera memória
void liberarMemoria(Territorio *mapa) {
    free(mapa);
}


int main() {
    srand(time(NULL));

    int n;
    printf("Quantidade de territorios: ");
    scanf("%d", &n);

    // alocação dinâmica
    Territorio *mapa = (Territorio*) calloc(n, sizeof(Territorio));

    cadastrar(mapa, n);

    int opcao;
    do {
        exibir(mapa, n);

        printf("\n1 - Atacar\n");
        printf("0 - Sair\n> ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            int a, d;

            printf("\nEscolha o atacante (indice): ");
            scanf("%d", &a);

            printf("Escolha o defensor (indice): ");
            scanf("%d", &d);

            // impedir ataque da mesma cor
            if (strcmp(mapa[a].cor, mapa[d].cor) == 0) {
                printf("Nao pode atacar territorio da mesma cor!\n");
            } else {
                atacar(&mapa[a], &mapa[d]);
            }
        }

    } while (opcao != 0);

    liberarMemoria(mapa);

    printf("\nJogo encerrado.\n");
    return 0;
}
