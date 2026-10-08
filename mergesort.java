
import java.util.Scanner;
import java.io.File;

public class mergesort{

    public static class Data{
        private int ano;
        private int mes;
        private int dia;

        public Data(int ano,int mes,int dia){
          this.dia= dia;
          this.mes= mes;
          this.ano= ano;  
        }

        public String format(){
            return String.format("%02d/%02d/%04d", this.dia, this.mes, this.ano);
        }

    }


    public static class Veiculo{


        private int id;
        private String marca;
        private String modelo;
        private int ano;
        private String categoria;
        private String[] combustivel;
        private int cilindros;
        private double cilindrada;
        private String transmissao;
        private String tracao;
        private double consumoCidade;
        private double consumoEstrada;
        private double co2;
        private boolean turbo;
        private Data dataRegistro;

public int getId() { return this.id; }
public String getMarca() { return this.marca; }
public String getModelo() { return this.modelo; }
public int getAno() { return this.ano; }
public String getCategoria() { return this.categoria; }
public String[] getCombustivel() { return this.combustivel; }
public int getCilindros() { return this.cilindros; }
public double getCilindrada() { return this.cilindrada; }
public String getTransmissao() { return this.transmissao; }
public String getTracao() { return this.tracao; }
public double getConsumoCidade() { return this.consumoCidade; }
public double getConsumoEstrada() { return this.consumoEstrada; }
public double getCo2() { return this.co2; }
public boolean getTurbo() { return this.turbo; }
public Data getDataRegistro() { return this.dataRegistro; }

    public static Veiculo parseVeiculo(String s){ // le uma linha e transforma em veiculo
        String[] partes = s.split(",");

            int id = Integer.parseInt(partes[0]);
            String marca = partes[1];
            String modelo = partes[2];
            int ano = Integer.parseInt(partes[3]);
            String categoria = partes[4];
            String[] combustivel = partes[5].split(";");
            int cilindros = Integer.parseInt(partes[6]);
            double cilindrada = Double.parseDouble(partes[7]);
            String transmissao = partes[8];
            String tracao = partes[9];
            double consumoCidade = Double.parseDouble(partes[10]);
            double consumoEstrada = Double.parseDouble(partes[11]);
            double co2 = Double.parseDouble(partes[12]);
            boolean turbo = Boolean.parseBoolean(partes[13]);
        
            String[] dataParts = partes[14].split("-");
            Data dataRegistro = new Data(
            Integer.parseInt(dataParts[0]),
            Integer.parseInt(dataParts[1]),
            Integer.parseInt(dataParts[2])
    );

        return new Veiculo(id, marca, modelo, ano, categoria, combustivel, 
                       cilindros, cilindrada, transmissao, tracao, 
                       consumoCidade, consumoEstrada, co2, turbo, dataRegistro);

  } // fim do parse
    
  
public void setConsumoCidade(double consumoCidade) { this.consumoCidade = consumoCidade; }
public void setConsumoEstrada(double consumoEstrada) { this.consumoEstrada = consumoEstrada; }
public void setCo2(double co2) { this.co2 = co2; }
public void setTurbo(boolean turbo) { this.turbo = turbo; }

public Veiculo(int id, String marca, String modelo, int ano, String categoria, 
                   String[] combustivel, int cilindros, double cilindrada, 
                   String transmissao, String tracao, double consumoCidade, 
                   double consumoEstrada, double co2, boolean turbo, Data dataRegistro) {
        this.id = id;
        this.marca = marca;
        this.modelo = modelo;
        this.ano = ano;
        this.categoria = categoria;
        this.combustivel = combustivel;
        this.cilindros = cilindros;
        this.cilindrada = cilindrada;
        this.transmissao = transmissao;
        this.tracao = tracao;
        this.consumoCidade = consumoCidade;
        this.consumoEstrada = consumoEstrada;
        this.co2 = co2;
        this.turbo = turbo;
        this.dataRegistro = dataRegistro;
    } 


public String format() {
            StringBuilder combStr = new StringBuilder("[");
            if (this.combustivel != null) {
                for (int i = 0; i < this.combustivel.length; i++) {
                    combStr.append(this.combustivel[i]);
                    if (i < this.combustivel.length - 1) {
                        combStr.append(",");
                    }
                }
            }
            combStr.append("]");

 
            return String.format(
                    "[%d ## %s ## %s ## %d ## %s ## %s ## %d ## %s ## %s ## %s ## %.2f ## %.2f ## %s ## %b ## %s]",
                this.id,
                this.marca,
                this.modelo,
                this.ano,
                this.categoria,
                combStr.toString(),
                this.cilindros,
                String.valueOf(this.cilindrada),
                this.transmissao,
                this.tracao,
                this.consumoCidade,
                this.consumoEstrada,
                String.valueOf(this.co2),
                this.turbo,
                this.dataRegistro != null ? this.dataRegistro.format() : ""
            );
        }
    } // fim da classe Veiculo

    public static class LeitorCsv{
    public static Veiculo[] ler(String caminhoarq) throws Exception{
        Veiculo[] veiculos = new Veiculo[500];
        File f = new File(caminhoarq);
        Scanner sc = new Scanner(f);
        int i = 0;

        sc.nextLine();
        while(sc.hasNextLine()){
            String linha = sc.nextLine();
            veiculos[i] = Veiculo.parseVeiculo(linha); 
            i++;
        }
        sc.close();
        return veiculos;
    }
}
   
static void mergeSort(Veiculo[] v){
    if(v.length <= 1) return;
    mergeSort(v,0,v.length - 1);
}

static void mergeSort(Veiculo[] v,int esq,int dir){
   if(esq<dir){
    int meio= (esq+dir) / 2;
    mergeSort(v,esq,meio);
    mergeSort(v,meio+1,dir);
    mesclar(v,esq,meio,dir);
   }
}

static void mesclar(Veiculo[] v, int esq,int meio,int dir){
Veiculo[] tmp = new Veiculo[dir - esq + 1];

int e = esq;//indice esquerda
int d = meio + 1;//indice direita
int k = 0;//indice do vetor temporario

   while (e <= meio && d <= dir) {
        if (v[e] != null && v[d] != null && (v[e].getConsumoCidade() <= v[d].getConsumoCidade())) {
            tmp[k] = v[e];
            e++;
        } else {
            tmp[k] = v[d];
            d++;
        }
        k++;
    }

    while(e <= meio){
        tmp[k] = v[e];
        e++;
        k++;
    }

        while(d <= dir){
        tmp[k] = v[d];
        d++;
        k++;
    }

     for (e = esq, k = 0; e <= dir; e++, k++) {
        v[e] = tmp[k];
    }
}

    //////////////////////////////////
public static void main(String[] args) throws Exception{

    Veiculo[] veiculos = LeitorCsv.ler("C:\\Users\\eduaf\\OneDrive\\Documentos\\MeusProjetos\\AEDS_2-PUC MG\\veiculos.csv");//trocar para "/tmp/veiculos.csv quando for mandar no verde"

    Scanner sc = new Scanner(System.in);

    Veiculo[] selecionados = new Veiculo[500];
    int n = 0;

    String linha = sc.nextLine();

    while ((linha.equals("-1"))== false) {

        int id = Integer.parseInt(linha);

        for (int i = 0; i < veiculos.length; i++) {
            if (veiculos[i] != null && veiculos[i].getId() == id) {
                selecionados[n] = veiculos[i];
                n++;
                break;
            }
        }

        linha = sc.nextLine();
    }

    mergeSort(selecionados,0,n-1);

    for (int i = 0; i < n; i++) {
        System.out.println(selecionados[i].format());
    }

    sc.close();
}
}

