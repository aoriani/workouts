#import <Foundation/Foundation.h>

@interface Stack : NSObject

@property (nonatomic, readonly) int size;
- (id) init;
- (void) push: (id) object;
- (void) pop;
- (id) peek;

@end