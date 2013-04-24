package oriani;

import org.junit.*;
import static org.junit.Assert.*;
import java.util.*;

public class TestTree{

    //This tree try to test every subtree variation 
    //THIS IS NOT A GOOD PRACTICE, WRITE A TEST FOR EACH VARIATION
    // I am doing that to speed up.
    static final Integer testElements[] ={50,25,75,12,35,60,80,5,100,8,90,7,91};
    static final Integer preOrderElements[]= {50,25,12,5,8,7,35,75,60,80,100,90,91};
    static final Integer inOrderElements[] = {5,7,8,12,25,35,50,60,75,80,90,91,100};
    static final Integer posOrderElements[] = {7,8,5,12,35,25,60,91,90,100,80,75,50};


    @Ignore
    static class MyVisitor<T> implements Tree.Visitor<T>{
        List<T> actual = new ArrayList<T>();
        
        public void visit(T value){
            actual.add(value);
        }
    }

    /** Test insertion and recursive preoder */
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
    
    /**Test recursive inorder traversal*/
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


    /**Test recursive posorder traversal */
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
    
    /** Test interative preoder */
    @Test public void testIterativePreorder(){
        Tree<Integer> tree = new Tree<Integer>();
        for (int e : testElements){
            tree.insertR(e);
        }

        List<Integer> expected = Arrays.asList(preOrderElements);
        MyVisitor<Integer> v = new MyVisitor<Integer>();
        tree.preorderI(v);
        assertEquals(expected,v.actual);   
    }
    
    /** Test interative inorder */
    @Test public void testIterativeIneorder(){
        //I know that I should a test should test only one method 
        // but tree traversal is the way to check the insertions
        Tree<Integer> tree = new Tree<Integer>();
        for (int e : testElements){
            tree.insertI(e);
        }
            
        List<Integer> expected = Arrays.asList(inOrderElements);
        MyVisitor<Integer> v = new MyVisitor<Integer>();
        tree.inorderI(v);
        assertEquals(expected,v.actual);    
    }
    
    /** Test interative posorder */
    @Test public void testIterativePosorderTraversal(){
        Tree<Integer> tree = new Tree<Integer>();
        for (int e : testElements){
            tree.insertI(e);
        }
            
        List<Integer> expected = Arrays.asList(posOrderElements);
        MyVisitor<Integer> v = new MyVisitor<Integer>();
        tree.posorderI(v);
        assertEquals(expected,v.actual);    
    }

    /** Test breadth first traversal */
    @Test public void testBreadthFirst(){
        Tree<Integer> tree = new Tree<Integer>();
        for (int e : testElements){
            tree.insertI(e);
        }
        
        Integer[] breadthFirstElements = testElements;
        List<Integer> expected = Arrays.asList(breadthFirstElements);
        MyVisitor<Integer> v = new MyVisitor<Integer>();
        tree.breadthFirst(v);
        assertEquals(expected,v.actual);              
    }
    
    /** Test the height of an empty tree */
    @Test public void testZeroHeightTree(){
       Tree<Integer> tree = new Tree<Integer>();
       assertEquals("An empty tree must have zero height",0,tree.heightR());
    }

    /** Test the height of an single element tree */
    @Test public void testHeightOneTree(){
       Tree<Integer> tree = new Tree<Integer>();
       tree.insertR(1);
       assertEquals("An single tree must have height one ",1,tree.heightR());
    }

    /** Test the height of an tree  with equal height subtrees*/
    @Test public void testEqualHeightSubTrees(){
       Tree<Integer> tree = new Tree<Integer>();
       tree.insertR(2);
       tree.insertR(1);
       tree.insertR(3);
       assertEquals(2,tree.heightR());
    }

    /** Test the height of an tree  with not equal height subtrees*/
    @Test public void testNotEqualHeightSubTrees(){
       Tree<Integer> tree = new Tree<Integer>();
       tree.insertR(2);
       tree.insertR(1);
       assertEquals(2,tree.heightR());
    }
    
    /** Test the height of a bug tree */
    @Test public void testHeightBigTree(){
        Tree<Integer> tree = new Tree<Integer>();
        for (int e : testElements){
            tree.insertI(e);
        }
       assertEquals(6,tree.heightR());
    }

    
    /** Test if a element can be found in a empty tree - Recursive */
    @Test public void testHasREmptyTree(){
        Tree<Integer> tree = new Tree<Integer>();
        assertFalse(tree.hasR(1));
    }

    /** Test if a element can be found in a empty tree - Iterative */
    @Test public void testHasIEmptyTree(){
        Tree<Integer> tree = new Tree<Integer>();
        assertFalse(tree.hasI(1));
    }

    /** Test if non element can fond in a tree - Recursive */
    @Test public void testHasRNonElementTree(){
        Tree<Integer> tree = new Tree<Integer>();
        for (int e : testElements){
            tree.insertI(e);
        }
        assertFalse(tree.hasR(-1));
    }

    /** Test if non element can fond in a tree - Iterative */
    @Test public void testHasINonElementTree(){
        Tree<Integer> tree = new Tree<Integer>();
        for (int e : testElements){
            tree.insertI(e);
        }
        assertFalse(tree.hasI(-1));
    }
    
    /** Test if root can fond in a tree - Recursive */
    @Test public void testHasRRootTree(){
        Tree<Integer> tree = new Tree<Integer>();
        for (int e : testElements){
            tree.insertI(e);
        }
        assertTrue(tree.hasR(50));
    }

    /** Test if root element can fond in a tree - Iterative */
    @Test public void testHasIRootTree(){
        Tree<Integer> tree = new Tree<Integer>();
        for (int e : testElements){
            tree.insertI(e);
        }
        assertTrue(tree.hasI(50));
    }
    
    /** Test if internal node can fond in a tree - Recursive */
    @Test public void testHasRInternalTree(){
        Tree<Integer> tree = new Tree<Integer>();
        for (int e : testElements){
            tree.insertI(e);
        }
        assertTrue(tree.hasR(60));
    }

    /** Test if internal node element can fond in a tree - Iterative */
    @Test public void testHasIInternalTree(){
        Tree<Integer> tree = new Tree<Integer>();
        for (int e : testElements){
            tree.insertI(e);
        }
        assertTrue(tree.hasI(100));
    }


    /** Test if leaf node can fond in a tree - Recursive */
    @Test public void testHasRLeafTree(){
        Tree<Integer> tree = new Tree<Integer>();
        for (int e : testElements){
            tree.insertI(e);
        }
        assertTrue(tree.hasR(91));
    }

    /** Test if leaf node element can fond in a tree - Iterative */
    @Test public void testHasILeafTree(){
        Tree<Integer> tree = new Tree<Integer>();
        for (int e : testElements){
            tree.insertI(e);
        }
        assertTrue(tree.hasI(7));
    }

    /** Test LCA for sibling*/
    @Test public void testLCASiblings(){
        Tree<Integer> tree = new Tree<Integer>();
        for (int e : testElements){
            tree.insertI(e);
        }
        assertEquals(Integer.valueOf(25),tree.lowestCommonAncestor(12,35));        
    }

    /** Test LCA for  not sibling*/
    @Test public void testLCANotSiblings(){
        Tree<Integer> tree = new Tree<Integer>();
        for (int e : testElements){
            tree.insertI(e);
        }
        assertEquals(Integer.valueOf(75),tree.lowestCommonAncestor(60,91));        
    }

    
    /** Test LCA  when LCA is root */
    @Test public void testLCARoot(){
        Tree<Integer> tree = new Tree<Integer>();
        for (int e : testElements){
            tree.insertI(e);
        }
        assertEquals(Integer.valueOf(50),tree.lowestCommonAncestor(7,91));        
    }


    /** Test LCA  when LCA is one of the supplied nodes */
    @Test public void testLCAOneOfTheNodes(){
        Tree<Integer> tree = new Tree<Integer>();
        for (int e : testElements){
            tree.insertI(e);
        }
        assertEquals(Integer.valueOf(80),tree.lowestCommonAncestor(80,91));        
    }
}

