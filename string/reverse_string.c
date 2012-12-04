#include <stdio.h>
#include <string.h>

/**
 * Reverse a string in place
 */
void reverse(char* string){
	int upper = strlen(string) - 1;
	int lower = 0;

	while(lower < upper){
		char tmp = string[lower];
		string[lower]= string[upper];
		string[upper] = tmp;
		lower++;
		upper--;
	} 
}

//TODO: do without the temp var


int main(){

	char text[] = "12345";
	reverse(text);
	printf("The reversed string is %s \n",text);
	return 0;
}

