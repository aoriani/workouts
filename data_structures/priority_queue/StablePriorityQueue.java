import java.util.AbstractCollection;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.NoSuchElementException;
import java.util.Queue;

/**
 * <p>
 * A stable priority queue. Not only elements with higher priority are retrieved first, but
 * elements of the same priority are retrieved in a very defined order: FIFO.
 * </p>
 * <p>
 * Priority queues are generally a implemented as min or max heaps, what enables support for 
 * arbitrary priorities and an O(log n) performance for insertion and removals. Due the 
 * generality and performance of such approach, it is the choice of the PriorityQueue of Java 
 * Framework and  the priority_queue of STL and boost (C++). 
 * </p>
 * <p>
 * However the use of heaps renders a non stable data structure. 
 * The retrieving order for elements of same priority is undefined. Boost
 * provides stable heaps by using an atomic counter. When an item is inserted, the counter is 
 * incremented  and its value is recorded in the entry for the new element.That value is used 
 * to sort items of the same priority.
 * </p>
 * <p>
 * This implementation uses a different strategy. It assumes that the number of different 
 * priorities is small and known before hand. Thus it uses an array of queues. Each
 * element of the array represent a different priority. That simplification allows to
 * insert and remove elements in O(1).
 * </p>
 * @author André Oriani
 *
 * @param <E>
 */
public class StablePriorityQueue<E extends StablePriorityQueue.PrioritizedElement>
		extends AbstractCollection<E> implements Queue<E> {

	public interface PrioritizedElement {
		public int getPriority();
	}

	private class StablePriorityQueueIterator implements Iterator<E> {
		private int currPriority;
		private Iterator<E> currIterator;

		public StablePriorityQueueIterator() {
			currPriority = 0;
			currIterator = null;

			for (; currPriority < mNumberOfPriorities; currPriority++) {
				if (mQueues[currPriority] != null) {
					currIterator = mQueues[currPriority].iterator();
					break;
				}
			}
		}

		@Override
		public boolean hasNext() {
			if (currIterator == null) {
				return false;
			} else {
				if (currIterator.hasNext()) {
					return true;
				} else {

					if (currPriority < (mNumberOfPriorities - 1)) {
						currPriority++;
						while (currPriority < mNumberOfPriorities) {
							if (mQueues[currPriority] != null) {
								currIterator = mQueues[currPriority].iterator();
								if (currIterator.hasNext()) {
									return true;
								}
							}

							currPriority++;
						}

						// if next iterator not found
						currIterator = null;
						return false;

					} else {
						currIterator = null;
						return false;
					}

				}
			}

		}

		@Override
		public E next() {
			if (hasNext()) {
				return currIterator.next();
			} else {
				throw new NoSuchElementException();
			}
		}

		@Override
		public void remove() {
			if (currIterator != null) {
				currIterator.remove();
			} else {
				throw new IllegalStateException();
			}
		}

	}

	private final int mNumberOfPriorities;
	private final Queue<E> mQueues[];

	public StablePriorityQueue(int numberOfPriorities) {
		if (numberOfPriorities <= 1) {
			throw new IllegalArgumentException(
					"Must have at least two priorities levels");
		}

		mNumberOfPriorities = numberOfPriorities;
		mQueues = new Queue[mNumberOfPriorities];
	}

	@Override
	public boolean add(E e) {
		if (e == null) {
			throw new NullPointerException("Cannot add null elements");
		}

		int priority = e.getPriority();
		if ((priority < 0) || (priority >= mNumberOfPriorities)) {
			throw new IllegalArgumentException(
					"Element has invalid priority for the container");
		}

		if (mQueues[priority] == null) {
			mQueues[priority] = new LinkedList<E>();
		}

		return mQueues[priority].add(e);
	}

	@Override
	public E element() {
		E e = peek();
		if (e == null) {
			throw new NoSuchElementException();
		}
		return e;
	}

	@Override
	public boolean offer(E e) {
		return add(e);
	}

	@Override
	public E peek() {
		for (Queue<E> queue : mQueues) {
			if ((queue != null) && (!queue.isEmpty())) {
				return queue.peek();
			}
		}

		return null;
	}

	@Override
	public E poll() {
		for (Queue<E> queue : mQueues) {
			if ((queue != null) && (!queue.isEmpty())) {
				return queue.poll();
			}
		}

		return null;
	}

	@Override
	public E remove() {
		E e = poll();
		if (e == null) {
			throw new NoSuchElementException();
		}
		return e;
	}

	@Override
	public Iterator<E> iterator() {
		return new StablePriorityQueueIterator();
	}

	@Override
	public int size() {
		int size = 0;
		for (Queue<E> queue : mQueues) {
			if (queue != null) {
				size += queue.size();
			}
		}
		return size;
	}

}
