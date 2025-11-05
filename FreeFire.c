#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

#define MAX 20

void adicionarComponente(Componente componentes[], int *qtd);
void removerComponente(Componente componentes[], int *qtd);
void listarComponentes(Componente componentes[], int qtd);
void bubbleSortNome(Componente componentes[], int qtd, int *comparacoes);
void insertionSortTipo(Componente componentes[], int qtd, int *comparacoes);
void selectionSortPrioridade(Componente componentes[], int qtd, int *comparacoes);
int buscaBinariaPorNome(Componente componentes[], int qtd, char nome[]);
void mostrarMenu(Componente componentes[], int qtd, int ordenadoNome);


int main() {
    Componente componentes[MAX];
    int qtd = 0;
    int opcao;
    int ordenadoNome = 0;

    do {
        mostrarMenu(componentes, qtd, ordenadoNome);

        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); 

        switch(opcao) {
            case 1:
                adicionarComponente(componentes, &qtd);
                break;
            case 2:
                removerComponente(componentes, &qtd);
                break;
            case 3:
                listarComponentes(componentes, qtd);
                break;
            case 4: {
                int tipoOrdenacao, comparacoes = 0;
                clock_t inicio, fim;
                double tempo;

                printf("\nEscolha o metodo de ordenacao:\n");
                printf("1.(por Nome)\n");
                printf("2.(por Tipo)\n");
                printf("3.(por Prioridade)\n");
                printf("Opcao: ");
                scanf("%d", &tipoOrdenacao);
                getchar();

                inicio = clock();
                if (tipoOrdenacao == 1) {
                    bubbleSortNome(componentes, qtd, &comparacoes);
                    ordenadoNome = 1;
                } else if (tipoOrdenacao == 2) {
                    insertionSortTipo(componentes, qtd, &comparacoes);
                    ordenadoNome = 0;
                } else if (tipoOrdenacao == 3) {
                    selectionSortPrioridade(componentes, qtd, &comparacoes);
                    ordenadoNome = 0;
                } else {
                    printf("Opcao invalida!\n");
                    break;
                }
                fim = clock();
                tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

                printf("\nComponentes ordenados com sucesso!\n");
                printf("Comparacoes realizadas: %d\n", comparacoes);
                printf("Tempo de execucao: %.4f segundos\n", tempo);
                listarComponentes(componentes, qtd);
                break;
            }
            case 5:
                if (ordenadoNome == 0) {
                    printf("\nA busca binaria so pode ser feita apos ordenacao por NOME! Escolha a opção 4!\n");
                } else {
                    char chave[30];
                    printf("\nDigite o nome do componente-chave: ");
                    fgets(chave, sizeof(chave), stdin);
                    chave[strcspn(chave, "\n")] = '\0';
                    int pos = buscaBinariaPorNome(componentes, qtd, chave);
                    if (pos != -1)
                        printf("\nComponente encontrado: %s | Tipo: %s | Prioridade: %d\n",
                            componentes[pos].nome, componentes[pos].tipo, componentes[pos].prioridade);
                    else
                        printf("\nComponente nao encontrado!\n");
                }
                break;
            case 6:
                printf("\n*** TORRE DE FUGA ATIVADA! ***\n");
                printf("Parabens, voce concluiu o desafio final!\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

    } while(opcao != 6);

    return 0;
}


void mostrarMenu(Componente componentes[], int qtd, int ordenadoNome) {
    printf("\n====================================================\n");
    printf("       PLANO DE FUGA - CODIGO DA ILHA (NIVEL MESTRE)\n");
    printf("====================================================\n");
    printf("Itens na Mochila: %d/%d\n", qtd, MAX);
    printf("Status da Ordenacao por Nome: %s\n", ordenadoNome ? "ORDENADO" : "NAO ORDENADO");
    printf("\n1. Adicionar Componente\n");
    printf("2. Descartar Componente\n");
    printf("3. Listar Componentes (Inventario)\n");
    printf("4. Organizar Mochila (Ordenar Componentes)\n");
    printf("5. Busca Binaria por Componente-Chave (por nome)\n");
    printf("6. ATIVAR TORRE DE FUGA (Sair)\n");
    printf("----------------------------------------------------\n");
}

void adicionarComponente(Componente componentes[], int *qtd) {
    if (*qtd >= MAX) {
        printf("\nMochila cheia!\n");
        return;
    }

    printf("\nNome do componente: ");
    fgets(componentes[*qtd].nome, sizeof(componentes[*qtd].nome), stdin);
    componentes[*qtd].nome[strcspn(componentes[*qtd].nome, "\n")] = '\0';

    printf("Tipo (Estrutural, Eletronico, Energia): ");
    fgets(componentes[*qtd].tipo, sizeof(componentes[*qtd].tipo), stdin);
    componentes[*qtd].tipo[strcspn(componentes[*qtd].tipo, "\n")] = '\0';

    printf("Prioridade (1-10): ");
    scanf("%d", &componentes[*qtd].prioridade);
    getchar();

    (*qtd)++;
    printf("\nComponente adicionado com sucesso!\n");
}

void removerComponente(Componente componentes[], int *qtd) {
    if (*qtd == 0) {
        printf("\nMochila vazia!\n");
        return;
    }

    char nome[30];
    printf("\nDigite o nome do componente a ser removido: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (int i = 0; i < *qtd; i++) {
        if (strcmp(componentes[i].nome, nome) == 0) {
            for (int j = i; j < *qtd - 1; j++) {
                componentes[j] = componentes[j + 1];
            }
            (*qtd)--;
            printf("\nComponente removido com sucesso!\n");
            return;
        }
    }
    printf("\nComponente nao encontrado!\n");
}

void listarComponentes(Componente componentes[], int qtd) {
    if (qtd == 0) {
        printf("\nNenhum componente cadastrado!\n");
        return;
    }

    printf("\n--- Inventario de Componentes ---\n");
    for (int i = 0; i < qtd; i++) {
        printf("%d. Nome: %s | Tipo: %s | Prioridade: %d\n",
               i + 1, componentes[i].nome, componentes[i].tipo, componentes[i].prioridade);
    }
}

void bubbleSortNome(Componente componentes[], int qtd, int *comparacoes) {
    for (int i = 0; i < qtd - 1; i++) {
        for (int j = 0; j < qtd - i - 1; j++) {
            (*comparacoes)++;
            if (strcmp(componentes[j].nome, componentes[j + 1].nome) > 0) {
                Componente temp = componentes[j];
                componentes[j] = componentes[j + 1];
                componentes[j + 1] = temp;
            }
        }
    }
}

void insertionSortTipo(Componente componentes[], int qtd, int *comparacoes) {
    for (int i = 1; i < qtd; i++) {
        Componente chave = componentes[i];
        int j = i - 1;
        while (j >= 0 && strcmp(componentes[j].tipo, chave.tipo) > 0) {
            (*comparacoes)++;
            componentes[j + 1] = componentes[j];
            j--;
        }
        componentes[j + 1] = chave;
    }
}

void selectionSortPrioridade(Componente componentes[], int qtd, int *comparacoes) {
    for (int i = 0; i < qtd - 1; i++) {
        int min = i;
        for (int j = i + 1; j < qtd; j++) {
            (*comparacoes)++;
            if (componentes[j].prioridade < componentes[min].prioridade)
                min = j;
        }
        Componente temp = componentes[i];
        componentes[i] = componentes[min];
        componentes[min] = temp;
    }
}

int buscaBinariaPorNome(Componente componentes[], int qtd, char nome[]) {
    int inicio = 0, fim = qtd - 1;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        int cmp = strcmp(nome, componentes[meio].nome);
        if (cmp == 0)
            return meio;
        else if (cmp > 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }
    return -1;
}
