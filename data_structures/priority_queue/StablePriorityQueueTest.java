import java.util.Iterator;

import junit.framework.TestCase;

public class StablePriorityQueueTest extends TestCase {

	private class Element implements StablePriorityQueue.PrioritizedElement {
		private int priority, value;

		public Element(int priority, int value) {
			this.priority = priority;
			this.value = value;
		}

		@Override
		public int getPriority() {
			return priority;
		}

		@Override
		public int hashCode() {
			final int prime = 31;
			int result = 1;
			result = prime * result + getOuterType().hashCode();
			result = prime * result + priority;
			result = prime * result + value;
			return result;
		}

		@Override
		public boolean equals(Object obj) {
			if (this == obj)
				return true;
			if (obj == null)
				return false;
			if (getClass() != obj.getClass())
				return false;
			Element other = (Element) obj;
			if (!getOuterType().equals(other.getOuterType()))
				return false;
			if (priority != other.priority)
				return false;
			if (value != other.value)
				return false;
			return true;
		}

		private StablePriorityQueueTest getOuterType() {
			return StablePriorityQueueTest.this;
		}

		@Override
		public String toString() {
			return "Element [priority=" + priority + ", value=" + value + "]";
		}

	}

	private StablePriorityQueue<Element> queue;

	@Override
	protected void setUp() throws Exception {
		queue = new StablePriorityQueue<Element>(3);
	}

	@Override
	protected void tearDown() throws Exception {
		queue.clear();
	}

	public void testSize() {
		queue.offer(new Element(0, 1));
		queue.offer(new Element(1, 1));
		queue.offer(new Element(1, 2));
		queue.offer(new Element(2, 1));
		assertEquals("The queue should have a size of 4.", 4, queue.size());
	}

	public void testPeekEmpty() {
		assertNull(queue.peek());
	}

	public void testPeek() {
		queue.offer(new Element(1, 1));
		queue.offer(new Element(1, 2));
		queue.offer(new Element(2, 1));
		assertEquals("Was expecting Elementt(1,1)", new Element(1, 1),
				queue.peek());
	}

	public void testPeekWithRemoval() {
		queue.offer(new Element(1, 1));
		queue.poll();
		queue.offer(new Element(2, 1));
		queue.offer(new Element(2, 2));
		assertEquals("Was expecting Element(1,1)", new Element(2, 1),
				queue.peek());
	}

	public void testPollEmpty() {
		assertNull(queue.poll());
	}

	public void testPoll() {
		queue.offer(new Element(2, 1));
		queue.offer(new Element(1, 1));
		queue.offer(new Element(0, 1));
		queue.offer(new Element(2, 2));
		queue.offer(new Element(1, 2));
		queue.offer(new Element(0, 2));
		assertEquals("Was expecting Element(0,1)", new Element(0, 1),
				queue.poll());
		assertEquals("Was expecting Element(0,2)", new Element(0, 2),
				queue.poll());
		assertEquals("Was expecting Element(1,1)", new Element(1, 1),
				queue.poll());
		assertEquals("Was expecting Element(1,2)", new Element(1, 2),
				queue.poll());
		assertEquals("Was expecting Element(2,1)", new Element(2, 1),
				queue.poll());
		assertEquals("Was expecting Element(2,2)", new Element(2, 2),
				queue.poll());
	}

	public void testIteratorEmpty() {
		for (Element e : queue) {
			fail("Not expecting elements");
		}
	}

	public void testIteratorSingleElement() {
		queue.offer(new Element(0, 1));
		for (Element e : queue) {
			assertEquals("Was expecting Element(0,1)", new Element(0, 1), e);
		}
	}

	public void testIterator() {
		queue.offer(new Element(2, 1));
		queue.offer(new Element(1, 1));
		queue.offer(new Element(0, 1));
		queue.offer(new Element(2, 2));
		queue.offer(new Element(1, 2));
		queue.offer(new Element(0, 2));
		Iterator<Element> iterator = queue.iterator();
		assertTrue(iterator.hasNext());
		assertEquals(new Element(0, 1), iterator.next());
		assertEquals(new Element(0, 2), iterator.next());
		assertEquals(new Element(1, 1), iterator.next());
		assertEquals(new Element(1, 2), iterator.next());
		assertEquals(new Element(2, 1), iterator.next());
		assertEquals(new Element(2, 2), iterator.next());
		assertFalse(iterator.hasNext());
	}

	public void testIteratorAfterRemoval() {
		queue.offer(new Element(2, 2));
		queue.offer(new Element(1, 1));
		queue.poll();
		for (Element e : queue) {
			assertEquals("Was expecting Element(2,2)", new Element(2, 2), e);
		}
	}

}
