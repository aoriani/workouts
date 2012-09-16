#include <string>
#include <gtest/gtest.h>
#include "list.h"

using std::string;
using std::size_t;

class ListTest:public ::testing::Test{
    protected:
        orion::List<string> list;
};


TEST_F(ListTest,defaultConstrutor){
    EXPECT_EQ(0, list.getSize());   
    EXPECT_EQ(4, list.getCapacity());
}

TEST_F(ListTest,copyConstrutor){
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

TEST_F(ListTest,assignmentOperatorSameCapacity){
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

TEST_F(ListTest,assignmentOperatorDiffCapacity){
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

TEST_F(ListTest,insertFront){        
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

TEST_F(ListTest,popFront){
    
}

int main(int argc, char* argv[]){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}


