class Celula {
    public int elemento;
    public Celula prox;

    public Celula() {
        this(0);
    }

    public Celula(int elemento) {
        this.elemento = elemento;
        this.prox = null;
    }
}

class Pilha {
    private Celula topo;

    public Pilha() {
        topo = null;
    }

    public void inserir(int x) {
        Celula tmp = new Celula(x);
        tmp.prox = topo;
        topo = tmp;
        tmp = null;
    }

    public int remover() throws Exception {
        if (topo == null) {
            throw new Exception("Erro!");
        }
        int elemento = topo.elemento;
        Celula tmp = topo;
        topo = topo.prox;
        return elemento;
    }
}

class Solution {

    Pilha pilha = new Pilha();

    public boolean isValid(String s) {
        for (int i = 0; i < s.length(); i++) {
if (s.charAt(i) == '(') {
    pilha.inserir(1);
}

if (s.charAt(i) == '{') {
    pilha.inserir(2);
}

if (s.charAt(i) == '[') {
    pilha.inserir(3);
} 
if (s.charAt(i) == ')' || s.charAt(i) == '}' || s.charAt(i) == ']') {
                try {
                    int x = pilha.remover();
                    if (s.charAt(i)==')' && x != 1 && x>0){
                        return false;
                    }
                    if (s.charAt(i)=='}' && x != 2 && x>0){
                        return false;
                    }
                    if (s.charAt(i)==']' && x != 3 && x>0){
                        return false;
                    }                                        
                } catch (Exception e) {
                    return false;
                }
            }
        }//fim dos ifs
//agora tem que checar se a pilha esta vazia, se nao estiver esta errado
try{
int y = pilha.remover();}
catch (Exception e){
    return true;
}
return false;


    }


}