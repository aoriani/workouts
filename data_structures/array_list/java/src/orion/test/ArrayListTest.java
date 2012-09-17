package orion.test;

import org.junit.Test;
import static org.junit.Assert.*;

import orion.ArrayList;

public class ArrayListTest{

    @Test
    public void testConstructor(){
        ArrayList<String> list = new ArrayList<String>();
        assertEquals("capacity should be four",4,list.capacity());
    }
    

}
