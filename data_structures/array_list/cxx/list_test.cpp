#include <string>
#include <stdexcept>
#include <gtest/gtest.h>
#include "list.h"

using std::string;
using std::size_t;

class ListTest:public ::testing::Test{
    protected:
        orion::List<string> list;
};

//==============================================================================
TEST_F(ListTest, defaultConstrutor){
    EXPECT_EQ(0, list.getSize());   
    EXPECT_EQ(4, list.getCapacity());
}

//==============================================================================
TEST_F(ListTest, copyConstrutor){
    list.insert_back("Hello");
    list.insert_back("World");
    list.insert_back("Foo");
    list.insert_back("Bar");    
    EXPECT_EQ(4, list.getSize());   
    EXPECT_EQ(4, list.getCapacity());
    
    orion::List<string> copy(list);
    EXPECT_EQ(4, copy.getSize());   
    EXPECT_EQ(4, copy.getCapacity());
    
    const size_t list_size = list.getSize();
    for(size_t i = 0;  i < list_size; i++){
        EXPECT_EQ(list[i],copy[i]);
    }
}

//==============================================================================
TEST_F(ListTest, assignmentOperatorSameCapacity){
    list.insert_back("Hello");
    list.insert_back("World");
    list.insert_back("Foo");
    list.insert_back("Bar");    
    
    orion::List<string> dest; //call default constructor
    dest = list; 
    
    EXPECT_EQ(4, dest.getSize());   
    EXPECT_EQ(4, dest.getCapacity());
    
    const size_t list_size = list.getSize();
    for(size_t i = 0;  i < list_size; i++){
        EXPECT_EQ(list[i],dest[i]);
    }
}

//==============================================================================
TEST_F(ListTest, assignmentOperatorDiffCapacity){
    list.insert_back("Hello");
    list.insert_back("World");
    list.insert_back("Foo");
    list.insert_back("Bar");
    //Add one more to force resize
    list.insert_back("Extra");    
    
    orion::List<string> dest; //call default constructor
    dest = list; 
    
    EXPECT_EQ(5, dest.getSize());   
    EXPECT_EQ(8, dest.getCapacity());
    
    const size_t list_size = list.getSize();
    for(size_t i = 0;  i < list_size; i++){
        EXPECT_EQ(list[i],dest[i]);
    }
}

//==============================================================================
TEST_F(ListTest, insertFront){        
    //Insert first
    list.insert_front("A");
    EXPECT_EQ(1, list.getSize());   
    EXPECT_EQ(4, list.getCapacity());
    
    //Insert second
    list.insert_front("B");
    EXPECT_EQ(2, list.getSize());   
    EXPECT_EQ(4, list.getCapacity());  
    
    //Insert +3 to force resize 
    list.insert_front("C");
    list.insert_front("D");
    list.insert_front("E");
    EXPECT_EQ(5, list.getSize());   
    EXPECT_EQ(8, list.getCapacity());  
    
    //Check if they are in the correct positions
    EXPECT_EQ(string("E"),list[0]);
    EXPECT_EQ(string("D"),list[1]);
    EXPECT_EQ(string("C"),list[2]);
    EXPECT_EQ(string("B"),list[3]);
    EXPECT_EQ(string("A"),list[4]);
}

//==============================================================================
TEST_F(ListTest, popFront){
    string testString[] = {"A","B","C","D","E"};
    for(int i = 0; i < 5; i++){
        list.insert_back(testString[i]);
    }
    EXPECT_EQ(8, list.getCapacity());
    
    //pop  elements
    for(int i=0; i<5; i++){
        EXPECT_EQ(testString[i], list.pop_front());
    }
    EXPECT_EQ(4, list.getCapacity());
    EXPECT_TRUE(list.isEmpty());    
}

//==============================================================================
TEST_F(ListTest, popBack){
    string testString[] = {"A","B","C","D","E"};
    for(int i = 0; i < 5; i++){
        list.insert_back(testString[i]);
    }
    EXPECT_EQ(8, list.getCapacity());
    
    //pop  elements
    for(int i=4; i>=0; i--){
        EXPECT_EQ(testString[i], list.pop_back());
    }
    EXPECT_EQ(4, list.getCapacity());
    EXPECT_TRUE(list.isEmpty());    
}

//==============================================================================
TEST_F(ListTest, popEmptyException){
   EXPECT_THROW(list.pop_front(),  std::length_error); 
   EXPECT_THROW(list.pop_back(),  std::length_error);
}

//==============================================================================
TEST_F(ListTest, contains){
    string testString[] = {"A","B","C","D","E"};
    for(int i = 0; i < 5; i++){
        list.insert_back(testString[i]);
    }
    
    EXPECT_TRUE(list.contains("C"));
    EXPECT_FALSE(list.contains("J"));
}

//==============================================================================
TEST_F(ListTest, remove){
    //Add one and remove
    list.insert_back("a");
    EXPECT_FALSE(list.remove("b"));
    EXPECT_EQ(1, list.getSize());
    EXPECT_TRUE(list.remove("a"));
    EXPECT_TRUE(list.isEmpty());
    
    //remove from middle
    list.insert_back("x");    
    list.insert_back("y");
    list.insert_back("z");
    EXPECT_TRUE(list.remove("y"));
    EXPECT_EQ(2, list.getSize());        
    EXPECT_EQ("x", list[0]);        
    EXPECT_EQ("z", list[1]);
    
    //remove first
    EXPECT_TRUE(list.remove("x"));
    EXPECT_EQ("z", list[0]);
    
    //remove last
    EXPECT_TRUE(list.remove("z"));
    EXPECT_TRUE(list.isEmpty());
}

//==============================================================================
TEST_F(ListTest, removeResize){
    string testString[] = {"A","B","C","D","E"};
    for(int i = 0; i < 5; i++){
        list.insert_back(testString[i]);
    }
    EXPECT_EQ(8, list.getCapacity());
    
    //remove items to downsize
    for(int i = 0; i < 5; i++){
        list.remove(testString[i]);
    } 
    
    EXPECT_EQ(4, list.getCapacity());
}

//==============================================================================
TEST_F(ListTest, subscriptOperatorException){
    EXPECT_THROW(list[-1], std::range_error);
    EXPECT_THROW(list[list.getSize()], std::range_error);
}

//==============================================================================
TEST_F(ListTest, iterators){
    string testString[] = {"A","B","C"};
    for(int i = 0; i < 3; i++){
        list.insert_back(testString[i]);
    }
    
    //Test begin and operator*
    orion::List<string>::Iterator it = list.begin();
    EXPECT_EQ(testString[0], (*it));
    
    //Test operator->
    EXPECT_EQ(testString[0].size(), it->size());
    
    //test postfix ++
    EXPECT_EQ(testString[0], *it++);
    EXPECT_EQ(testString[1], *it);
    
    //test prefix ++
    EXPECT_EQ(testString[2], *++it);
    
    //test end() and operator==
    ++it;
    EXPECT_EQ(list.end(), it);
    
}

//==============================================================================
int main(int argc, char* argv[]){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}


