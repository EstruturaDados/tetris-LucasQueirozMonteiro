#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 5   


typedef struct {
    char nome;  
    int id;    
} Peca;


Peca fila[TAM];
int inicio = 0, fim = 0, qtd = 0;
int proximoID = 1;


Peca gerarPeca() {
    char tipos[4] = {'I', 'O', 'T', 'L'};
    Peca nova;

    nova.nome = tipos[rand() % 4];
    nova.id = proximoID++;

    return nova;
}


void enqueue() {
    if (qtd == TAM) {
        printf("⚠️  A fila está cheia! Não é possível inserir.\n");
        return;
    }

    fila[fim] = gerarPeca();
    fim = (fim + 1) % TAM;
    qtd++;

    printf("Peça inserida com sucesso!\n");
}


void dequeue() {
    if (qtd == 0) {
        printf("⚠️  A fila está vazia! Não há peça para jogar.\n");
        return;
    }

    Peca removida = fila[inicio];
    inicio = (inicio + 1) % TAM;
    qtd--;

    printf("Você jogou a peça: [%c | id=%d]\n", removida.nome, removida.id);
}


void mostrarFila() {
    printf("\n=== Estado atual da fila ===\n");

    if (qtd == 0) {
        printf("(fila vazia)\n\n");
        return;
    }

    int i = inicio;
    for (int c = 0; c < qtd; c++) {
        printf("[%c | id=%d] ", fila[i].nome, fila[i].id);
        i = (i + 1) % TAM;
    }
    printf("\n\n");
}


void inicializarFila() {
    for (int i = 0; i < TAM; i++) {
        enqueue();
    }
}


int main() {
    srand(time(NULL));

    inicializarFila();  
    int opcao;

    do {
        mostrarFila();

        printf("=== MENU ===\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("3 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                dequeue();
                break;
            case 2:
                enqueue();
                break;
            case 3:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 3);

    return 0;
}
