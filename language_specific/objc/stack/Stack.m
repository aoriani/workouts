#import <Foundation/Foundation.h>
#import "Stack.h"

@implementation Stack
{
    NSMutableArray* backingArray;
}

@synthesize size = _size;

//haven't reached the book section about constructors
-(id) init {
    self = [super init];
    if (self){
        backingArray = [[NSMutableArray alloc] init];
        _size = 0;
    }
    return self;
}

- (void) push: (id) object {
    if (object != nil) {
        [backingArray insertObject: object atIndex:0];
        ++_size;
    }
}

- (void) pop {
    if ([backingArray count] > 0) {
        [backingArray removeObjectAtIndex: 0];
        --_size;
    }
}

- (id) peek {
    return [backingArray firstObject];
}

@end