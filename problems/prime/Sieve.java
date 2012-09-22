import java.util.Arrays;

public class Sieve{

    private static final int SIZE = 250;

    private  static boolean[] dumbestSieve(){
        boolean table[] = new boolean[SIZE+1];
        for(int e=0; e<table.length;e++) table[e]=true;

        for (int i =2; i<=SIZE; i++){
            if (table[i]){
                for(int j = 2*i; j<=SIZE; j += i){
                    table[j] = false;
                }            
            
            }
        }
        return table;
    }


    private static boolean[] lessDumbSieve(){
        boolean table[] = new boolean[SIZE+1];
        int upperBound  = (int)Math.sqrt(SIZE);
        for(int e=0; e<table.length;e++) table[e]=true;
        
        for(int i=2; i<=upperBound;i++){
            if(table[i]){
                for(int j = i*i; j<=SIZE; j+=i){
                    table[j] = false;
                } 
            }
        }
        return table;
    } 


    private static void printResult(boolean table[]){
        for(int i =2; i<=SIZE; i++){
            if(table[i]) System.out.print(""+i+" ");
        }
        System.out.println();
    }


    public static void main(String args[]){
        System.out.println("Dumbest sieve:");
        printResult(dumbestSieve());
        
        System.out.println("Less dumb sieve:");
        printResult(lessDumbSieve());
    
    }

}
