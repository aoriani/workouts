
def insertion_sort(array):
	size = len(array) ;
	#only sort if not trivially sorted (len ==1 )
	if size > 1:
		for i in range(1,size):
			elem = array[i]
			j = i - 1
			while j>=0 and array[j]>elem:
				array[j+1] = array[j]
				array[j] = elem
				j = j - 1


def selection_sort(array):
	size = len(array)
	if size > 1:
		for i in range(0,size-1):
			minIndex = i
			for j in range(i+1,size):
				if array[j] < array[minIndex]:
					minIndex = j
			if minIndex != i : # do the swap
				temp = array[i]
				array[i] = array[minIndex]
				array[minIndex] = temp

if __name__ == "__main__":
	array = [ 6,5,4,3,2,1]
	selection_sort(array)
	for e in array : print(e)

