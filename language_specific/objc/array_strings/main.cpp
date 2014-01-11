#include <iostream>
#include <array>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {

    array<string,3> list = {"A","B","C"};
    
    for (string& s: list) {
        cout<<s<<endl;
    }
    
    return 0;
}