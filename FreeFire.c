#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Estrutura que representa um item do inventário
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// === Funções do sistema ===
void inserirItem(Item mochila[], int *qtd, int *espacoUsado);
void removerItem(Item mochila[], int *qtd, int *espacoUsado);
void listarItens(Item mochila[], int qtd, int espacoUsado);
void buscarItem(Item mochila[], int qtd);
void exibirCabecalho();

int main() {
    Item mochila[10];        // Vetor que armazena até 10 itens diferentes
    int qtd = 0;             // Quantidade de tipos de itens cadastrados
    int espacoUsado = 0;     // Soma total das quantidades (ocupação da mochila)
    int opcao;

    exibirCabecalho(); // Exibe o título do jogo no início

    do {
        printf("\n========== MENU PRINCIPAL ==========\n");
        printf("Itens na mochila: %d / 100\n", espacoUsado);
        printf("-----------------------------------\n");
        printf("1 - Adicionar item (loot)\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // limpa buffer

        switch (opcao) {
            case 1:
                inserirItem(mochila, &qtd, &espacoUsado);
                break;
            case 2:
                removerItem(mochila, &qtd, &espacoUsado);
                break;
            case 3:
                listarItens(mochila, qtd, espacoUsado);
                break;
            case 4:
                buscarItem(mochila, qtd);
                break;
            case 0:
                printf("\nEncerrando o sistema de inventario...\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}

// =================== FUNÇÕES ===================

// Função que exibe o título do jogo
void exibirCabecalho() {
    printf("===========================================================\n");
    printf("      Mochila de Sobrevivencia - Codigo da Ilha \n");
    printf("===========================================================\n");
    printf("Prepare-se para sobreviver! Colete e organize seus itens.\n");
}

// Função para inserir um novo item na mochila
void inserirItem(Item mochila[], int *qtd, int *espacoUsado) {
    if (*qtd >= 10) {
        printf("\nA mochila esta cheia! Nao e possivel adicionar mais tipos de itens.\n");
        return;
    }

    Item novo;

    printf("\n=== CADASTRO DE ITEM ===\n");
    printf("Nome do item: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0'; // remove o \n

    printf("Tipo (ex: arma, municao, cura, ferramenta): ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar(); // limpar buffer

    // Verifica se a mochila ainda tem espaço
    if (*espacoUsado + novo.quantidade > 100) {
        printf("\nNao ha espaco suficiente na mochila!\n");
        printf("Espaco disponivel: %d\n", 100 - *espacoUsado);
        return;
    }

    mochila[*qtd] = novo;
    (*qtd)++;
    *espacoUsado += novo.quantidade;

    printf("\nItem adicionado com sucesso!\n");
    listarItens(mochila, *qtd, *espacoUsado);
}

// Função para remover um item da mochila
void removerItem(Item mochila[], int *qtd, int *espacoUsado) {
    if (*qtd == 0) {
        printf("\nA mochila esta vazia! Nenhum item para remover.\n");
        return;
    }

    char nomeRemover[30];
    printf("\nDigite o nome do item que deseja remover: ");
    fgets(nomeRemover, sizeof(nomeRemover), stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

    int encontrado = 0;
    for (int i = 0; i < *qtd; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            encontrado = 1;
            *espacoUsado -= mochila[i].quantidade; // Libera espaço
            for (int j = i; j < *qtd - 1; j++) {
                mochila[j] = mochila[j + 1]; // desloca itens
            }
            (*qtd)--;
            printf("\nItem '%s' removido com sucesso!\n", nomeRemover);
            break;
        }
    }

    if (!encontrado)
        printf("\nItem nao encontrado na mochila!\n");

    listarItens(mochila, *qtd, *espacoUsado);
}

// Função para listar todos os itens da mochila
void listarItens(Item mochila[], int qtd, int espacoUsado) {
    printf("\n=== ITENS NA MOCHILA ===\n");
    printf("Espaco ocupado: %d / 100\n", espacoUsado);
    printf("---------------------------------\n");

    if (qtd == 0) {
        printf("Mochila vazia!\n");
    } else {
        for (int i = 0; i < qtd; i++) {
            printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
                   i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
        }
    }
}

// Função de busca sequencial por nome do item
void buscarItem(Item mochila[], int qtd) {
    if (qtd == 0) {
        printf("\nA mochila esta vazia! Nenhum item para buscar.\n");
        return;
    }

    char nomeBusca[30];
    printf("\nDigite o nome do item que deseja buscar: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < qtd; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\nItem encontrado!\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            return;
        }
    }

    printf("\nItem '%s' nao encontrado na mochila.\n", nomeBusca);
}
