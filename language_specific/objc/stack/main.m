#import <Foundation/Foundation.h>
#import "Stack.h"

int main() {
    
    @autoreleasepool {
        Stack* stack = [[Stack alloc] initialize];
        [stack push: @"A"];
        [stack push: @"B"];
        NSLog(@"The item on the top of stack is <%@>", [stack peek]);
        [stack pop];
        NSLog(@"The item on the top of stack is <%@>", [stack peek]);
        [stack pop];
        NSLog(@"The item on the top of stack is <%@>", [stack peek]);
        
    }
    
    return 0;
}