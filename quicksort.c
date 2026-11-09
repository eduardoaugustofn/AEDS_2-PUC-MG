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

void swap(Veiculo *a, Veiculo *b) {
    Veiculo temp = *a;
    *a = *b;
    *b = temp;
}

int comparar(Veiculo a, Veiculo b) {
    if (a.consumoEstrada < b.consumoEstrada) return -1;
    if (a.consumoEstrada > b.consumoEstrada) return 1;
    return strcmp(a.marca, b.marca);
}

void quicksort(Veiculo veiculos[], int tam, int inicio) {
    if ((tam - inicio) > 1) {
        int esq = inicio;
        int dir = tam - 1;
        Veiculo pivo = veiculos[(esq + dir) / 2];

        while (esq <= dir) {
            while (comparar(veiculos[esq], pivo) < 0) {
                esq++;
            }

            while (comparar(veiculos[dir], pivo) > 0) {
                dir--;
            }

            if (esq <= dir) {
                swap(&veiculos[esq], &veiculos[dir]);
                esq++;
                dir--;
            }
        }

        if (inicio < dir) {
            quicksort(veiculos, dir + 1, inicio);
        }

        if (esq < tam - 1) {
            quicksort(veiculos, tam, esq);
        }
    }
}

int main() {
    FILE *arquivo = fopen("/tmp/veiculos.csv", "r");
    Veiculo veiculos[500];
    int quantidade = 0;

    char linha[500];
    int ids[500];
    Veiculo selecionados[500];

    if (arquivo != NULL) {
        fgets(linha, 500, arquivo);

        while (fgets(linha, 500, arquivo) != NULL) {
            veiculos[quantidade] = lerVeiculo(linha);
            quantidade++;
        }

        fclose(arquivo);
    }

    int i = 0;

    while (1) {
        scanf("%d", &ids[i]);

        if (ids[i] == -1) {
            break;
        }

        for (int j = 0; j < quantidade; j++) {
            if (veiculos[j].id == ids[i]) {
                selecionados[i] = veiculos[j];
                i++;
                break;
            }
        }
    }

    quicksort(selecionados, i, 0);

    for (int j = 0; j < i; j++) {
        mostrarVeiculo(selecionados[j]);
    }
    return 0;
}