#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura sala, nó
typedef struct Sala {
    char nome[50];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

// Função que cria sala, nó da árvore
Sala* criarSala(const char *nome) {
    Sala *novaSala = (Sala*) malloc(sizeof(Sala));
    if (novaSala == NULL) {
        printf("Erro ao alocar memória para a sala!\n");
        exit(1);
    }
    strcpy(novaSala->nome, nome);
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    return novaSala;
}

// Explorar as salas
void explorarSalas(Sala *atual) {
    if (atual == NULL) return;

    printf("\nVocê está em: %s\n", atual->nome);

    // Caso o jogador chegue a uma sala sem caminhos (nó-folha)
    if (atual->esquerda == NULL && atual->direita == NULL) {
        printf("Fim da exploração! Não há mais caminhos a seguir.\n");
        return;
    }

    char escolha;
    printf("Deseja ir para a esquerda (e), direita (d) ou sair (s)? ");
    scanf(" %c", &escolha);

    if (escolha == 'e' || escolha == 'E') {
        if (atual->esquerda != NULL)
            explorarSalas(atual->esquerda);
        else
            printf("Não há caminho à esquerda!\n");
    } 
    else if (escolha == 'd' || escolha == 'D') {
        if (atual->direita != NULL)
            explorarSalas(atual->direita);
        else
            printf("Não há caminho à direita!\n");
    } 
    else if (escolha == 's' || escolha == 'S') {
        printf("Você decidiu encerrar a exploração.\n");
        return;
    } 
    else {
        printf("Opção inválida! Tente novamente.\n");
        explorarSalas(atual);
    }
}


int main() {
    // Montagem manual da árvore binária (mapa da mansão)
    Sala *hall = criarSala("Hall de Entrada");
    Sala *salaEstar = criarSala("Sala de Estar");
    Sala *cozinha = criarSala("Cozinha");
    Sala *biblioteca = criarSala("Biblioteca");
    Sala *jardim = criarSala("Jardim");
    Sala *quarto = criarSala("Quarto Principal");
    Sala *porao = criarSala("Porão Misterioso");

    // estrutura da árvore
    hall->esquerda = salaEstar;
    hall->direita = cozinha;
    salaEstar->esquerda = biblioteca;
    salaEstar->direita = jardim;
    cozinha->esquerda = quarto;
    cozinha->direita = porao;

    // Inicio Hall de Entrada
    printf("\n=== DETECTIVE QUEST ===\n\n");
    printf("Explore a mansão e descubra o que há em cada cômodo!\n");
    printf("---------------------------------------------\n");

    explorarSalas(hall);

    // Liberação de memória
    free(hall);
    free(salaEstar);
    free(cozinha);
    free(biblioteca);
    free(jardim);
    free(quarto);
    free(porao);

    printf("\nObrigado por jogar Detective Quest!\n");
    return 0;
}
