#import <Foundation/Foundation.h>
#import "Stack.h"

@implementation Stack

//haven't reached the book section about constructors
-(Stack*) initialize {
    backingArray = [[NSMutableArray alloc] init];
    size = 0;
    return self;
}

- (void) push: (id) object {
    if (object != nil) {
        [backingArray insertObject: object atIndex:0];
        ++size;
    }
}

- (void) pop {
    if ([backingArray count] > 0) {
        [backingArray removeObjectAtIndex: 0];
        --size;
    }
}

- (id) peek {
    return [backingArray firstObject];
}

@end