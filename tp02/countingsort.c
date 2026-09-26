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

int buscarVeiculo(Veiculo veiculos[], int quantidade, int id) {
    for (int i = 0; i < quantidade; i++) {
        if (veiculos[i].id == id) {
            return i;
        }
    }
    return -1;
}

void countingSort(Veiculo veiculos[], int n) {
    int maxCilindros = 0;
    for (int i = 0; i < n; i++) {
        if (veiculos[i].cilindros > maxCilindros) {
            maxCilindros = veiculos[i].cilindros;
        }
    }

    int *count = (int *)malloc((maxCilindros + 1) * sizeof(int));
    for (int i = 0; i <= maxCilindros; i++) {
        count[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        count[veiculos[i].cilindros]++;
    }

    for (int i = 1; i <= maxCilindros; i++) {
        count[i] += count[i - 1];
    }

    Veiculo *output = (Veiculo *)malloc(n * sizeof(Veiculo));

    for (int i = n - 1; i >= 0; i--) {
        int idx = count[veiculos[i].cilindros] - 1;
        output[idx] = veiculos[i];
        count[veiculos[i].cilindros]--;
    }

    for (int i = 0; i < n; i++) {
        veiculos[i] = output[i];
    }

    free(count);
    free(output);
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

    Veiculo veiculosPesquisa[500];
    int qtdPesquisa = 0;

    int id;
    scanf("%d", &id);

    while (id != -1) {
        int posicao = buscarVeiculo(veiculos, quantidade, id);
        if (posicao != -1) {
            veiculosPesquisa[qtdPesquisa] = veiculos[posicao];
            qtdPesquisa++;
        }
        scanf("%d", &id);
    }

    countingSort(veiculosPesquisa, qtdPesquisa);

    for (int i = 0; i < qtdPesquisa; i++) {
        mostrarVeiculo(veiculosPesquisa[i]);
    }

    return 0;
}