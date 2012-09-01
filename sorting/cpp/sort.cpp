#include <iostream>
#include<cstring>

using std::cout;
using std::endl;
using std::size_t;


template <typename T>
void insertion_sort(T array[], size_t size){

	for(int i=1; i < size; i++){
		T elem = array[i];
		int j = i - 1;
		while((j >= 0) && array[j]> elem){
			array[j+1] = array[j];
			array[j] = elem;
			j--;
		}
	}
}

template<typename T>
void selection_sort(T array[],size_t size){

	for (int i = 0 ; i < size-1; i++) {
		int minIndex = i;
		for (int j = i+1; j < size; j++) {
			if (array[j]< array[minIndex]) {
				minIndex = j;
			}	
		}
		if(minIndex != i){
			T temp = array[i];
			array[i] = array[minIndex];
			array[minIndex] = temp;
		}
	}
}


int main(){
	int array[] = {6,5,4,3,2,1};
	size_t size= sizeof(array)/sizeof(int);
	selection_sort(array,size);
	
	for(int i=0; i<size;i++){
		cout << array[i]<<endl;
	}
}