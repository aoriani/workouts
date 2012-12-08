#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define TRUE 1
#define FALSE 0
#define TAPE_SIZE 64

extern unsigned int sleep(unsigned int seconds);


typedef int bool;

enum turing_action_t {
	LEFT,
	RIGHT,
	HALT
};

struct rule {
	int state;
	char in_symbol;
	int new_state;
	char out_symbol;
	enum turing_action_t action;	
};

struct rule* find_matching_rule(struct rule rules[], int nrules, int state, char in_sym){
	for (int i = 0; i < nrules; i++ ){
		if ((rules[i].state == state) && (rules[i].in_symbol == in_sym)) {
			return &(rules[i]);
		}
	}
	return NULL;
}


bool applyRule(char tape[], int* curr_state, int* curr_pos,struct rule* rule_toapply){
	tape[*curr_pos] = rule_toapply->out_symbol;
	*curr_state = rule_toapply->new_state;
	int new_pos = *curr_pos;
	switch (rule_toapply->action) {
		case LEFT:
			new_pos--;
			break;
		case RIGHT:
			new_pos++;
			break;

		default:
			break;
	}
	
	if ((rule_toapply->action == HALT) || (new_pos<0) || (new_pos>= TAPE_SIZE)) {
		return FALSE;
	}else {
		*curr_pos = new_pos;
		return TRUE;
	}
}

static inline void drawhead(const int pos){
	for (int i = 1; i< pos; i++) {
		putchar(' ');
	}
	putchar('|');
	putchar('\n');
}


void drawTuring(const int curr_state, const int curr_pos, const char tape[]){	
	system("clear");
	drawhead(curr_pos);
	printf("%s\n",tape);
	printf("State: %d\n",curr_state);
	sleep(2);
}


int main(){
	int curr_state =1 ;
	int curr_pos = 0;
	char tape[TAPE_SIZE+1]= {'0','1','1','0','0','1','1','0','0','1','1','0','0','1','1','0','0','1','1','0','0','1','1','0'};
	struct rule rules[] = { {1,'0',1,'1',RIGHT},{1,'1',1,'0',RIGHT}, {1,0,1,0,HALT}};
	struct rule* curr_rule = find_matching_rule(rules,3,curr_state,tape[curr_pos]);
	while(curr_rule != NULL && applyRule(tape,&curr_state,&curr_pos, curr_rule)){
		drawTuring(curr_state,curr_pos,tape);
		curr_rule = find_matching_rule(rules,3,curr_state,tape[curr_pos]);
	}
	
	return EXIT_SUCCESS;
	
}




