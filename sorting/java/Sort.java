import java.util.Arrays;

public class Sort {


    private static <T extends Comparable> void insertionSort(T array[]){
    
        for (int i=1 ; i<array.length;i++){
            T elem = array[i];
            int j = i-1;
            while( (j>=0) && (array[j].compareTo(elem)>0)){
                array[j+1] = array[j]; 
                j--;           
            }
            array[j+1] =elem;
        }
    }

    private static <T extends Comparable> void selectionSort(T array[]){
    
        for(int i = 0; i <(array.length-1); i++){
            int smallerIndex=i; 
            for(int j = i+1; j <array.length; j++){
                if(array[j].compareTo(array[smallerIndex])<0){
                    smallerIndex = j;
                }
            }       
            
            if( smallerIndex != i){
                T aux = array[i];
                array[i] = array[smallerIndex];
                array[smallerIndex] = aux;
            }
        }
    }


    public static void main(String args[]){
        Integer array[] = {6,5,4,3,2,1,0};
        selectionSort(array);
        System.out.println(Arrays.toString(array));
    }

}
