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

void selecaomodelo(Veiculo veiculos[], int tam) {
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
void swap(Veiculo *a, Veiculo *b) {
    Veiculo temp = *a;
    *a = *b;
    *b = temp;
}

void quicksort(Veiculo veiculos[],int tam,int inicio){//ordena por consumo estrada desempate marca
if((tam - inicio) > 1){

int pivoIdx = (inicio + tam)/2;
int i = inicio;
int j = tam - 1;

while(i < j) {
    while(i < j && veiculos[i].consumoEstrada <= veiculos[pivoIdx].consumoEstrada) {
        i++;
    }
    
    while(i < j && veiculos[j].consumoEstrada >= veiculos[pivoIdx].consumoEstrada) {
        j--;
    }
    
    if(i < j) {
        swap(&veiculos[i], &veiculos[j]);
        i++;
        j--;
    }
}
quicksort(veiculos, i, inicio);
quicksort(veiculos, tam, i);

}// fim do while
}

int main() {
printf("ENTROU NO MAIN\n");

    FILE *arquivo = fopen("veiculos.csv", "r"); // veiculos.csv
    Veiculo veiculos[500];
    int quantidade = 0;

    char linha[500];
    int ids[500];
    Veiculo selecionados[500];

    fgets(linha, 500, arquivo);

    while (fgets(linha, 500, arquivo) != NULL) {

        veiculos[quantidade] = lerVeiculo(linha);
        quantidade++;
    }

    fclose(arquivo);



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

quicksort(selecionados,i,0);

for (int j = 0; j < i; j++) {
    mostrarVeiculo(selecionados[j]);
}
    return 0;
}

