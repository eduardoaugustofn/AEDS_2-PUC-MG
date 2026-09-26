package tp02;
import java.io.File;
import java.util.Scanner;

public class listadupla {

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

        public static Veiculo parseVeiculo(String s) {
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
    }

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

    public static class Celula {
        Veiculo veiculo;
        Celula prox;
        Celula prev;

        public Celula(Veiculo veiculo) {
            this.veiculo = veiculo;
            this.prox = null;
            this.prev = null;
        }
    }

    public static class ListaDupla {
        private Celula inicio;
        private int n;

        public ListaDupla() {
            this.inicio = null;
            this.n = 0;
        }

        public void inserirInicio(Veiculo veiculo) {
            Celula novo = new Celula(veiculo);
            novo.prox = inicio;
            if (inicio != null) {
                inicio.prev = novo;
            }
            inicio = novo;
            n++;
        }

        public void inserir(Veiculo veiculo, int pos) {
            if (pos == 0) {
                inserirInicio(veiculo);
                return;
            }

            Celula tmp = inicio;
            for (int i = 0; i < pos - 1; i++) {
                tmp = tmp.prox;
            }

            Celula novo = new Celula(veiculo);
            novo.prox = tmp.prox;
            novo.prev = tmp;
            if (tmp.prox != null) {
                tmp.prox.prev = novo;
            }
            tmp.prox = novo;
            n++;
        }

        public void inserirFim(Veiculo veiculo) {
            Celula novo = new Celula(veiculo);
            if (inicio == null) {
                inicio = novo;
            } else {
                Celula tmp = inicio;
                while (tmp.prox != null) {
                    tmp = tmp.prox;
                }
                tmp.prox = novo;
                novo.prev = tmp;
            }
            n++;
        }

        public Veiculo removerInicio() {
            if (inicio == null) return null;
            Veiculo veiculo = inicio.veiculo;
            inicio = inicio.prox;
            if (inicio != null) {
                inicio.prev = null;
            }
            n--;
            return veiculo;
        }

        public Veiculo remover(int pos) {
            Celula tmp = inicio;
            for (int i = 0; i < pos; i++) {
                tmp = tmp.prox;
            }

            Veiculo veiculo = tmp.veiculo;
            if (tmp.prev != null) {
                tmp.prev.prox = tmp.prox;
            } else {
                inicio = tmp.prox;
            }
            if (tmp.prox != null) {
                tmp.prox.prev = tmp.prev;
            }
            n--;
            return veiculo;
        }

        public Veiculo removerFim() {
            Celula tmp = inicio;
            while (tmp.prox != null) {
                tmp = tmp.prox;
            }

            Veiculo veiculo = tmp.veiculo;
            if (tmp.prev != null) {
                tmp.prev.prox = null;
            } else {
                inicio = null;
            }
            n--;
            return veiculo;
        }

        public void mostrar() {
            Celula tmp = inicio;
            int i = 0;

            while (tmp != null && i < n) {
                System.out.println(tmp.veiculo.format());
                tmp = tmp.prox;
                i++;
            }
        }
    }

    public static Veiculo buscarPorId(Veiculo[] base, int id) {
        for (int i = 0; i < base.length; i++) {
            if (base[i] != null && base[i].getId() == id) {
                return base[i];
            }
        }
        return null;
    }

    public static void main(String[] args) throws Exception {
        Veiculo[] baseDados = LeitorCsv.ler("/tmp/veiculos.csv");
        ListaDupla lista = new ListaDupla();
        Scanner sc = new Scanner(System.in);

        String linha = sc.nextLine();
        while (!linha.equals("-1")) {
            int id = Integer.parseInt(linha);
            Veiculo v = buscarPorId(baseDados, id);

            if (v != null) {
                lista.inserirFim(v);
            }

            linha = sc.nextLine();
        }

        if (sc.hasNextLine()) {
            int numComandos = Integer.parseInt(sc.nextLine());

            for (int i = 0; i < numComandos; i++) {
                String comando = sc.nextLine();
                String[] partes = comando.split(" ");
                String op = partes[0];

                Veiculo removido = null;

                if (op.equals("II")) {
                    int id = Integer.parseInt(partes[1]);
                    Veiculo v = buscarPorId(baseDados, id);
                    if (v != null) {
                        lista.inserirInicio(v);
                    }
                } else if (op.equals("I*")) {
                    int pos = Integer.parseInt(partes[1]);
                    int id = Integer.parseInt(partes[2]);
                    Veiculo v = buscarPorId(baseDados, id);
                    if (v != null) {
                        lista.inserir(v, pos);
                    }
                } else if (op.equals("IF")) {
                    int id = Integer.parseInt(partes[1]);
                    Veiculo v = buscarPorId(baseDados, id);
                    if (v != null) {
                        lista.inserirFim(v);
                    }
                } else if (op.equals("RI")) {
                    removido = lista.removerInicio();
                } else if (op.equals("R*")) {
                    int pos = Integer.parseInt(partes[1]);
                    removido = lista.remover(pos);
                } else if (op.equals("RF")) {
                    removido = lista.removerFim();
                }

                if (removido != null) {
                    System.out.println("(R)" + removido.getMarca() + " " + removido.getModelo());
                }
            }
        }

        lista.mostrar();
        sc.close();
    }
}