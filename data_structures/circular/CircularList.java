public class CircularList<T extends Comparable> {
    private static class Node<T extends Comparable>{
        Node next;
        T data;
    }

    private Node<T> head = null;
    
    @Override
    public String toString(){
        if(head!=null){
            Node<T> aux = head;
            StringBuilder builder = new StringBuilder();
            do{
                builder.append(aux.data.toString() + " ");
                aux = aux.next;
            }while(aux != head);
            return builder.toString();
        }else{
            return "Empty";
        }
    }    
    
    public void insert(T data){
        if (data == null){
            throw new IllegalArgumentException("Cannot insert NULL");
        }
        Node<T> newNode = new Node<T>();
        newNode.data = data;
        
        if( head == null){
            head = newNode;
            newNode.next = head;
        }else if(data.compareTo(head.data)< 0){//new head
            //who points to head
            Node<T> tail = head;
            while(tail.next != head){
                tail = tail.next;
            }
            newNode.next = head;
            tail.next = newNode;
            head = newNode;
        }else{ // insert in the middle
            Node<T> aux = head;
            //find insertion point
            while((aux.next != head) && (aux.next.data.compareTo(data)<= 0)){
                aux = aux.next;
            }
            newNode.next = aux.next;
            aux.next = newNode; 
        }
    }
    
    public boolean remove (T data){
        if (data == null){
            throw new IllegalArgumentException("Dunno how to remove NULL");
        }
        
        if(head == null){ //Empty list
            return false;
        }else if(data.equals(head.data)){ // removing head
            if(head.next == head) {// single elements on list
                head = null;
            }else{
                //who points to head?
                Node<T> tail = head;
                while(tail.next != head) {
                    tail = tail.next;
                }
                tail.next = head.next;
                head = head.next;
            } 
            return true;  
        }else{ //remove node in the middle
            Node<T> aux = head;
            while((aux.next != head) && (aux.next.data.compareTo(data)<0)){
                aux = aux.next;
            }
            
            if(aux.next.data.equals(data)){//found?
                aux.next = aux.next.next;
                return true;
            }else{
                return false;
            }
        }
    }
    
    public static void main (String... args){
        CircularList<Integer> list = new CircularList<Integer>();

        //I should have JUnit, but I am lazy
        list.insert(1);
        list.insert(3);
        list.insert(2);
        System.out.println(list.remove(3));

        list.insert(4);
        
        try{
            list.insert(null);
        }catch(IllegalArgumentException e){
            System.out.println("Exception! Yeah");
        }
        
        System.out.println(list);
    
    }
}