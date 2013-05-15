def nonincreasing_insertion_sort(list):
    for i in range(1,len(list)):
        key = list[i]
        j = i - 1
        while (j>=0) and (list[j]<key):
            list[j+1] = list[j]
            j -= 1
        list[j+1] = key


if __name__ == "__main__":
    list1 = [1,2,3,4,5,6]
    nonincreasing_insertion_sort(list1)
    print(list1)
    
    list2 = [6,5,4,3,2,1]
    nonincreasing_insertion_sort(list2)
    print(list2)
    
    list3 = [1,6,2,4,5,3]
    nonincreasing_insertion_sort(list3)
    print(list3)