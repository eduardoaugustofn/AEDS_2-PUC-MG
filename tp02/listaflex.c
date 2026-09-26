#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int ano;
    int mes;
    int dia;
} Data;

typedef struct {
    int id;
    char marca[100];
    char modelo[100];
    int ano;
    char categoria[100];
    char combustivel[100];
    int cilindros;
    double cilindrada;
    char transmissao[100];
    char tracao[100];
    double consumoCidade;
    double consumoEstrada;
    double co2;
    int turbo;
    Data dataRegistro;
} Veiculo;

void mostrarData(Data data) {
    printf("%02d/%02d/%04d", data.dia, data.mes, data.ano);
}

void mostrarVeiculo(Veiculo v) {
    printf("[%d ## %s ## %s ## %d ## %s ## [",
           v.id,
           v.marca,
           v.modelo,
           v.ano,
           v.categoria);

    char combustiveis[100];
    strcpy(combustiveis, v.combustivel);

    char *parte = strtok(combustiveis, ";");

    while (parte != NULL) {
        printf("%s", parte);
        parte = strtok(NULL, ";");
        if (parte != NULL) {
            printf(",");
        }
    }

    printf("] ## %d ## %.1f ## %s ## %s ## %.2f ## %.2f ## %.1f ## %s ## ",
           v.cilindros,
           v.cilindrada,
           v.transmissao,
           v.tracao,
           v.consumoCidade,
           v.consumoEstrada,
           v.co2,
           v.turbo ? "true" : "false");

    mostrarData(v.dataRegistro);

    printf("]\n");
}

Veiculo lerVeiculo(char linha[]) {
    Veiculo v;
    char *parte;

    parte = strtok(linha, ",");
    v.id = atoi(parte);

    parte = strtok(NULL, ",");
    strcpy(v.marca, parte);

    parte = strtok(NULL, ",");
    strcpy(v.modelo, parte);

    parte = strtok(NULL, ",");
    v.ano = atoi(parte);

    parte = strtok(NULL, ",");
    strcpy(v.categoria, parte);

    parte = strtok(NULL, ",");
    strcpy(v.combustivel, parte);

    parte = strtok(NULL, ",");
    v.cilindros = atoi(parte);

    parte = strtok(NULL, ",");
    v.cilindrada = atof(parte);

    parte = strtok(NULL, ",");
    strcpy(v.transmissao, parte);

    parte = strtok(NULL, ",");
    strcpy(v.tracao, parte);

    parte = strtok(NULL, ",");
    v.consumoCidade = atof(parte);

    parte = strtok(NULL, ",");
    v.consumoEstrada = atof(parte);

    parte = strtok(NULL, ",");
    v.co2 = atof(parte);

    parte = strtok(NULL, ",");
    v.turbo = strcmp(parte, "true") == 0;

    parte = strtok(NULL, ",");
    sscanf(parte, "%d-%d-%d",
           &v.dataRegistro.ano,
           &v.dataRegistro.mes,
           &v.dataRegistro.dia);

    return v;
}

int buscarPorId(Veiculo veiculos[], int quantidade, int id) {
    for (int i = 0; i < quantidade; i++) {
        if (veiculos[i].id == id) {
            return i;
        }
    }
    return -1;
}

typedef struct No {
    Veiculo veiculo;
    struct No *prox;
} No;

typedef struct {
    No *inicio;
} Lista;

void inicializarLista(Lista *lista) {
    lista->inicio = NULL;
}

void inserirInicio(Lista *lista, Veiculo v) {
    No *novo = (No *)malloc(sizeof(No));
    novo->veiculo = v;
    novo->prox = lista->inicio;
    lista->inicio = novo;
}

void inserir(Lista *lista, Veiculo v, int posicao) {
    if (posicao == 0) {
        inserirInicio(lista, v);
        return;
    }

    // tmp vai andando pela lista até chegar no nó anterior da posicao 
    No *tmp = lista->inicio;
    for (int i = 0; i < posicao - 1; i++) {
        tmp = tmp->prox;
    }

    No *novo = (No *)malloc(sizeof(No));
    novo->veiculo = v;
    novo->prox = tmp->prox;
    tmp->prox = novo;
}

void inserirFim(Lista *lista, Veiculo v) {
    No *novo = (No *)malloc(sizeof(No));
    novo->veiculo = v;
    novo->prox = NULL;

    if (lista->inicio == NULL) {
        lista->inicio = novo;
        return;
    }

    // se a lista tá viva, esse loop anda até o último nó, o prox do ult é NULL 
    No *tmp = lista->inicio;
    while (tmp->prox != NULL) {
        tmp = tmp->prox;
    }
    tmp->prox = novo;
}

Veiculo removerInicio(Lista *lista) {
    No *removido = lista->inicio;
    Veiculo v = removido->veiculo;
    lista->inicio = removido->prox;
    free(removido);
    return v;
}

Veiculo remover(Lista *lista, int posicao) {
    if (posicao == 0) {
        return removerInicio(lista);
    }

    // nesse caso o tmp fica na casa anterior ao que vai sair 
    No *tmp = lista->inicio;
    for (int i = 0; i < posicao - 1; i++) {
        tmp = tmp->prox;
    }

    No *removido = tmp->prox;
    Veiculo v = removido->veiculo;
    tmp->prox = removido->prox;
    free(removido);
    return v;
}

Veiculo removerFim(Lista *lista) {
    No *tmp = lista->inicio;

    if (tmp->prox == NULL) {
        Veiculo v = tmp->veiculo;
        free(tmp);
        lista->inicio = NULL;
        return v;
    }

    // aqui vai parar no penultimo nó pq o ultimo tem q ser apagado 
    while (tmp->prox->prox != NULL) {
        tmp = tmp->prox;
    }

    No *removido = tmp->prox;
    Veiculo v = removido->veiculo;
    free(removido);
    tmp->prox = NULL;
    return v;
}

void mostrarLista(Lista *lista) {
    No *tmp = lista->inicio;
    while (tmp != NULL) {
        mostrarVeiculo(tmp->veiculo);
        tmp = tmp->prox;
    }
}

int main() {
    FILE *arquivo = fopen("/tmp/veiculos.csv", "r");

    Veiculo veiculos[500];
    int quantidade = 0;

    char linha[500];

    fgets(linha, 500, arquivo);

    while (fgets(linha, 500, arquivo) != NULL) {
        veiculos[quantidade] = lerVeiculo(linha);
        quantidade++;
    }

    fclose(arquivo);

    Lista lista;
    inicializarLista(&lista);

    int id;
    scanf("%d", &id);

    while (id != -1) {
        int pos = buscarPorId(veiculos, quantidade, id);
        if (pos != -1) {
            inserirFim(&lista, veiculos[pos]);
        }
        scanf("%d", &id);
    }

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        char comando[10];
        scanf("%s", comando);

        Veiculo removido;
        int removeu = 0;

        if (strcmp(comando, "II") == 0) {
            int idInserir;
            scanf("%d", &idInserir);
            int pos = buscarPorId(veiculos, quantidade, idInserir);
            if (pos != -1) {
                inserirInicio(&lista, veiculos[pos]);
            }
        } else if (strcmp(comando, "I*") == 0) {
            int posicao, idInserir;
            scanf("%d %d", &posicao, &idInserir);
            int pos = buscarPorId(veiculos, quantidade, idInserir);
            if (pos != -1) {
                inserir(&lista, veiculos[pos], posicao);
            }
        } else if (strcmp(comando, "IF") == 0) {
            int idInserir;
            scanf("%d", &idInserir);
            int pos = buscarPorId(veiculos, quantidade, idInserir);
            if (pos != -1) {
                inserirFim(&lista, veiculos[pos]);
            }
        } else if (strcmp(comando, "RI") == 0) {
            removido = removerInicio(&lista);
            removeu = 1;
        } else if (strcmp(comando, "R*") == 0) {
            int posicao;
            scanf("%d", &posicao);
            removido = remover(&lista, posicao);
            removeu = 1;
        } else if (strcmp(comando, "RF") == 0) {
            removido = removerFim(&lista);
            removeu = 1;
        }

        if (removeu) {
            printf("(R)%s %s\n", removido.marca, removido.modelo);
        }
    }

    mostrarLista(&lista);

    return 0;
}