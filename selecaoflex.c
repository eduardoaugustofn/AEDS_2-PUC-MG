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

void mystrcpy(char *destino, const char *origem) {
    int i = 0;
    while (origem[i] != '\0') {
        destino[i] = origem[i];
        i++;
    }
    destino[i] = '\0';
}

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
    mystrcpy(combustiveis, v.combustivel);

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
    mystrcpy(v.marca, parte);

    parte = strtok(NULL, ",");
    mystrcpy(v.modelo, parte);

    parte = strtok(NULL, ",");
    v.ano = atoi(parte);

    parte = strtok(NULL, ",");
    mystrcpy(v.categoria, parte);

    parte = strtok(NULL, ",");
    mystrcpy(v.combustivel, parte);

    parte = strtok(NULL, ",");
    v.cilindros = atoi(parte);

    parte = strtok(NULL, ",");
    v.cilindrada = atof(parte);

    parte = strtok(NULL, ",");
    mystrcpy(v.transmissao, parte);

    parte = strtok(NULL, ",");
    mystrcpy(v.tracao, parte);

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

int buscarVeiculo(Veiculo veiculos[], int quantidade, int id) {
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
    No *fim;
} Lista;

void inicializarLista(Lista *lista) {
    lista->inicio = NULL;
    lista->fim = NULL;
}

void inserirFim(Lista *lista, Veiculo v) {
    No *novo = (No *)malloc(sizeof(No));
    novo->veiculo = v;
    novo->prox = NULL;

    if (lista->inicio == NULL) {
        lista->inicio = novo;
    } else {
        lista->fim->prox = novo;
    }

    lista->fim = novo;
}

char minuscula(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + 32;
    }
    return c;
}

int compararModelo(char a[], char b[]) {
    int i = 0;

    while (a[i] != '\0' && b[i] != '\0') {
        char ca = minuscula(a[i]);
        char cb = minuscula(b[i]);

        if (ca != cb) {
            return ca - cb;
        }

        i++;
    }

    return minuscula(a[i]) - minuscula(b[i]);
}

void selecaoLista(Lista *lista) {
    for (No *i = lista->inicio; i != NULL; i = i->prox) {
        No *menor = i;

        for (No *j = i->prox; j != NULL; j = j->prox) {
            if (compararModelo(j->veiculo.modelo, menor->veiculo.modelo) < 0) {
                menor = j;
            }
        }

        Veiculo temp = i->veiculo;
        i->veiculo = menor->veiculo;
        menor->veiculo = temp;
    }
}

void mostrarLista(Lista *lista) {
    for (No *aux = lista->inicio; aux != NULL; aux = aux->prox) {
        mostrarVeiculo(aux->veiculo);
    }
}

void liberarLista(Lista *lista) {
    No *aux = lista->inicio;

    while (aux != NULL) {
        No *prox = aux->prox;
        free(aux);
        aux = prox;
    }

    lista->inicio = NULL;
    lista->fim = NULL;
}

int main() {
    FILE *arquivo = fopen("/tmp/veiculos.csv", "r");
    Veiculo veiculos[500];
    int quantidade = 0;

    char linha[500];

    if (arquivo != NULL) {
        fgets(linha, 500, arquivo);

        while (fgets(linha, 500, arquivo) != NULL) {
            veiculos[quantidade] = lerVeiculo(linha);
            quantidade++;
        }

        fclose(arquivo);
    }

    Lista lista;
    inicializarLista(&lista);

    int id;

    while (1) {
        scanf("%d", &id);

        if (id == -1) {
            break;
        }

        int posicao = buscarVeiculo(veiculos, quantidade, id);

        if (posicao != -1) {
            inserirFim(&lista, veiculos[posicao]);
        }
    }

    selecaoLista(&lista);

    mostrarLista(&lista);

    liberarLista(&lista);

    return 0;
}