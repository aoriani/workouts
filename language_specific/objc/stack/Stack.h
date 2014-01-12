#import <Foundation/Foundation.h>

@interface Stack : NSObject
{
    NSMutableArray* backingArray;
    int size;
}

- (Stack*) initialize;
- (void) push: (id) object;
- (void) pop;
- (id) peek;
@end