package tp02;

import java.util.Arrays;

public class insercao {

    public static int[] inserc(int[] vet){

        int[] vet2 = new int[vet.length];//vet ordenado

        for (int i=1; i<vet.length ; i++){
            if(vet[i]>=vet2[i-1]){// ja esta em ordem, vai p ultima posicao
                vet2[i]=vet[i];
            }
            else{
            for(int j=1;j<vet2.length-1;j++){// j=1(ultimo termo do vet2) 
               if(vet[i]>vet2[i-j]){
                int tmp = vet2[i-j];
                vet2[i-j]=vet[i];
                vet[i-j-1] = tmp;
            } 
        }
            }
        }
        return vet2;
    }

    public static void main(String[] args){
        int[] vet = {12,11,13,5,6};
        System.out.println(Arrays.toString(inserc(vet)));
    }
    
}
