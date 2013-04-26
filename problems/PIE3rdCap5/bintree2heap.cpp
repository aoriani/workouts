
/*
 *You are given a set of integers in an unordered binary tree. 
 * Use an array sorting routine to transform the tree into a heap 
 * that uses a balanced binary tree as its underlying data structure.
 * PIE3rdEd pg 75
 */
#include <algorithm>
#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;
using std::setw;
using std::sort;


struct Node{
    Node *left, *right;
    int value;
};

/*
    
        6
       / \
      17  1
    /    /  \
   5    45  44
   /    /
   30  10 

*/

Node thirty = {0,0,30};
Node ten    = {0,0,10};
Node five   = {&thirty,0,5};
Node forty_five = {&ten,0,45};
Node forty_four = {0,0,44};
Node seventeen  = {&five,0,17};
Node one  = {&forty_five, &forty_four,1};
Node six = {&seventeen, &one, 6};


///Count the number of nodes in the tree
int count_node(Node* node){
    if(!node){
        return 0;
    }else{
        return 1 + count_node(node->left) + count_node(node->right);
    }
}

///Fill an array of pointer to nodes with the tree
int fill_array(Node* node, int count, Node* array[]){
    if(!node){
        return count;
    }else{
        array[count] = node;
        count++;
        count = fill_array(node->left,count, array);
        count = fill_array(node->right,count, array);
        return count;
    }
}
                
/// A comparator for two node so sort can work
bool myComparator(Node* a, Node* b){
    return a->value < b->value;
}

//Create a max-heap binary tree from array
void maxHeapfy(Node* array[], int count){
    for(int k=0; k < count; k++){
        int cur = (count - 1) - k;
        int left = (count - 1) - (2*k+2);
        int right = (count - 1) - (2*k+1);
        array[cur]->left = (left >= 0)? array[left] : 0;
        array[cur]->right = (right >= 0)? array[right] : 0;
    }
}

void printHeap(Node* node, int spaces){
    
    if(node->right) printHeap(node->right, spaces+5);
    cout<<setw(spaces)<<node->value<<endl;
    if(node->left) printHeap(node->left,spaces+5);

}

int main(){
    int nNodes = count_node(&six); //O(n)
    cout<<"The tree has "<<nNodes<<" nodes"<<endl;
    Node** array = new Node*[nNodes];
    fill_array(&six,0, &array[0]); //O(n)
    sort(array, array+nNodes,myComparator); //O(nlgn)
    maxHeapfy(array,nNodes); //O(n)
    printHeap(array[nNodes-1],0); //O(n)
    
    delete[] array;
    return 0;
}

