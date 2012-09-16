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


int main(int argc, char* argv[]){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}


