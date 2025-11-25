#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3


typedef struct {
    char nome;  
    int id;     
} Peca;


Peca fila[TAM_FILA];
int inicio = 0, fim = 0;


Peca pilha[TAM_PILHA];
int topo = -1;


int proximoID = 1;


Peca gerarPeca() {
    char tipos[4] = {'I', 'O', 'T', 'L'};
    Peca nova;

    nova.nome = tipos[rand() % 4];
    nova.id = proximoID++;

    return nova;
}


void enqueue(Peca p) {
    fila[fim] = p;
    fim = (fim + 1) % TAM_FILA;
}


Peca dequeue() {
    Peca removida = fila[inicio];
    inicio = (inicio + 1) % TAM_FILA;
    return removida;
}


void push(Peca p) {
    if (topo == TAM_PILHA - 1) {
        printf("⚠️  A pilha está cheia! Não é possível reservar outra peça.\n");
        return;
    }

    pilha[++topo] = p;
    printf("Peça [%c | id=%d] reservada com sucesso!\n", p.nome, p.id);

    
    enqueue(gerarPeca());
}


Peca pop() {
    return pilha[topo--];
}


void mostrarFila() {
    printf("\n=== Fila (5 peças) ===\n");

    int i = inicio;
    for (int c = 0; c < TAM_FILA; c++) {
        printf("[%c | %d] ", fila[i].nome, fila[i].id);
        i = (i + 1) % TAM_FILA;
    }
    printf("\n");
}


void mostrarPilha() {
    printf("=== Pilha de Reserva (max 3) ===\n");

    if (topo == -1) {
        printf("(vazia)\n");
        return;
    }

    for (int i = topo; i >= 0; i--) {
        printf("[%c | %d]\n", pilha[i].nome, pilha[i].id);
    }
    printf("\n");
}


void inicializarFila() {
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(gerarPeca());
    }
}


int main() {
    srand(time(NULL));
    inicializarFila();

    int opcao;

    do {
        mostrarFila();
        mostrarPilha();

        printf("\n=== MENU ===\n");
        printf("1 - Jogar peça\n");
        printf("2 - Reservar peça\n");
        printf("3 - Usar peça reservada\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {

            case 1: { 
                Peca jogada = dequeue();
                printf("Peça jogada: [%c | %d]\n", jogada.nome, jogada.id);

                
                enqueue(gerarPeca());
                break;
            }

            case 2: { 
                if (topo == TAM_PILHA - 1) {
                    printf("⚠️ Pilha cheia! Não é possível reservar.\n");
                } else {
                    Peca reservada = dequeue();
                    push(reservada);
                }
                break;
            }

            case 3: { 
                if (topo == -1) {
                    printf("⚠️ Pilha vazia! Não há peça reservada.\n");
                } else {
                    Peca usada = pop();
                    printf("Peça usada da reserva: [%c | %d]\n", usada.nome, usada.id);

                    
                    enqueue(usada);
                }
                break;
            }

            case 0:
                printf("Encerrando...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}
