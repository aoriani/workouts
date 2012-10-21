
public class TreeP{

    static class Node{
        public char value;
        public Node parent,left,right;
        public boolean visited; 
    
        public Node(char v){
            value = v;
            parent = left = right = null;
            visited = false; 
        }
    } 
    
    
    private static Node createTree(){
        Node a = new Node('a');
        Node b = new Node('b');
        Node c = new Node('c');
        Node d = new Node('d');
        Node e = new Node('e');
        Node f = new Node('f');        
        Node g = new Node('g');        
        Node h = new Node('h');
        Node i = new Node('i');
        //Links
        a.left=b; a.right=c;
        b.left=d;b.right=e;b.parent=a;
        c.right=f;c.parent=a;
        d.left=g;d.parent=b;
        e.right=h;e.parent=b;
        f.parent=c;
        g.parent=d;
        h.left=i; h.parent=e;
        i.parent=h;  
        
        return a;         
    }
    
    private static void recurPreorder(Node root){
        System.out.print(""+root.value+" ");
        if(root.left!=null)recurPreorder(root.left);
        if(root.right!=null)recurPreorder(root.right);
    }
    
    private static void visit(Node node){
        System.out.print(""+node.value+" ");
        node.visited = true;
    }
    
    private static void iterPreorder(Node root){
    
        while(root != null){    
             visit(root);
             while(root.left != null){
                root = root.left;
                visit(root);
             }
             
             if(root.right!=null){
                root = root.right;
                visit(root);
                 while(root.left != null){
                    root = root.left;
                    visit(root);
                 }
             }
 
             while(root != null && (root.right == null || root.right.visited==true)){
                 root = root.parent;
             }
             if(root != null && root.right != null){
                root = root.right;
             }
        }
    }


    private static void recurInorder(Node root){
        if(root.left!= null) recurInorder(root.left);
        visit(root);
        if(root.right!= null) recurInorder(root.right);
    }


    private static void iterInorder(Node root){
    
        while(root!= null){
            //Go left futher as possible
            while(root.left!= null){
                root = root.left;
            }
            visit(root);
            
            if((root.right!=null) &&(root.right.visited ==false)){
                root = root.right;
                while(root.left!= null){
                  root = root.left;
                }
                visit(root);
            }
            
            while(root != null ){
                root = root.parent;
                if(root != null){
                    if(!root.visited){
                       visit(root);
                    }
                    if((root.right != null) && !root.right.visited){
                        root = root.right;
                        break;
                    }
                }
            }
       }
    }


    private static void recurPostorder(Node root){
        if(root.left!=null)recurPostorder(root.left);
        if(root.right!=null)recurPostorder(root.right);
        visit(root);
    }
    
    private static void iterPostOrder(Node root){
    
        while(root!=null){
        
            while(root.left != null){
                root = root.left;
            }
            
            if(root.right == null){
                visit(root);
            }else if( !root.right.visited){
                root = root.right;
                while(root.left != null){
                    root = root.left;
                }   
                visit(root);
            }
            
            while(root != null){
                root = root.parent;
                
                if(root != null){
                    if((root.right!=null) && !root.right.visited){
                        root = root.right;
                        break;                
                    }else{
                        visit(root);
                    }              
                }            
            
            }
        }
    }



    public static void main (String args[]){
        System.out.println("Recursive preorder:");
        recurPreorder(createTree());
        System.out.println();

        System.out.println("Iterative preorder:");
        recurPreorder(createTree());
        System.out.println();
        
        System.out.println("Recursive inorder:");
        recurInorder(createTree());
        System.out.println();

        System.out.println("Iterative inorder:");
        iterInorder(createTree());
        System.out.println();

        System.out.println("Recursive  postorder:");
        recurPostorder(createTree());
        System.out.println();

        System.out.println("Recursive  postorder:");
        iterPostOrder(createTree());
        System.out.println();

        System.out.println();
    }



}
