import unittest

class Node:
    def __init__(self, data, next=None):
        self.next = next
        self.data = data
        

#===============================================================================
def hasCycleFloyd(head):
    if head is None: return False

    hare,turtoise = head, head
    
    while True:
        hare = hare.next;
        if hare is None: return False
        if hare is turtoise: return True
       
        hare = hare.next;
        if hare is None: return False
        if hare is turtoise: return True 
        
        turtoise = turtoise.next
        

#===============================================================================
def hasCycleBrent(head):
    if head is None: return False

    hare,turtoise = head,head
    step = 2 
    
    while True:
        for i in range(step):
            hare = hare.next
            if hare is None: return False
            if hare is turtoise: return True
        step *=2 
        turtoise = hare
        
        
        
        
#===============================================================================


noCycleList = Node(1,Node(2,Node(3,Node(4,Node(5,Node(6,Node(7,Node(8,Node(9)))))))))

LoopHole = Node(9)
LongCycleList = Node(1,Node(2,Node(3,Node(4,Node(5,Node(6,Node(7,Node(8,LoopHole))))))))
LoopHole.next = LongCycleList


LoopHole = Node(9)
MiddleCycleList = Node(1,Node(2,Node(3,Node(4,Node(5,Node(6,Node(7,Node(8,LoopHole))))))))
LoopHole.next = LongCycleList.next.next.next.next


class CycleInList(unittest.TestCase):

    def testNoCycleFloyd(self):
        self.assertFalse(hasCycleFloyd(noCycleList))        

    def testNoCycleBrent(self):
        self.assertFalse(hasCycleBrent(noCycleList))

    def testLongCycleFloyd(self):
        self.assertTrue(hasCycleFloyd(LongCycleList))        

    def testLongCycleBrent(self):
        self.assertTrue(hasCycleBrent(LongCycleList))
        
    def testMiddleCycleFloyd(self):
        self.assertTrue(hasCycleFloyd(MiddleCycleList))        

    def testMiddleCycleBrent(self):
        self.assertTrue(hasCycleBrent(MiddleCycleList))        


        
if __name__ == "__main__":
    unittest.main()
    
            
