package oriani;

import java.util.*;

//See http://stackoverflow.com/q/4830400/1525801 
// for the generics especifiers


/**
 * This class implements a Binary Search Tree
 * @author André Oriani
 */
public class Tree<T extends Comparable<T>> { 


    static class Node<T extends Comparable<T>>{
        T value;
        Node<T> left,right;
        
        Node(T value){
            this.value = value;
            this.left = this.right = null;
        }
    }
    
    public interface Visitor<T>{
        public void visit(T value);
    }
    
    /// The root for the tree 
    private Node<T> root = null;
    
    public Tree(){}
    
    
    /**
     * Insert a value iteratively
     * @param value  data to be inserted on the tree
     * @returns the tree to allow chaining
     */ 
    public Tree<T> insertI(T value){
        
        Node<T> newNode = new Node<T>(value);
        
        if(root == null){ //Empty tree
            root = newNode;
        }else{ //Find insertion point
            Node<T> aux = root;
            while(true){
                if (value.compareTo(aux.value) > 0){
                    if(aux.right == null){
                        aux.right = newNode;
                        break; //We found the insertion point
                    }else{
                        aux = aux.right;
                    }
                }else{
                    if(aux.left == null){
                        aux.left = newNode;
                        break; //We found the insertion point
                    }else{
                        aux = aux.left;
                    }
                }
            }
        }
        return this;
    }
    
    
    /**
     *  Recursive preorder traversal
     *  @param visitor The object that will be called for each node visited
     */
     public void preorderR(Visitor<T> visitor){
        preorderR(root,visitor);
     }
    
     private void preorderR(Node<T> node, Visitor<T> visitor){
        if(node != null){
            visitor.visit(node.value);
            preorderR(node.left,visitor);
            preorderR(node.right,visitor);
        }
     }


    /**
     *  Recursive inoder traversal
     *  @param visitor The object that will be called for each node visited
     */
     public void inorderR(Visitor<T> visitor){
        inorderR(root,visitor);
     }
    
     private void inorderR(Node<T> node, Visitor<T> visitor){
        if(node != null){
            inorderR(node.left,visitor);
            visitor.visit(node.value);
            inorderR(node.right,visitor);
        }
     }

    /**
     *  Recursive posorder traversal
     *  @param visitor The object that will be called for each node visited
     */
     public void posorderR(Visitor<T> visitor){
        posorderR(root,visitor);
     }
    
     private void posorderR(Node<T> node, Visitor<T> visitor){
        if(node != null){
            posorderR(node.left,visitor);
            posorderR(node.right,visitor);
            visitor.visit(node.value);
        }
     }

    /**
     *  Iterative preorder traversal
     *  @param visitor The object that will be called for each node visited
     */
     public void preorderI(Visitor<T> visitor){
        if(root != null){
            Stack<Node<T>> stack = new Stack<Node<T>>();
            stack.push(root);
            while(!stack.isEmpty()){
                Node<T> currNode = stack.pop();
                if(currNode.right != null) {
                    stack.push(currNode.right);
                }
                if(currNode.left != null) {
                    stack.push(currNode.left);
                }
                visitor.visit(currNode.value);
            }
        }
     }
     
     
    /**
     *  Breadth first traversal
     *  @param visitor The object that will be called for each node visited
     */  
     public void breadthFirst(Visitor<T> visitor){
        if(root != null){
            Queue<Node<T>> queue = new LinkedList<Node<T>>();
            queue.offer(root);
            while(!queue.isEmpty){
                Node<T> currNode = queue.poll();
                if(currNode.left != null){
                    queue.offer(currNode.left);
                } 
                if(currNode.right != null){
                    queue.offer(currNode.right);
                }
                visitor.visit(currNode.value);
            }
        }
     }   
     

    /**
     * Recursive height of the tree
     */
    public int heightR(){
        return heightR(root);
    }
    
    private int heightR(Node<T> currNode){
        if(currNode != null){        
            return 1 + Math.max(heightR(currNode.left),
                 heightR(currNode.right));
        }else return 0;
    }
    
    
}