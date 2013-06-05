import java.util.Arrays;

public class QuickSort{

    private int[] array;
    
    public QuickSort(int[] a){
        array = a;
    }
    
    private int partition(int lo, int hi){
        //We assume array if random, if it sorted this alg will be n^2
        // Normally the pivot is the middle element and then we swap with
        // the array[low], but I am not gonna do that to symplify the alg
        int pivot =  array[lo];
        int i = lo;
        int j = hi+1;
        
        while(true){
            while(array[++i] < pivot){
                if(i == hi) break;
            }
            
            while(array[--j] > pivot){
                if(j == lo) break;
            }
            
            if( i>= j) break;
            
            //Swap 
            int temp = array[i]; array[i]=array[j]; array[j]=temp;
        }
        
        //Put pivot in the correct place
        int temp = array[j]; array[j]=array[lo]; array[lo]=temp;
        return j;
    }

    private void sort(int lo, int hi){
        if(lo >= hi) return;
        int j = partition(lo,hi);
        sort(lo,j-1);
        sort(j+1,hi);
    }
    
    public void sort(){
        sort(0, array.length-1);
    }

    public static void main(String... args){
        int a[] = {18,47,4,23,5,0,0,15,3,2,48,4,1,99,4};
        QuickSort qs = new QuickSort(a);
        qs.sort();
        System.out.println(Arrays.toString(a));
    }
}