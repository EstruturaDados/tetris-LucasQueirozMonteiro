#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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


typedef struct {
    Peca fila[TAM_FILA];
    int inicio, fim;
    Peca pilha[TAM_PILHA];
    int topo;
} Estado;

Estado ultimoEstado;
int historicoDisponivel = 0; 


Peca gerarPeca() {
    char tipos[4] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.nome = tipos[rand() % 4];
    nova.id = proximoID++;
    return nova;
}

void salvarEstado() {
    memcpy(ultimoEstado.fila, fila, sizeof(fila));
    ultimoEstado.inicio = inicio;
    ultimoEstado.fim = fim;
    memcpy(ultimoEstado.pilha, pilha, sizeof(pilha));
    ultimoEstado.topo = topo;
    historicoDisponivel = 1;
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
        printf("⚠️ Pilha cheia!\n");
        return;
    }
    pilha[++topo] = p;
}

Peca pop() {
    return pilha[topo--];
}


void mostrarFila() {
    printf("\n=== Fila (5 peças) ===\n");
    int i = inicio;
    for (int c = 0; c < TAM_FILA; c++) {
        printf("[%c|%d] ", fila[i].nome, fila[i].id);
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
        printf("[%c|%d]\n", pilha[i].nome, pilha[i].id);
    }
    printf("\n");
}


void inicializarFila() {
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(gerarPeca());
    }
}


void trocarTopoFila() {
    if (topo == -1) {
        printf("⚠️ Pilha vazia!\n");
        return;
    }
    salvarEstado();
    Peca temp = fila[inicio];
    fila[inicio] = pilha[topo];
    pilha[topo] = temp;
    printf("Topo da pilha trocado com frente da fila!\n");
}


void desfazer() {
    if (!historicoDisponivel) {
        printf("⚠️ Nenhuma jogada para desfazer!\n");
        return;
    }
    memcpy(fila, ultimoEstado.fila, sizeof(fila));
    inicio = ultimoEstado.inicio;
    fim = ultimoEstado.fim;
    memcpy(pilha, ultimoEstado.pilha, sizeof(pilha));
    topo = ultimoEstado.topo;
    historicoDisponivel = 0;
    printf("Última jogada desfeita!\n");
}


void inverterFilaPilha() {
    salvarEstado();
    
    Peca tempFila[TAM_FILA];
    memcpy(tempFila, fila, sizeof(fila));

    
    Peca tempPilha[TAM_PILHA];
    memcpy(tempPilha, pilha, sizeof(pilha));
    int tempTopo = topo;
    int tempInicio = inicio;
    int tempFim = fim;

    
    topo = -1;
    inicio = 0;
    fim = 0;

    
    for (int i = 0; i < TAM_FILA && i < TAM_PILHA; i++) {
        push(tempFila[(inicio + i) % TAM_FILA]);
    }

    
    int countFila = 0;
    for (int i = 0; i <= tempTopo && countFila < TAM_FILA; i++, countFila++) {
        enqueue(tempPilha[i]);
    }
    while (countFila < TAM_FILA) {
        enqueue(gerarPeca());
        countFila++;
    }

    printf("Fila e pilha invertidas!\n");
}


int main() {
    srand(time(NULL));
    inicializarFila();
    int opcao;

    do {
        mostrarFila();
        mostrarPilha();

        printf("\n=== MENU Mestre ===\n");
        printf("1 - Jogar peça\n");
        printf("2 - Reservar peça\n");
        printf("3 - Usar peça reservada\n");
        printf("4 - Trocar topo da pilha com frente da fila\n");
        printf("5 - Desfazer última jogada\n");
        printf("6 - Inverter fila com pilha\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: {
                salvarEstado();
                Peca jogada = dequeue();
                printf("Peça jogada: [%c|%d]\n", jogada.nome, jogada.id);
                enqueue(gerarPeca());
                break;
            }
            case 2: {
                if (topo == TAM_PILHA - 1) {
                    printf("⚠️ Pilha cheia!\n");
                } else {
                    salvarEstado();
                    Peca reservada = dequeue();
                    push(reservada);
                    enqueue(gerarPeca());
                    printf("Peça reservada!\n");
                }
                break;
            }
            case 3: {
                if (topo == -1) {
                    printf("⚠️ Pilha vazia!\n");
                } else {
                    salvarEstado();
                    Peca usada = pop();
                    enqueue(usada);
                    printf("Peça usada da reserva!\n");
                }
                break;
            }
            case 4:
                trocarTopoFila();
                break;
            case 5:
                desfazer();
                break;
            case 6:
                inverterFilaPilha();
                break;
            case 0:
                printf("Encerrando programa...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}
