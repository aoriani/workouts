#ifndef BST_H__
#define BST_H__

#include <iostream>
#include <cassert>
#include <algorithm>
#include <queue>
#include <stack>

using std::cout;
using std::endl;
using std::max;
using std::queue;
using std::stack;

template <typename T>
class BST{
    
    private:
        struct Node{
            T data;
            Node *left, *right;
            
            Node(const T& elem){
                data = elem;
                left = right = NULL;
            }
        };
        typedef Node* NodePtr;
        NodePtr root;
        
        void insertRecursive(NodePtr& node, const T&  elem);
        void dtorHelper(NodePtr node);
        bool hasKeyRecursive(const NodePtr& node, const T& elem) const;
        void printRecursive(const NodePtr& node, int spaces) const;
        int height(const NodePtr& node) const;
        bool remove(const T& elem, void (BST<T>::*delStrategy)(NodePtr&));
        void delStrategyMerge(NodePtr& ptrToFix);
        void delStrategyCopy(NodePtr& ptrToFix);
        
    public:
        BST();
        ~BST();
        void insert(const T& elem);
        void insertRecursive(const T& elem);
        bool hasKey(const T& elem) const;
        bool hasKeyRecursive(const T& elem) const;
        bool removeMerge(const T& elem);
        bool removeCopy(const T& elem);
        int height() const;
        void print() const;
        void breadthFirst() const;
        void iterativePreorder() const;
        void iterativeInorder() const;
        void iterativeInorderImproved() const;
        void iterativePosorder() const;
        void iterativePosorderImproved() const;
        T lowestCommonAncestor(const T& a, const T& b) const;
};


template <typename T>
BST<T>::BST(){ //O(1)
    root = NULL;
}

template <typename T>
void BST<T>::dtorHelper(NodePtr node){ //O(n) because visit all node once
    assert(node);
    if(node->left) dtorHelper(node->left);
    if(node->right) dtorHelper(node->right);
    delete node;    
}

template <typename T>
BST<T>::~BST(){ //O(n) because dtorHelper is
    if(root) dtorHelper(root);
    root = NULL;
}

template <typename T>
void BST<T>::insert(const T& elem){ //O(lgn) as we visit one node at each level - O(n) when tree is a list
    NodePtr newnode = new Node(elem);
    assert(newnode);

    if(!root){
        //empty tree
        root = newnode;
    }else{
        //find insertion point
        NodePtr currNode = root, prevNode;        
        while(currNode){
            prevNode = currNode;
            if(elem <= currNode->data){
                currNode = currNode->left;
            }else{
                currNode = currNode->right;
            }
        }
        if(elem <= prevNode->data){
            prevNode->left = newnode;
        }else{
            prevNode->right = newnode;
        }
    }
}


template <typename T>
void BST<T>::insertRecursive(NodePtr& nodeptr, const T& elem){//O(lgn) as we visit one node at each level - O(n) when tree is a list
    if(nodeptr == NULL){
        assert(nodeptr = new Node(elem));
    }else if(elem <= nodeptr->data){
        insertRecursive(nodeptr->left,elem);
    }else{
        insertRecursive(nodeptr->right,elem);
    }
}

template <typename T>
inline void BST<T>::insertRecursive(const T& elem){
    insertRecursive(root,elem);
}

template <typename T>
bool BST<T>::hasKey(const T& elem) const {//O(lgn) as we visit one node at each level - O(n) when tree is a list
    NodePtr curr = root;
    while(curr){
        if(elem == curr->data){
            return true;
        }else if(elem < curr->data){
            curr = curr->left;
        }else{
            curr = curr->rigth;
        }
    }
    return false;
}

template <typename T>
bool BST<T>::hasKeyRecursive(const NodePtr& nodeptr, const T& elem) const{//O(lgn) as we visit one node at each level
    if(nodeptr == NULL){
        return false;
    }else if(elem == nodeptr->data){
        return true;
    }else if(elem  < nodeptr->data){
        return hasKeyRecursive(nodeptr->left, elem);
    }else{
        return hasKeyRecursive(nodeptr->right, elem);
    }
}

template <typename T>
inline bool BST<T>::hasKeyRecursive(const T& elem) const{
    return hasKeyRecursive(root,elem);
}

template <typename T>
void BST<T>::printRecursive(const NodePtr& node, int spaces)const { //O(n) 'cause it visits each node once
    assert(node);
    assert(spaces>=0);
    if(node->right) printRecursive(node->right, spaces+5);
    for(int i=0;i<spaces;i++) cout<<" "; cout<<node->data<<endl;
    if(node->left) printRecursive(node->left, spaces+5);
}


template <typename T>
inline void BST<T>::print() const{
    if(root) printRecursive(root,0);
}

template <typename T>
int BST<T>::height(const NodePtr& node) const{//O(n) 'cause it visits each subtree once
    if(node == NULL) return 0;
    else return 1+max(height(node->left),height(node->right));
}

template <typename T>
inline int BST<T>::height() const{
    return height(root);
}


/*
 * Searching the element to remove is O(lgn) for a balanced tree as we move 
 * between level. The actual remove is O(1) for leaves and node with one child
 * and O(lgn) for node with two child because we have to search for the rightmost
 * node on left subtree
 */
template <typename T>
bool BST<T>::remove(const T& elem, void (BST<T>::*delStrategy)(NodePtr&)){
    if(root == NULL) return false; // cannot remove from empty tree
    
    //find element to removed
    NodePtr curr = root, prev;
    while((curr != NULL) && (curr->data != elem)){
        prev = curr;
        if(elem <= curr->data) curr = curr->left;
        else curr = curr->right;
    }
    
    if(curr == NULL) return false; //elem not found;
    else if(curr == root) (this->*delStrategy)(root); //Special case to fix root pointer
    else if(curr == prev->left) (this->*delStrategy)(prev->left);
    else (this->*delStrategy)(prev->right);
    
    return true;
}

template <typename T>
void BST<T>::delStrategyMerge(NodePtr& ptrToFix){
    NodePtr toDelete = ptrToFix;
    
    //Leaf node or node only with right subtree
    /*
            Parent             Parent
              |                  |
             Node   =>          Nil
             /  \
           Nil  Nil         


            Parent             Parent
              |                  |
             Node   =>           |
             /  \                \
           Nil  Right            Right

     
     */
        
    if(ptrToFix->left == NULL) ptrToFix = ptrToFix->right;
    //node only with right subtree, similar procedure 
    else if(ptrToFix->right == NULL) ptrToFix = ptrToFix->left;
    else{ //Node with both children
        /*
            In the merge strategy parent's pointer  to node to be deleted
            will be set to the left subtree. The right subtree is connected 
            to the rightmost node of the left subtree. That node is greater than
            any other node on left subtree but smaller than any node on right subtree
            . Thus BST properties are conserved 
        
        
            Parent                    Parent
               |                         |
              Node      =>              /\
             /   \                     /_\
           /\    /\                       \
          /_\   /_\                      RigthMost
             \                                  \
           RightMost                            /\
                                               /_\
        */
        
        //Search for the rightmost
        NodePtr rightmost = ptrToFix->left;
        while(rightmost->right != NULL) rightmost = rightmost->right;
        //Fix pointers
        rightmost->right = ptrToFix->right;
        ptrToFix = ptrToFix->left;
    }   
    delete toDelete;
}

template <typename T>
void BST<T>::delStrategyCopy(NodePtr& ptrToFix){
    //Needs refactory here but reference to pointer is handy to fix parent's 
    //pointer to deleted node
    NodePtr toDelete = ptrToFix;
    if(ptrToFix->left == NULL) ptrToFix = ptrToFix->right;
    else if(ptrToFix->right == NULL) ptrToFix = ptrToFix->left;
    else{ //Node with both children
        /*
            Copy strategy copies data from rightmost node on left subtree of the 
            node to be deleted to it and then deletes the rightmost node. Since 
            the rightmost has only one child at maximum, deleting it easy. As we 
            saw on previous aproach, the use of rightmost does not violate the 
            properties of BSTs. Advantage is that tree keeps the height on most
            cases. A con is that if you use pointers to node, then this strategy
            will break your code. 
            
            Parent                    Parent
               |                         |
              Node(value=a)      =>     Node(value=b)
             /   \                     /      \
           /\    /\                   /\      /\
          /_\   /_\                  /_\     /_\
             \                                  
           RightMost(value=b)                   
                                                      
        */
    
        //Find rightmost and keep track of its parent to delete it
        NodePtr rightmost = ptrToFix, rightmostParent;
        while(rightmost->right != NULL){
            rightmostParent = rightmost;
            rightmost = rightmost->right;
        }
        //copy data from rightmost to the node that should be deleted
        ptrToFix->data = rightmost->data;
        //mark to rightmost to be the actual node to be deleted
        toDelete = rightmost;
        //fix pointers
        if(rightmost == ptrToFix->left){
            //rightmost node is the root of its left subtree
            /*
                      Node                  Node
                     /    \                /    \
                Rightmost /\ =>           /\    /\
                 /    \                  /_\  
                /\   Nill
               /_\ 
            */
           ptrToFix->left = ptrToFix->left->left;
        }else{
            //rightmost's parent  right  pointer points to the rightmost
            //Now it should inherit rightmost's left subtree
            rightmostParent->right = rightmost->left;
        }
    
    }
    delete toDelete;
}

template <typename T>
inline bool BST<T>::removeMerge(const T& elem){
    return remove(elem, &BST<T>::delStrategyMerge);
}

template <typename T>
inline bool BST<T>::removeCopy(const T& elem){
    return remove(elem, &BST<T>::delStrategyCopy);
}

template <typename T>
void BST<T>::breadthFirst() const{
    if(root){
        queue<NodePtr> aux;
        aux.push(root);
        while(!aux.empty()){
            NodePtr current = aux.front(); aux.pop();
            cout<<current->data<<" ";
            if(current->left) aux.push(current->left);
            if(current->right) aux.push(current->right);
        }
    }
    cout<<endl;
}

template <typename T>
void BST<T>::iterativePreorder() const{
    if(root){
        stack<NodePtr> aux;
        aux.push(root);
        while(!aux.empty()){
            NodePtr cur = aux.top(); aux.pop();
            cout<<cur->data<<" ";
            if(cur->right) aux.push(cur->right);
            if(cur->left) aux.push(cur->left);
        }
    }
    cout<<endl;
}

template <typename T>
void BST<T>::iterativeInorder() const{
    if(root){
        stack<NodePtr> aux;
        aux.push(root);
        NodePtr cur = root->left;
        
        while(!aux.empty()){
            while(cur){
                aux.push(cur);
                cur = cur->left;
            }
            do{
                cur=aux.top();aux.pop();
                cout<<cur->data<<" ";
            }while(!aux.empty() && (cur->right==NULL));
            if(cur->right != NULL){
                aux.push(cur->right);
                cur = cur->right->left;       
            }
        }
    }
    cout<<endl;
}

template <typename T>
void BST<T>::iterativeInorderImproved() const{
    //from http://leetcode.com/2010/04/binary-search-tree-in-order-traversal.html
    //similar to mine but combine loops to result on smaller code
    stack<NodePtr> stack;
    NodePtr current = root;
    while(!stack.empty() || current){
        if(current){
            stack.push(current);
            current = current->left;
        }else{
            current = stack.top(); stack.pop();
            cout<<current->data<<" ";
            current = current->right;
        }  
    }
    cout<<endl;
}

template <typename T>
void BST<T>::iterativePosorder() const{//O(n) each node is visited at most thrice
    if(root){
        stack<NodePtr> aux;
        aux.push(root);
        NodePtr cur = root->left;
        
        while(!aux.empty()){
            while(cur){
                aux.push(cur);
                cur = cur->left;
            }
            while(!aux.empty() && (aux.top()->right == NULL || aux.top()->right==cur)){
                cur = aux.top(); aux.pop();
                cout<<cur->data<<" ";
            }
            if(!aux.empty() && aux.top()->right != NULL){
                cur = aux.top()->right;
                aux.push(cur);
                cur = cur->left;
            }
        }
    }
    cout<<endl;
}

template <typename T>
void BST<T>::iterativePosorderImproved() const{//O(n) each node is visited at most thrice
    if(root){
            stack<NodePtr> stack;
            NodePtr cur = root;
            NodePtr lastPoped = NULL;
            
            do{
                if(cur){
                    //Try walking on left subtree as much as possible
                    stack.push(cur);
                    cur = cur->left;
                }else{
                    // if you cannot go futher on left use the stack to backtrack
                    //  to go to left subtree. As this is posorder traversal we can
                    //only visit the root if we are returning from its right subtree
                    NodePtr top = stack.top();
                    if( (top->right==NULL) || (top->right == lastPoped)){
                        stack.pop();
                        lastPoped = top;
                        cout<<top->data<<" ";
                    }else cur = top->right;
                }                
            }while(!stack.empty());
    }
    cout<<endl;    
}

template <typename T>
T BST<T>::lowestCommonAncestor(const T& a, const T& b) const{
    assert(hasKey(a));
    assert(hasKey(b));
    
    NodePtr aux = root; 
    //As we asserted that both values are in the tree, it ensured we have a 
    // lowest common ancestor. In the worst case is the root.
    while(true){
        T auxValue = aux->data;
        if(a>auxValue && b>auxValue){
            aux = aux->right;
        }else if(a<auxValue && b<auxValue){
            aux = aux->left;
        }else{
            return auxValue;
        }       
    }
}

#endif // BST_H__
