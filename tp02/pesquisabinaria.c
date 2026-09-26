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

void selecaoModelo(Veiculo veiculos[], int tam) {
    for (int i = 0; i < tam - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < tam; j++) {
            if (strcmp(veiculos[j].modelo, veiculos[min_idx].modelo) < 0) {
                min_idx = j;
            }
        }

        Veiculo temp = veiculos[i];
        veiculos[i] = veiculos[min_idx];
        veiculos[min_idx] = temp;
    }
}

int buscaBinariaModelo(Veiculo veiculos[], int n, char modelo[]) {
    int esq = 0;
    int dir = n - 1;

    while (esq <= dir) {
        int meio = (esq + dir) / 2;
        int comp = strcmp(veiculos[meio].modelo, modelo);

        if (comp == 0) {
            return meio;
        } else if (comp < 0) {
            esq = meio + 1;
        } else {
            dir = meio - 1;
        }
    }

    return -1;
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
        for (int i = 0; i < quantidade; i++) {
            if (veiculos[i].id == id) {
                veiculosPesquisa[qtdPesquisa] = veiculos[i];
                qtdPesquisa++;
                break;
            }
        }
        scanf("%d", &id);
    }

    getchar();

    selecaoModelo(veiculosPesquisa, qtdPesquisa);

    char entrada[100];

    while (fgets(entrada, 100, stdin) != NULL) {
        entrada[strcspn(entrada, "\n")] = 0;

        if (strcmp(entrada, "FIM") == 0) {
            break;
        }

        int pos = buscaBinariaModelo(veiculosPesquisa, qtdPesquisa, entrada);

        if (pos != -1) {
            printf("SIM\n");
        } else {
            printf("NAO\n");
        }
    }

    return 0;
}