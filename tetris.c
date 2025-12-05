
// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.


    // 🧩 Nível Novato: Fila de Peças Futuras
    //
    // - Crie uma struct Peca com os campos: tipo (char) e id (int).
    // - Implemente uma fila circular com capacidade para 5 peças.
    // - Crie funções como inicializarFila(), enqueue(), dequeue(), filaCheia(), filaVazia().
    // - Cada peça deve ser gerada automaticamente com um tipo aleatório e id sequencial.
    // - Exiba a fila após cada ação com uma função mostrarFila().
    // - Use um menu com opções como:
    //      1 - Jogar peça (remover da frente)
    //      0 - Sair
    // - A cada remoção, insira uma nova peça ao final da fila.



    // 🧠 Nível Aventureiro: Adição da Pilha de Reserva
    //
    // - Implemente uma pilha linear com capacidade para 3 peças.
    // - Crie funções como inicializarPilha(), push(), pop(), pilhaCheia(), pilhaVazia().
    // - Permita enviar uma peça da fila para a pilha (reserva).
    // - Crie um menu com opção:
    //      2 - Enviar peça da fila para a reserva (pilha)
    //      3 - Usar peça da reserva (remover do topo da pilha)
    // - Exiba a pilha junto com a fila após cada ação com mostrarPilha().
    // - Mantenha a fila sempre com 5 peças (repondo com gerarPeca()).


    // 🔄 Nível Mestre: Integração Estratégica entre Fila e Pilha
    //
    // - Implemente interações avançadas entre as estruturas:
    //      4 - Trocar a peça da frente da fila com o topo da pilha
    //      5 - Trocar os 3 primeiros da fila com as 3 peças da pilha
    // - Para a opção 4:
    //      Verifique se a fila não está vazia e a pilha tem ao menos 1 peça.
    //      Troque os elementos diretamente nos arrays.
    // - Para a opção 5:
    //      Verifique se a pilha tem exatamente 3 peças e a fila ao menos 3.
    //      Use a lógica de índice circular para acessar os primeiros da fila.
    // - Sempre valide as condições antes da troca e informe mensagens claras ao usuário.
    // - Use funções auxiliares, se quiser, para modularizar a lógica de troca.
    // - O menu deve ficar assim:
    //      4 - Trocar peça da frente com topo da pilha
    //      5 - Trocar 3 primeiros da fila com os 3 da pilha


#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX 5
typedef struct {
    char tipo;
    int id;
} pecas;

//implementando um fila circular para gerenciar as peças
typedef struct {
    pecas itens[MAX];
    int frente;
    int tras;
    int tamanho;
} fila;

//implementando uma pilha para gerenciar as peças
typedef struct {
    pecas itens[3];
    int topo;
} pilha;

//funções da fila
void inicializarFila(fila* f) { // inicializa a fila
    f->frente = 0;
    f->tras = -1;
    f->tamanho = 0;
}
int estaVazia(fila* f) {
    return f->tamanho == 0;
}
int estaCheia(fila* f) {
    return f->tamanho == MAX;
}

void enqueue(fila* f, pecas p) { // adiciona um item ao final da fila
    if (estaCheia(f)) {
        printf("Fila cheia! Nao e possivel adicionar mais pecas.\n");
        return;
    }
    f->tras = (f->tras + 1) % MAX;
    f->itens[f->tras] = p;
    f->tamanho++;
}

void dequeue(fila* f) { // remove o item da frente da fila
    if (estaVazia(f)) {
        printf("Fila vazia! Nao ha pecas para remover.\n");
        return;
    }
    f->frente = (f->frente + 1) % MAX;
    f->tamanho--;
}

int filacheia(fila* f) {
    return f->tamanho == MAX;
}   

int filavazia(fila* f) {
    return f->tamanho == 0;
}

void mostrarFila(fila* f) { // exibe os itens na fila
    if (estaVazia(f)) {
        printf("Fila vazia!\n");
        return;
    }
    printf("Pecas na fila:\n");
    for (int i = 0; i < f->tamanho; i++) {
        int indice = (f->frente + i) % MAX;
        printf("Peca ID: %d, Tipo: %c\n", f->itens[indice].id, f->itens[indice].tipo);
    }
}

//função para inicializar a pilha
void inicializarPilha(pilha* p) {
    p->topo = -1;
}

//push
void push(pilha* p, pecas item) { // adiciona um item ao topo da pilha
    if (p->topo == 2) {
        printf("Pilha cheia! Nao e possivel adicionar mais pecas.\n");
        return;
    }
    p->itens[++(p->topo)] = item;
}

//pop
void pop(pilha* p) { // remove o item do topo da pilha
    if (p->topo == -1) {
        printf("Pilha vazia! Nao ha pecas para remover.\n");
        return;
    }
    p->topo--;
}

//pilha cheia
int pilhacheia(pilha* p) { // verifica se a pilha esta cheia
    return p->topo == 2;
}
//pilha vazia
int pilhavazia(pilha* p) {
    return p->topo == -1;
}

//Enviar uma peça da fila para a pilha (reserva)
void moverFilaParaPilha(fila* f, pilha* p) { // move um item da frente da fila para o topo da pilha
    if (filavazia(f)) {
        printf("Fila vazia! Nao ha pecas para mover.\n");
        return;
    }
    if (pilhacheia(p)) {
        printf("Pilha cheia! Nao e possivel mover mais pecas.\n");
        return;
    }
    pecas item = f->itens[f->frente]; 
    dequeue(f);
    push(p, item);
    printf("Peca ID: %d, Tipo: %c movida da fila para a pilha.\n", item.id, item.tipo);
}
//mostrar pilha
void mostrarPilha(pilha* p) { // exibe os itens na pilha
    if (pilhavazia(p)) {
        printf("Pilha vazia!\n");
        return;
    }
    printf("Pecas na pilha:\n");
    for (int i = p->topo; i >= 0; i--) {
        printf("Peca ID: %d, Tipo: %c\n", p->itens[i].id, p->itens[i].tipo);
    }
}
// gerar peça aleatória
pecas gerarPecaAleatoria(int id) { // gera uma peça com tipo aleatório
    pecas p;
    p.id = id;
    int tipoAleatorio = rand() % 4;
    switch (tipoAleatorio) {
        case 0:
            p.tipo = 'T';
            break;
        case 1:
            p.tipo = 'O';
            break;
        case 2:
            p.tipo = 'L';
            break;
        case 3:
            p.tipo = 'I';
            break;
    }
    return p;
}


//menu
int exibirmenu() { // exibe o menu e retorna a opcao escolhida
    int opcao;
    printf("========= Menu de Pecas =========\n");
    printf("1. Inserir nova peca\n");
    printf("2. Jogar peca(remover da frente)\n");
    printf("3. Mover peca da fila para a pilha (reserva)\n");
    printf("4. Trocar a peca da frente da fila com o topo da pilha\n");
    printf("5. Trocar os 3 primeiros da fila com as 3 pecas da pilha\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);
    return opcao;
}
int main() { // função principal
    fila filaPecas;
    inicializarFila(&filaPecas);
    pilha pilhaReserva;
    inicializarPilha(&pilhaReserva);
    int opcao, id_peca = 1;
    char tipo_peca;

    do { // loop do menu
        opcao = exibirmenu();
        switch (opcao) {
            case 1://inserir peça
               if (filacheia(&filaPecas)) {
                    printf("Fila cheia! Nao e possivel adicionar mais pecas.\n");
                } else {
                    printf("Digite o tipo da peca (T,O,L,I): \n");
                    scanf(" %c", &tipo_peca);
                    pecas novaPeca;
                    novaPeca.id = id_peca++;
                    novaPeca.tipo = tipo_peca;
                    enqueue(&filaPecas, novaPeca);
                    printf("Peca inserida com sucesso na fila.\n");
                    mostrarFila(&filaPecas);
                }
                break;
            case 2://jogar peça
                if (filavazia(&filaPecas)) {
                    printf("Fila vazia! Nao ha pecas para jogar.\n");
                } else {
                    printf("Jogando a peca na frente da fila...\n");
                    dequeue(&filaPecas);
                    printf("Peca jogada com sucesso.\n");
                    mostrarFila(&filaPecas);
                }
                break;
            case 3://mover peça da fila para a pilha
                moverFilaParaPilha(&filaPecas, &pilhaReserva);
                mostrarFila(&filaPecas);
                mostrarPilha(&pilhaReserva);
                break;
            case 4://trocar peça da frente da fila com o topo da pilha
                if (filavazia(&filaPecas)) {
                    printf("Fila vazia! Nao ha pecas para trocar.\n");
                } else if (pilhavazia(&pilhaReserva)) {
                    printf("Pilha vazia! Nao ha pecas para trocar.\n");
                } else {
                    pecas pecaFila = filaPecas.itens[filaPecas.frente];
                    pecas pecaPilha = pilhaReserva.itens[pilhaReserva.topo];
                    filaPecas.itens[filaPecas.frente] = pecaPilha;
                    pilhaReserva.itens[pilhaReserva.topo] = pecaFila;
                    printf("Pecas trocadas com sucesso.\n");
                    mostrarFila(&filaPecas);
                    mostrarPilha(&pilhaReserva);
                }
                break;
            case 5://trocar os 3 primeiros da fila com as 3 peças da pilha
                if (filaPecas.tamanho < 3) {
                    printf("Nao ha pecas suficientes na fila para trocar.\n");
                } else if (pilhaReserva.topo < 2) {
                    printf("Nao ha pecas suficientes na pilha para trocar.\n");
                } else {
                    for (int i = 0; i < 3; i++) {
                        pecas pecaFila = filaPecas.itens[(filaPecas.frente + i) % MAX];
                        pecas pecaPilha = pilhaReserva.itens[pilhaReserva.topo - i];
                        filaPecas.itens[(filaPecas.frente + i) % MAX] = pecaPilha;
                        pilhaReserva.itens[pilhaReserva.topo - i] = pecaFila;
                    }
                    printf("As 3 primeiras pecas da fila foram trocadas com as 3 pecas da pilha com sucesso.\n");
                    mostrarFila(&filaPecas);
                    mostrarPilha(&pilhaReserva);
                }
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
    }

    } while (opcao != 0);

        // Preencher a fila até o máximo
        while (!filacheia(&filaPecas)) {
            pecas pecaAleatoria = gerarPecaAleatoria(id_peca++);
            enqueue(&filaPecas, pecaAleatoria);
        }

    return 0;
}