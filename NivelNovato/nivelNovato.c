#include <stdio.h>
#include <string.h>

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

int main() {

    // Armazena os 5 territórios
    Territorio territorios[5];

    printf("=== SISTEMA DE CADASTRO DE TERRITORIOS (WAR) ===\n");

    // Entrada dos dados
    for (int i = 0; i < 5; i++) {
        printf("\n--- Cadastro do Territorio %d ---\n", i + 1);

        printf("Nome do territorio: ");
        scanf(" %29[^\n]", territorios[i].nome); 
        // %29[^\n] para pegar nome com espaços

        printf("Cor do exercito: ");
        scanf(" %9s", territorios[i].cor); 

        printf("Quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
    }

    // Exibição dos dados cadastrados
    printf("\n=== LISTA DE TERRITORIOS CADASTRADOS ===\n");

    for (int i = 0; i < 5; i++) {
        printf("\nTerritorio %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exercito: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
    }

    printf("\nCadastro concluido com sucesso!\n");

    return 0;
}
