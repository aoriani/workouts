package orion;

import java.util.Collection;
import java.util.Iterator;
import java.util.List;
import java.util.ListIterator;

/**
 * A simple(?) implementation of an array list
 * @author André Oriani
 */
public class ArrayList<T> implements List<T>{

    private static final int INITIAL_CAPACITY =4;

    private int capacity = INITIAL_CAPACITY;
    private int size = 0 ;
    private T[] array = (T[])new Object[capacity];


    public ArrayList(){}
    
    /**
     * {@inheritDoc}
     */
    @Override
    public boolean add(T elem){
        throw new UnsupportedOperationException();
    }

    /**
     * {@inheritDoc}
     */    
    @Override
    public void add(int index, T element){
        throw new UnsupportedOperationException();    
    }

    /**
     * {@inheritDoc}
     */    
    @Override
    public boolean addAll(Collection<? extends T> c){
        throw new UnsupportedOperationException();    
    }

    /**
     * {@inheritDoc}
     */    
    @Override
    public boolean addAll(int index, Collection<? extends T> c){
        throw new UnsupportedOperationException();    
    }

    /**
     * {@inheritDoc}
     */    
    @Override
    public void clear(){
        throw new UnsupportedOperationException();    
    }
    
    /**
     * {@inheritDoc}
     */    
    @Override
    public boolean contains(Object o){
        throw new UnsupportedOperationException();    
    }
    
    /**
     * {@inheritDoc}
     */    
    @Override
    public boolean containsAll(Collection<?> c){
        throw new UnsupportedOperationException();    
    }

    /**
     * {@inheritDoc}
     */    
    @Override
    public boolean equals(Object c){
        throw new UnsupportedOperationException();    
    }

    /**
     * {@inheritDoc}
     */    
    @Override
    public int hashCode(){
        throw new UnsupportedOperationException();    
    }
    
    /**
     * {@inheritDoc}
     */    
    @Override
    public T get(int index){
        throw new UnsupportedOperationException();    
    }

    /**
     * {@inheritDoc}
     */    
    @Override
    public int indexOf(Object o){
        throw new UnsupportedOperationException();    
    }
    
    /**
     * {@inheritDoc}
     */    
    @Override
    public boolean isEmpty(){
        throw new UnsupportedOperationException();    
    }        

    /**
     * {@inheritDoc}
     */    
    @Override
    public Iterator<T> iterator(){
        throw new UnsupportedOperationException();    
    }        

    /**
     * {@inheritDoc}
     */    
    @Override
    public int lastIndexOf(Object o){
        throw new UnsupportedOperationException();    
    }        

    /**
     * {@inheritDoc}
     */    
    @Override
    public ListIterator<T> listIterator(){
        throw new UnsupportedOperationException();    
    }        

    /**
     * {@inheritDoc}
     */    
    @Override
    public ListIterator<T> listIterator(int index){
        throw new UnsupportedOperationException();    
    }        

    /**
     * {@inheritDoc}
     */    
    @Override
    public T remove(int index){
        throw new UnsupportedOperationException();    
    }        

    /**
     * {@inheritDoc}
     */    
    @Override
    public boolean remove(Object o){
        throw new UnsupportedOperationException();    
    }
    
    /**
     * {@inheritDoc}
     */    
    @Override
    public boolean removeAll(Collection<?> c){
        throw new UnsupportedOperationException();    
    }
     
    /**
     * {@inheritDoc}
     */    
    @Override
    public boolean retainAll(Collection<?> c){
        throw new UnsupportedOperationException();    
    }

    /**
     * {@inheritDoc}
     */    
    @Override
    public T set(int index, T elememt){
        throw new UnsupportedOperationException();    
    }

    /**
     * {@inheritDoc}
     */    
    @Override
    public int size(){
        throw new UnsupportedOperationException();    
    }
    
    /**
     * {@inheritDoc}
     */    
    @Override
    public List<T> subList(int fromIndex, int toIndex){
        throw new UnsupportedOperationException();    
    }

    /**
     * {@inheritDoc}
     */    
    @Override
    public Object[] toArray(){
        throw new UnsupportedOperationException();    
    }

    /**
     * {@inheritDoc}
     */    
    @Override
    public <T> T[] toArray(T[] a){
        throw new UnsupportedOperationException();    
    }
}

