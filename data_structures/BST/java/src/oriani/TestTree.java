package oriani;

import org.junit.*;
import static org.junit.Assert.*;
import java.util.*;

public class TestTree{

    //This tree try to test every subtree variation 
    //THIS IS NOT A GOOD PRACTICE, WRITE A TEST FOR EACH VARIATION
    // I am doing that to speed up.
    static final Integer testElements[] ={50,25,75,12,35,60,80,5,100,8,90,7,91};
    static final Integer preOrderElements[]=                             {50,25,12,5,8,7,35,75,60,80,100,90,91};
    static final Integer inOrderElements[] = {5,7,8,12,25,35,50,60,75,80,90,91,100};
    static final Integer posOrderElements[] = {7,8,5,12,35,25,60,91,90,100,80,75,50};


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
        for (int e : testElements){
            tree.insertI(e);
        }
            
        List<Integer> expected = Arrays.asList(preOrderElements);
        MyVisitor<Integer> v = new MyVisitor<Integer>();
        tree.preorderR(v);
        assertEquals(expected,v.actual);    
    }
    
    ///Test recursive inorder traversal
    @Test public void testRecursiveInorderTraversal(){
        Tree<Integer> tree = new Tree<Integer>();
        for (int e : testElements){
            tree.insertI(e);
        }

        List<Integer> expected = Arrays.asList(inOrderElements);
        MyVisitor<Integer> v = new MyVisitor<Integer>();
        tree.inorderR(v);
        assertEquals(expected,v.actual);    
    }


    ///Test recursive inorder traversal
    @Test public void testRecursivePosorderTraversal(){
        Tree<Integer> tree = new Tree<Integer>();
        for (int e : testElements){
            tree.insertI(e);
        }
            
        List<Integer> expected = Arrays.asList(posOrderElements);
        MyVisitor<Integer> v = new MyVisitor<Integer>();
        tree.posorderR(v);
        assertEquals(expected,v.actual);    
    }
    
    ///Test interative preoder
    @Test public void testIterativePreorder(){
        Tree<Integer> tree = new Tree<Integer>();
        for (int e : testElements){
            tree.insertI(e);
        }

        List<Integer> expected = Arrays.asList(preOrderElements);
        MyVisitor<Integer> v = new MyVisitor<Integer>();
        tree.preorderI(v);
        assertEquals(expected,v.actual);
        
    
    }


}

