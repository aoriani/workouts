#include "doublelinked.h"
#include <cassert>
#include <iostream>
using namespace std;

//Not the best test suite ( not fully automatic)
#define BEGIN_TEST(x) void x () { \
                        cout<<endl<<"Running "<<#x<<endl;
                        
#define END_TEST cout<<"End"<<endl<<endl; }                        


BEGIN_TEST(testInsertFront)
    DoubleLinkedList<int> list;
    list.insertFront(1);
    list.printList();
    list.printListReverse();
    list.insertFront(2);
    list.insertFront(3);
    list.printList();
    list.printListReverse();    
END_TEST

BEGIN_TEST(testInsertBack)
    DoubleLinkedList<int> list;
    list.insertBack(1);
    list.printList();
    list.printListReverse();
    list.insertBack(2);
    list.insertBack(3);
    list.printList();
    list.printListReverse();    
END_TEST

BEGIN_TEST(testRemoveEmpty)
    DoubleLinkedList<int> list;
    assert(!list.remove(4));
END_TEST

BEGIN_TEST(testRemoveSingle)
    DoubleLinkedList<int> list;
    list.insertFront(4);
    assert(list.remove(4));
    list.printList();
    list.printListReverse();    
END_TEST

BEGIN_TEST(testRemoveHead)
    DoubleLinkedList<int> list;
    list.insertFront(4);
    list.insertFront(5);
    list.insertFront(6);
    assert(list.remove(6));
    list.printList();
    list.printListReverse();    
END_TEST

BEGIN_TEST(testRemoveTail)
    DoubleLinkedList<int> list;
    list.insertFront(4);
    list.insertFront(5);
    list.insertFront(6);
    assert(list.remove(4));
    list.printList();
    list.printListReverse();    
END_TEST

BEGIN_TEST(testRemoveMiddle)
    DoubleLinkedList<int> list;
    list.insertFront(4);
    list.insertFront(5);
    list.insertFront(6);
    assert(list.remove(5));
    list.printList();
    list.printListReverse();    
END_TEST

BEGIN_TEST(testRemoveNotFound)
    DoubleLinkedList<int> list;
    list.insertFront(4);
    list.insertFront(5);
    list.insertFront(6);
    assert(!list.remove(55));
END_TEST

BEGIN_TEST(testInsertAfterEmpty)
    DoubleLinkedList<int> list;
    assert(!list.insertAfter(55,4));
END_TEST

BEGIN_TEST(testInsertAfterNewTail1)
    DoubleLinkedList<int> list;
    list.insertFront(1);
    assert(!list.insertAfter(2,4));
    list.printList();
    list.printListReverse();    
END_TEST

BEGIN_TEST(testInsertAfterNewTail2)
    DoubleLinkedList<int> list;
    list.insertFront(1);
    assert(list.insertAfter(1,4));
    list.printList();
    list.printListReverse();    
END_TEST

BEGIN_TEST(testInsertAfterNewTail3)
    DoubleLinkedList<int> list;
    list.insertFront(1);
    list.insertFront(2);
    assert(list.insertAfter(2,4));
    list.printList();
    list.printListReverse();    
END_TEST

BEGIN_TEST(testInsertAfterMiddle)
    DoubleLinkedList<int> list;
    list.insertFront(1);
    list.insertFront(2);
    list.insertFront(3);    
    assert(list.insertAfter(2,4));
    list.printList();
    list.printListReverse();    
END_TEST

BEGIN_TEST(testCopyConstructorEmptyList)
    DoubleLinkedList<int> list;
    DoubleLinkedList<int> list2(list);
    list2.printList();
    list2.printListReverse();    
END_TEST

BEGIN_TEST(testCopyConstructorSingleElem)
    DoubleLinkedList<int> list;
    list.insertFront(1);
    DoubleLinkedList<int> list2(list);
    list2.printList();
    list2.printListReverse();    
END_TEST

BEGIN_TEST(testCopyConstructorManyElem)
    DoubleLinkedList<int> list;
    list.insertFront(1);
    list.insertFront(2);
    list.insertFront(3);
    DoubleLinkedList<int> list2(list);
    list2.printList();
    list2.printListReverse();    
END_TEST

BEGIN_TEST(testAssignEmptyEmpty)
    DoubleLinkedList<int> list;
    DoubleLinkedList<int> list2;
    list2 = list;
    list2.printList();
    list2.printListReverse();    
END_TEST

BEGIN_TEST(testAssignEmptySome)
    DoubleLinkedList<int> list;
    list.insertFront(1);
    list.insertFront(2);
    DoubleLinkedList<int> list2;
    list2 = list;
    list2.printList();
    list2.printListReverse();    
END_TEST

BEGIN_TEST(testAssignSomeEmpty)
    DoubleLinkedList<int> list;
    DoubleLinkedList<int> list2;
    list2.insertFront(1);
    list2.insertFront(2);
    list2 = list;
    list2.printList();
    list2.printListReverse();    
END_TEST

BEGIN_TEST(testAssignEqualSized)
    DoubleLinkedList<int> list;
    DoubleLinkedList<int> list2;
    list.insertFront(9);
    list.insertFront(99);
    list2.insertFront(1);
    list2.insertFront(2);
    list2 = list;
    list2.printList();
    list2.printListReverse();    
END_TEST



BEGIN_TEST(testAssignBigShort)
    DoubleLinkedList<int> list;
    DoubleLinkedList<int> list2;
    list.insertFront(9);
    list.insertFront(99);
    list2.insertFront(1);
    list2.insertFront(2);
    list2.insertFront(3);
    list2.insertFront(4);    
    list2 = list;
    list2.printList();
    list2.printListReverse();    
END_TEST

BEGIN_TEST(testAssignShortBig)
    DoubleLinkedList<int> list;
    DoubleLinkedList<int> list2;
    list2.insertFront(9);
    list2.insertFront(99);
    list.insertFront(1);
    list.insertFront(2);
    list.insertFront(3);
    list.insertFront(4);    
    list2 = list;
    list2.printList();
    list2.printListReverse();    
END_TEST

int main(){
    testInsertFront();
    testInsertBack();
    testRemoveEmpty();
    testRemoveSingle();
    testRemoveHead();
    testRemoveTail();
    testRemoveMiddle();
    testRemoveNotFound();
    testInsertAfterEmpty();
    testInsertAfterNewTail1();
    testInsertAfterNewTail2();
    testInsertAfterNewTail3();
    testInsertAfterMiddle();
    testCopyConstructorEmptyList();
    testCopyConstructorSingleElem();
    testCopyConstructorManyElem();
    testAssignEmptyEmpty();
    testAssignEmptySome();
    testAssignSomeEmpty(); 
    testAssignEqualSized();
    testAssignBigShort();
    testAssignShortBig();
    
    return 0;
}

