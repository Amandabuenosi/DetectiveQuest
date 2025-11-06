#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// sala (nó da árvore binária)
typedef struct Sala {
    char nome[50];
    char pista[100];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

// árvore de pistas (BST)
typedef struct PistaNode {
    char pista[100];
    struct PistaNode *esquerda;
    struct PistaNode *direita;
} PistaNode;

// Cria dinamicamente umc comodo com nome e pista
Sala* criarSala(const char *nome, const char *pista) {
    Sala *nova = (Sala*) malloc(sizeof(Sala));
    if (nova == NULL) {
        printf("Erro ao alocar memória para a sala!\n");
        exit(1);
    }
    strcpy(nova->nome, nome);
    strcpy(nova->pista, pista);
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

// Pista na árvore BST em ordem alfabética
PistaNode* inserirPista(PistaNode *raiz, const char *pista) {
    if (raiz == NULL) {
        PistaNode *nova = (PistaNode*) malloc(sizeof(PistaNode));
        strcpy(nova->pista, pista);
        nova->esquerda = NULL;
        nova->direita = NULL;
        return nova;
    }

    if (strcmp(pista, raiz->pista) < 0)
        raiz->esquerda = inserirPista(raiz->esquerda, pista);
    else if (strcmp(pista, raiz->pista) > 0)
        raiz->direita = inserirPista(raiz->direita, pista);

    return raiz;
}

// pistas coletadas em ordem alfabética (in-order)
void exibirPistas(PistaNode *raiz) {
    if (raiz != NULL) {
        exibirPistas(raiz->esquerda);
        printf("- %s\n", raiz->pista);
        exibirPistas(raiz->direita);
    }
}

// Explora a mansão e coletar pistas
void explorarSalasComPistas(Sala *atual, PistaNode **raizPistas) {
    if (atual == NULL) return;

    printf("\nVocê está em: %s\n", atual->nome);

    if (strlen(atual->pista) > 0) {
        printf("Você encontrou uma pista: \"%s\"\n", atual->pista);
        *raizPistas = inserirPista(*raizPistas, atual->pista);
    } else {
        printf("Nenhuma pista encontrada aqui.\n");
    }

    char escolha;
    printf("Deseja ir para a esquerda (e), direita (d) ou sair (s)? ");
    scanf(" %c", &escolha);

    if (escolha == 'e' || escolha == 'E') {
        if (atual->esquerda != NULL)
            explorarSalasComPistas(atual->esquerda, raizPistas);
        else
            printf("Não há caminho à esquerda!\n");
    } 
    else if (escolha == 'd' || escolha == 'D') {
        if (atual->direita != NULL)
            explorarSalasComPistas(atual->direita, raizPistas);
        else
            printf("Não há caminho à direita!\n");
    } 
    else if (escolha == 's' || escolha == 'S') {
        printf("Encerrando exploração...\n");
        return;
    } 
    else {
        printf("Opção inválida! Tente novamente.\n");
        explorarSalasComPistas(atual, raizPistas);
    }
}

// Exibe o menu principal
void menu() {
    printf("\n==============================\n");
    printf(" 🔎 DETECTIVE QUEST - MENU\n");
    printf("==============================\n");
    printf("1 - Explorar a mansão\n");
    printf("2 - Ver pistas coletadas\n");
    printf("0 - Sair do jogo\n");
    printf("==============================\n");
    printf("Escolha uma opção: ");
}

// Função principal
int main() {
    // Criação das salas (árvore binária fixa)
    Sala *hall = criarSala("Hall de Entrada", "Um lenço com as iniciais 'M.K.'");
    Sala *salaEstar = criarSala("Sala de Estar", "Um copo quebrado próximo ao sofá");
    Sala *cozinha = criarSala("Cozinha", "");
    Sala *biblioteca = criarSala("Biblioteca", "Um livro com uma página arrancada");
    Sala *jardim = criarSala("Jardim", "");
    Sala *quarto = criarSala("Quarto Principal", "Perfume idêntico ao da vítima");
    Sala *porao = criarSala("Porão Misterioso", "Uma luva manchada de tinta vermelha");

    // Estrutura da mansão
    hall->esquerda = salaEstar;
    hall->direita = cozinha;
    salaEstar->esquerda = biblioteca;
    salaEstar->direita = jardim;
    cozinha->esquerda = quarto;
    cozinha->direita = porao;

    PistaNode *pistasColetadas = NULL;
    int opcao;

    printf("=====================================\n");
    printf("DETECTIVE QUEST: COLETA DE PISTAS\n");
    printf("=====================================\n");
    printf("Bem-vindo, detetive! Explore a mansão e descubra o mistério!\n");

    do {
        menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("\nIniciando exploração da mansão...\n");
                explorarSalasComPistas(hall, &pistasColetadas);
                break;
            case 2:
                printf("\n=== PISTAS COLETADAS ===\n");
                if (pistasColetadas == NULL)
                    printf("Nenhuma pista foi coletada ainda.\n");
                else
                    exibirPistas(pistasColetadas);
                break;
            case 0:
                printf("\nEncerrando o jogo... Até a próxima, detetive!\n");
                break;
            default:
                printf("\nOpção inválida! Escolha novamente.\n");
        }

    } while (opcao != 0);

    // Libera memória das salas (simplificado)
    free(hall);
    free(salaEstar);
    free(cozinha);
    free(biblioteca);
    free(jardim);
    free(quarto);
    free(porao);

    return 0;
}
