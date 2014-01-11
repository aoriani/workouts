#import <Foundation/Foundation.h>

int main (int argc, char* argv[]){
	@autoreleasepool{
		NSArray* list = [NSArray arrayWithObjects: @"A", @"B", @"C",nil];
        
		for(NSString* s in list) {
			NSLog(@"%@", s);
		}
	}
	return 0;
}
