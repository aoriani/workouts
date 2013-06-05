import java.util.Arrays;

public class MergeSort{

    private int aux[];
    private int array[];
    
    public MergeSort(int a[]){
        array = a;
        aux = new int[a.length];
    }
    
    private void merge(int lo, int mid, int hi){
        //Copy to aux array 
        for(int e = lo; e <= hi; e++) {
            aux[e]= array[e];
        }
        
        //Merge
        int i = lo;
        int j = mid + 1;
        int k = lo;
        while(k <= hi){
            if( (i<= mid) && (j<= hi)){
                if(aux[i] < aux[j]){
                    array[k++] = aux[i++];
                }else{
                    array[k++] = aux[j++];
                }
            } else if ( i <= mid){
                array[k++] = aux [i++];
            } else {
                array[k++] = aux[j++];
            }
        }
    }
    
    private void sort(int lo, int hi){
        if(lo >= hi) return;
        int mid = (hi+ lo)/2;
        sort(lo,mid);
        sort(mid+1,hi);
        merge(lo,mid,hi);
    }
    
    public void sort(){
        sort(0,array.length - 1 );
    }   
    
    public static void main(String... args){
    
        int a[] = {18,47,4,23,5,0,15,3,2,48,1,99};
        MergeSort ms = new MergeSort(a);
        ms.sort();
        System.out.println(Arrays.toString(a));
    }
    
}