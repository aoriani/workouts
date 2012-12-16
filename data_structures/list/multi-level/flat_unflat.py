class Node:
    def __init__(self, data,next=None,previous=None,child=None):
        self.data = data
        self.next = next
        self.previous = previous
        self.child = child
        
        
        
def printListRecursive(head, level=0):
    aux = head
    while aux is not None:
        print " "*level + aux.data
        if aux.child is not None:
            printListRecursive(aux.child, level + 4)
        aux = aux.next
        


def printList(head):
    aux = head
    while aux is not None:
        print "%s " % aux.data
        aux = aux.next  


def flatList(head, tail):
    assert head is not None, tail is not None
    aux=head
    while aux is not None:
        if aux.child is not None:
            tail = appendChild(tail,aux.child)
        aux = aux.next
        
        
def appendChild(tail, child):
    assert tail is not None
    tail.next,child.previous = child,tail
    tail = child
    while tail.next is not None: tail = tail.next
    return tail



def unflatList(head):
    assert head is not None
    aux = head
    while aux is not None:
        if aux.child is not None:
            aux.child.previous.next = None
            aux.child.previous = None
            unflatList(aux.child)
        aux = aux.next


if __name__ == "__main__":

    a = Node("a")
    a1 = Node("a1")
    a2 = Node("a2")
    a.child,a1.next,a2.previous = a1,a2,a1

    a21 = Node("a21")
    a22 = Node("a22")
    a2.child, a21.next, a22.previous = a21,a22,a21

    b = Node("b")
    b1 = Node("b1")
    b2 = Node("b2")
    b.child,b1.next,b2.previous = b1,b2,b1
    a.next,b.previous = b,a

    flatList(a,b)
    printList(a)
    unflatList(a)
    printListRecursive(a)


