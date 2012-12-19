import java.util.Arrays;

public class MergeSort<T extends Comparable>{
	private T[] aux;
	private T[] sorted;

	public MergeSort(T[] toBeSorted){
	    assert toBeSorted.length>0;
		sorted = toBeSorted;
		aux = (T[]) new Comparable[sorted.length];
	}

	private void merge (int lo, int mid, int hi){
		for(int k=lo; k<=hi; k++){
			aux[k]=sorted[k];	
		}
		int a1 = lo;
		int a2 = mid+1;
		for (int k=lo; k<=hi; k++){
			if(a1>mid){//1st part run out
				sorted[k]=aux[a2++];
			}else if(a2>hi){//2nd part run out
				sorted[k]=aux[a1++];
			}else if(aux[a1].compareTo(aux[a2])<0){
				sorted[k]=aux[a1++];
			}else{
				sorted[k]=aux[a2++];
			}
		}
	
	}
	
	private void mergeSort(int lo, int hi){
		if(lo<hi){
			int mid = (hi+lo)/2; //Integer division (floor)
			mergeSort(lo,mid);
			mergeSort(mid+1,hi);
			if(sorted[mid].compareTo(sorted[mid+1])>0){//if not sorted
				merge(lo,mid,hi);
			}
		}
	}

	public void sort(){
		mergeSort(0, sorted.length-1);	
	}	

	public static void main (String args[]){
		Integer toBeSorted[] ={1,5,3,2,4};
		MergeSort<Integer> sorted = new MergeSort<Integer>(toBeSorted);
                sorted.sort();
		System.out.println(Arrays.toString(toBeSorted));
		
		Integer toBeSorted1[] ={1,2,3,4,5};
		sorted = new MergeSort<Integer>(toBeSorted1);
        sorted.sort();
		System.out.println(Arrays.toString(toBeSorted1));
		
		Integer toBeSorted2[] ={5,4,3,2,1};
		sorted = new MergeSort<Integer>(toBeSorted2);
        sorted.sort();
		System.out.println(Arrays.toString(toBeSorted2));
		
		Integer toBeSorted3[] ={5};
		sorted = new MergeSort<Integer>(toBeSorted3);
        sorted.sort();
		System.out.println(Arrays.toString(toBeSorted3));
		
	}

}


