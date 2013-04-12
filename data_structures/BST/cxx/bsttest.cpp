#include "bst.h"
#include <iostream>


int main(){
    
    BST<int> tree;
    tree.insert(2);
    tree.insertRecursive(3);
    tree.insert(1); 
    tree.insertRecursive(4);    
    tree.print();
    tree.breadthFirst();
    tree.iterativeInorder();
    tree.iterativePosorder();
    tree.iterativePosorderImproved();
    
    tree.removeMerge(3);
    tree.removeCopy(2);
    
    std::cout<<"The tree height is : "<<tree.height()<<std::endl;  
    
    tree.print(); 
    return 0;
}
