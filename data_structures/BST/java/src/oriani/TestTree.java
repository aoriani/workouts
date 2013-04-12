package oriani;

import org.junit.*;
import static org.junit.Assert.*;
import java.util.*;

public class TestTree{

    @Ignore
    static class MyVisitor<T> implements Tree.Visitor<T>{
        List<T> actual = new ArrayList<T>();
        
        public void visit(T value){
            actual.add(value);
        }
    }

    ///Test insertion and recursive preoder
    @Test public void testIterativeInsertAndRecursivePreorder(){
        //I know that I should a test should test only one method 
        // but tree traversal is the way to check the insertions
        Tree<Integer> tree = new Tree<Integer>();
        tree.insertI(20).insertI(15).insertI(30).insertI(14).insertI(16)
            .insertI(25).insertI(31).insertI(10).insertI(32).insertI(1)
            .insertI(33);
            
        Integer array[] = {20,15,14,10,1,16,30,25,31,32,33};
        List<Integer> expected = Arrays.asList(array);
        MyVisitor<Integer> v = new MyVisitor<Integer>();
        tree.preorderR(v);
        assertEquals(expected,v.actual);    
    }
    
    ///Test recursive inorder traversal
    @Test public void testRecursiveInorderTraversal(){
        Tree<Integer> tree = new Tree<Integer>();
        tree.insertI(20).insertI(15).insertI(30).insertI(14).insertI(16)
            .insertI(25).insertI(31).insertI(10).insertI(32).insertI(1)
            .insertI(33);
            
        Integer array[] = {1,10,14,15,16,20,25,30,31,32,33};

        List<Integer> expected = Arrays.asList(array);
        MyVisitor<Integer> v = new MyVisitor<Integer>();
        tree.inorderR(v);
        assertEquals(expected,v.actual);    
    }


    ///Test recursive inorder traversal
    @Test public void testRecursivePosorderTraversal(){
        Tree<Integer> tree = new Tree<Integer>();
        tree.insertI(20).insertI(15).insertI(30).insertI(14).insertI(16)
            .insertI(25).insertI(31).insertI(10).insertI(32).insertI(1)
            .insertI(33);
            
        Integer array[] = {1,10,14,16,15,25,33,32,31,30,20};

        List<Integer> expected = Arrays.asList(array);
        MyVisitor<Integer> v = new MyVisitor<Integer>();
        tree.posorderR(v);
        assertEquals(expected,v.actual);    
    }
    
    ///Test interative preoder
    @Test public void testIterativePreorder(){
        Tree<Integer> tree = new Tree<Integer>();
        tree.insertI(20).insertI(15).insertI(30).insertI(14).insertI(16)
            .insertI(25).insertI(31).insertI(10).insertI(32).insertI(1)
            .insertI(33);
            
        Integer array[] = {20,15,14,10,1,16,30,25,31,32,33};
        List<Integer> expected = Arrays.asList(array);
        MyVisitor<Integer> v = new MyVisitor<Integer>();
        tree.preorderI(v);
        assertEquals(expected,v.actual);
        
    
    }


}

