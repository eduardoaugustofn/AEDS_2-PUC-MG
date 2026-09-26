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

typedef struct {
    Veiculo dados[5];
    int inicio;
    int fim;
    int qtd;
} FilaCircular;

void inicializarFila(FilaCircular *fila) {
    fila->inicio = 0;
    fila->fim = 0;
    fila->qtd = 0;
}

Veiculo desenfileirar(FilaCircular *fila) {
    Veiculo v = fila->dados[fila->inicio];
    fila->inicio = (fila->inicio + 1) % 5;//passa todos pra dir
    fila->qtd--;
    return v;
}

void enfileirar(FilaCircular *fila, Veiculo v) {
    if (fila->qtd == 5) {
        Veiculo removido = desenfileirar(fila);
        printf("(R) %s %s\n", removido.marca, removido.modelo);
    }

    fila->dados[fila->fim] = v; //veiculo na pos fim
    fila->fim = (fila->fim + 1) % 5;
    fila->qtd++;
}

void mostrarFila(FilaCircular *fila) {
    int idx = fila->inicio;
    for (int i = 0; i < fila->qtd; i++) {
        mostrarVeiculo(fila->dados[idx]);
        idx = (idx + 1) % 5;
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

    FilaCircular fila;
    inicializarFila(&fila);

    int id;
    scanf("%d", &id);

    while (id != -1) {
        int pos = buscarPorId(veiculos, quantidade, id);
        if (pos != -1) {
            enfileirar(&fila, veiculos[pos]);
        }
        scanf("%d", &id);
    }

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        char comando[10];
        scanf("%s", comando);

        if (strcmp(comando, "I") == 0) {
            int idInserir;
            scanf("%d", &idInserir);
            int pos = buscarPorId(veiculos, quantidade, idInserir);
            if (pos != -1) {
                enfileirar(&fila, veiculos[pos]);
            }
        } else if (strcmp(comando, "R") == 0) {
            Veiculo removido = desenfileirar(&fila);
            printf("(R) %s %s\n", removido.marca, removido.modelo);
        }
    }

    mostrarFila(&fila);

    return 0;
}