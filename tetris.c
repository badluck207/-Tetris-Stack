#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FILA 5  // tamanho máximo da fila

// -------------------------------------------------------------
// Struct que representa uma peça do Tetris
// -------------------------------------------------------------
typedef struct {
    char nome;  // tipo da peça (I, O, T, L)
    int id;     // identificador único
} Peca;

// -------------------------------------------------------------
// Struct da fila circular de peças
// -------------------------------------------------------------
typedef struct {
    Peca itens[MAX_FILA];
    int frente;
    int tras;
    int tamanho;
} Fila;

// -------------------------------------------------------------
// Protótipos das funções
// -------------------------------------------------------------
void inicializarFila(Fila *fila);
int filaVazia(Fila *fila);
int filaCheia(Fila *fila);
void enfileirar(Fila *fila, Peca novaPeca);
void desenfileirar(Fila *fila);
void exibirFila(Fila *fila);
Peca gerarPeca();

// -------------------------------------------------------------
// Função principal
// -------------------------------------------------------------
int main() {
    Fila fila;
    int opcao;
    int idAtual = 0;

    srand(time(NULL)); // inicializa gerador de números aleatórios
    inicializarFila(&fila);

    // Inicializa a fila com 5 peças
    for (int i = 0; i < MAX_FILA; i++) {
        Peca nova = gerarPeca();
        nova.id = idAtual++;
        enfileirar(&fila, nova);
    }

    do {
        printf("\n===== FILA DE PEÇAS FUTURAS =====\n");
        exibirFila(&fila);

        printf("\nOpções:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                desenfileirar(&fila);
                break;
            case 2: {
                if (!filaCheia(&fila)) {
                    Peca nova = gerarPeca();
                    nova.id = idAtual++;
                    enfileirar(&fila, nova);
                } else {
                    printf("\nFila cheia! Não é possível adicionar mais peças.\n");
                }
                break;
            }
            case 0:
                printf("\nEncerrando o programa...\n");
                break;
            default:
                printf("\nOpção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}

// -------------------------------------------------------------
// Função: inicializarFila()
// Inicializa os índices e tamanho da fila
// -------------------------------------------------------------
void inicializarFila(Fila *fila) {
    fila->frente = 0;
    fila->tras = -1;
    fila->tamanho = 0;
}

// -------------------------------------------------------------
// Função: filaVazia()
// Retorna 1 se a fila estiver vazia, senão 0
// -------------------------------------------------------------
int filaVazia(Fila *fila) {
    return fila->tamanho == 0;
}

// -------------------------------------------------------------
// Função: filaCheia()
// Retorna 1 se a fila estiver cheia, senão 0
// -------------------------------------------------------------
int filaCheia(Fila *fila) {
    return fila->tamanho == MAX_FILA;
}

// -------------------------------------------------------------
// Função: enfileirar()
// Adiciona uma peça no final da fila (enqueue)
// -------------------------------------------------------------
void enfileirar(Fila *fila, Peca novaPeca) {
    if (filaCheia(fila)) {
        printf("\nFila cheia! Não é possível inserir nova peça.\n");
        return;
    }

    fila->tras = (fila->tras + 1) % MAX_FILA;
    fila->itens[fila->tras] = novaPeca;
    fila->tamanho++;

    printf("\nPeça [%c %d] inserida na fila.\n", novaPeca.nome, novaPeca.id);
}

// -------------------------------------------------------------
// Função: desenfileirar()
// Remove a peça da frente da fila (dequeue)
// -------------------------------------------------------------
void desenfileirar(Fila *fila) {
    if (filaVazia(fila)) {
        printf("\nFila vazia! Nenhuma peça para jogar.\n");
        return;
    }

    Peca removida = fila->itens[fila->frente];
    fila->frente = (fila->frente + 1) % MAX_FILA;
    fila->tamanho--;

    printf("\nPeça [%c %d] jogada!\n", removida.nome, removida.id);
}

// -------------------------------------------------------------
// Função: exibirFila()
// Mostra o estado atual da fila
// -------------------------------------------------------------
void exibirFila(Fila *fila) {
    if (filaVazia(fila)) {
        printf("\nFila vazia.\n");
        return;
    }

    printf("\nFila de peças:\n");
    for (int i = 0; i < fila->tamanho; i++) {
        int index = (fila->frente + i) % MAX_FILA;
        printf("[%c %d] ", fila->itens[index].nome, fila->itens[index].id);
    }
    printf("\n");
}

// -------------------------------------------------------------
// Função: gerarPeca()
// Gera uma nova peça com tipo aleatório
// -------------------------------------------------------------
Peca gerarPeca() {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.nome = tipos[rand() % 4]; // escolhe tipo aleatório
    nova.id = 0; // o id é definido no momento do enqueue
    return nova;
}
