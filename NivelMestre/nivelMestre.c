#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MISSao_BUFFER 200

// struct territorio
typedef struct {
    char nome[30];
    char cor[10];   // dono por cor
    int tropas;
} Territorio;

// struct jogador
typedef struct {
    char nome[30];
    char cor[10];
    char *missao; // alocada dinamicamente
} Jogador;


// atribui uma missão aleatória (destino já deve apontar para memória alocada)
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int idx = rand() % totalMissoes;
    strcpy(destino, missoes[idx]);
}

// exibe missão (passagem por valor da string)
void exibirMissao(const char *missao) {
    printf("Missao: %s\n", missao);
}

// função de ataque - usa ponteiros
void atacar(Territorio* atacante, Territorio* defensor) {
    int dadoA = (rand() % 6) + 1;
    int dadoD = (rand() % 6) + 1;

    printf("\n-- Combate entre %s (A) e %s (D) --\n", atacante->nome, defensor->nome);
    printf("%s rolou: %d\n", atacante->nome, dadoA);
    printf("%s rolou: %d\n", defensor->nome, dadoD);

    if (dadoA > dadoD) {
        printf("Resultado: atacante venceu!\n");
        // defensor troca de dono
        strcpy(defensor->cor, atacante->cor);
        // defensor recebe metade das tropas do atacante (arredonda para baixo)
        defensor->tropas = atacante->tropas / 2;
    } else {
        printf("Resultado: defensor resistiu!\n");
        if (atacante->tropas > 0)
            atacante->tropas--; // atacante perde 1 tropa
    }
}

// exibe mapa resumido
void exibirMapa(Territorio* mapa, int tamanho) {
    printf("\n=== MAPA ===\n");
    for (int i = 0; i < tamanho; i++) {
        printf("[%d] %s | Cor: %s | Tropas: %d\n",
               i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// verifica missão simples; retorna 1 se cumprida, 0 caso contrário
// missao: texto; mapa: vetor de territorios; tamanho: número territorios
// playerCor: cor do jogador; inimigoCor: cor do oponente
int verificarMissao(const char* missao, Territorio* mapa, int tamanho, const char* playerCor, const char* inimigoCor) {
    // 1) "Conquistar 3 territorios"
    if (strcmp(missao, "Conquistar 3 territorios") == 0) {
        int cnt = 0;
        for (int i = 0; i < tamanho; i++)
            if (strcmp(mapa[i].cor, playerCor) == 0) cnt++;
        return (cnt >= 3);
    }

    // 2) "Conquistar 5 territorios"
    if (strcmp(missao, "Conquistar 5 territorios") == 0) {
        int cnt = 0;
        for (int i = 0; i < tamanho; i++)
            if (strcmp(mapa[i].cor, playerCor) == 0) cnt++;
        return (cnt >= 5);
    }

    // 3) "Eliminar todas as tropas do adversario"
    if (strcmp(missao, "Eliminar todas as tropas do adversario") == 0) {
        int soma = 0;
        for (int i = 0; i < tamanho; i++)
            if (strcmp(mapa[i].cor, inimigoCor) == 0)
                soma += mapa[i].tropas;
        return (soma == 0);
    }

    // 4) "Ter um territorio com 8 ou mais tropas"
    if (strcmp(missao, "Ter um territorio com 8 ou mais tropas") == 0) {
        for (int i = 0; i < tamanho; i++)
            if (strcmp(mapa[i].cor, playerCor) == 0 && mapa[i].tropas >= 8)
                return 1;
        return 0;
    }

    // 5) "Controlar metade dos territorios"
    if (strcmp(missao, "Controlar metade dos territorios") == 0) {
        int cnt = 0;
        for (int i = 0; i < tamanho; i++)
            if (strcmp(mapa[i].cor, playerCor) == 0) cnt++;
        return (cnt >= (tamanho / 2));
    }

    // missão desconhecida: não cumprida
    return 0;
}

// libera memória de missões e mapa
void liberarMemoria(Territorio* mapa, Jogador* jogadores, int numJogadores) {
    if (mapa) free(mapa);
    for (int i = 0; i < numJogadores; i++) {
        if (jogadores[i].missao) free(jogadores[i].missao);
    }
    if (jogadores) free(jogadores);
}


int main() {
    srand(time(NULL));

    int n;
    printf("Quantos territorios (minimo 5 recomendado)? ");
    scanf("%d", &n);
    if (n <= 0) {
        printf("Numero invalido.\n");
        return 0;
    }

    // aloca mapa dinamico
    Territorio *mapa = (Territorio*) calloc(n, sizeof(Territorio));
    if (!mapa) {
        printf("Erro alocacao.\n");
        return 1;
    }

    // cadastra territorios
    printf("\n-- Cadastro dos territorios --\n");
    for (int i = 0; i < n; i++) {
        printf("\nTerritorio %d nome: ", i);
        scanf(" %29[^\n]", mapa[i].nome);
        printf("Cor (dono inicial): ");
        scanf(" %9s", mapa[i].cor);
        printf("Tropas: ");
        scanf("%d", &mapa[i].tropas);
    }

    // numero de jogadores (vamos fazer 2)
    int numJogadores = 2;
    Jogador *jogadores = (Jogador*) malloc(sizeof(Jogador) * numJogadores);
    if (!jogadores) {
        printf("Erro alocacao jogadores.\n");
        free(mapa);
        return 1;
    }

    // entrada jogadores
    for (int i = 0; i < numJogadores; i++) {
        printf("\nNome do jogador %d: ", i+1);
        scanf(" %29[^\n]", jogadores[i].nome);
        printf("Cor do jogador %d: ", i+1);
        scanf(" %9s", jogadores[i].cor);
        // aloca memoria para missao
        jogadores[i].missao = (char*) malloc(MISSao_BUFFER);
        jogadores[i].missao[0] = '\0';
    }

    // vetor de missoes pre-definidas
    char *missoes[] = {
        "Conquistar 3 territorios",
        "Conquistar 5 territorios",
        "Eliminar todas as tropas do adversario",
        "Ter um territorio com 8 ou mais tropas",
        "Controlar metade dos territorios"
    };
    int totalMissoes = sizeof(missoes) / sizeof(missoes[0]);

    // atribui missao para cada jogador (mostra uma vez)
    printf("\n-- Sorteando missoes --\n");
    for (int i = 0; i < numJogadores; i++) {
        atribuirMissao(jogadores[i].missao, missoes, totalMissoes);
        printf("\nJogador: %s\n", jogadores[i].nome);
        exibirMissao(jogadores[i].missao);
        printf("(esta missao sera verificada automaticamente durante o jogo)\n");
    }

    // jogo: turno alternado
    int turno = 0; // 0 -> jogador 0, 1 -> jogador 1
    int opcao;
    int vencedor = -1;

    do {
        int atual = turno % numJogadores;
        int oponente = (turno + 1) % numJogadores;

        printf("\n============================\n");
        printf("Turno de: %s (cor %s)\n", jogadores[atual].nome, jogadores[atual].cor);
        exibirMapa(mapa, n);

        // ação do jogador
        printf("\nAcoes:\n1 - Atacar\n2 - Passar turno\n0 - Sair do jogo\nEscolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            int idxA, idxD;
            printf("Indice do territorio atacante: ");
            scanf("%d", &idxA);
            printf("Indice do territorio defensor: ");
            scanf("%d", &idxD);

            // valida indices
            if (idxA < 0 || idxA >= n || idxD < 0 || idxD >= n) {
                printf("Indice invalido.\n");
            } else {
                // valida que atacante pertença ao jogador atual
                if (strcmp(mapa[idxA].cor, jogadores[atual].cor) != 0) {
                    printf("Territorio atacante nao pertence a voce.\n");
                } else if (strcmp(mapa[idxD].cor, jogadores[atual].cor) == 0) {
                    printf("Nao pode atacar territorio da mesma cor.\n");
                } else {
                    // realiza ataque
                    atacar(&mapa[idxA], &mapa[idxD]);
                }
            }
        } else if (opcao == 2) {
            printf("Passando turno.\n");
        } else if (opcao == 0) {
            printf("Saindo do jogo.\n");
            break;
        } else {
            printf("Opcao invalida.\n");
        }

        // verifica se jogador atual cumpriu a missao
        if (verificarMissao(jogadores[atual].missao, mapa, n, jogadores[atual].cor, jogadores[oponente].cor)) {
            vencedor = atual;
            printf("\n*** Missao cumprida por %s! ***\n", jogadores[atual].nome);
            break;
        }

        turno++;
    } while (1);

    if (vencedor >= 0) {
        printf("\nVencedor: %s (missao: %s)\n", jogadores[vencedor].nome, jogadores[vencedor].missao);
    } else {
        printf("\nNenhum vencedor declarado.\n");
    }

    // libera memoria
    liberarMemoria(mapa, jogadores, numJogadores);

    printf("\nFim do jogo. Obrigado por jogar.\n");
    return 0;
}
