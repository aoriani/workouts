#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>


struct shared{
	int a_b;
	int c_d;
	int e_f;
};
const int a=1,b=2,c=3,d=4,e=6,f=2;
const key_t key = 1234;
pid_t pab,pcd,pef;
void* shared_mem;

int main(){
	//Parent process create the shared memory 
	int shmid = shmget(key,sizeof(struct shared), 0666|IPC_CREAT);
	if(shmid == -1) exit(EXIT_FAILURE);
	
	//Fork child
	pab = fork();
	if(pab == 0){  
		//Inside process ab
		//attach to shared memory
		shared_mem = shmat(shmid,(void*) 0,0);
		if(shared_mem == (void*) -1) exit (EXIT_FAILURE);
		struct shared* shared_data = (struct shared*) shared_mem;
		shared_data->a_b = a +b;
		
		//detach
		if(shmdt(shared_mem) == -1) exit (EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}else {
		pcd = fork();
		if(pcd == 0){
			//Inside process cd
			//attach to shared memory
			shared_mem = shmat(shmid,(void*) 0,0);
			if(shared_mem == (void*) -1) exit (EXIT_FAILURE);
			struct shared* shared_data = (struct shared*) shared_mem;
			shared_data->c_d = c+d;
			
			//detach
			if(shmdt(shared_mem) == -1) exit (EXIT_FAILURE);
			exit(EXIT_SUCCESS);
			
		}else{
			pef = fork();
			if(pef == 0){
				//Inside process ef
				//attach to shared memory
				shared_mem = shmat(shmid,(void*) 0,0);
				if(shared_mem == (void*) -1) exit (EXIT_FAILURE);
				struct shared* shared_data = (struct shared*) shared_mem;
				shared_data->e_f = e/f;
				
				//detach
				if(shmdt(shared_mem) == -1) exit (EXIT_FAILURE);
				
				exit(EXIT_SUCCESS);
			}
		}
	}

	//Wait child process termination
	int status_ab,status_cd,status_ef;
	waitpid(pab,&status_ab,0);
	waitpid(pcd,&status_cd,0);
	waitpid(pef,&status_ef,0);
	
	//Check if all child exited  normally
	if(!WIFEXITED(status_ab) || !WIFEXITED(status_cd)||!WIFEXITED(status_ef)){
		exit(EXIT_FAILURE);
	}
	
	//Parent attaches to memory 
	shared_mem = shmat(shmid,(void*) 0,0);
	if(shared_mem == (void*) -1) exit (EXIT_FAILURE);
	struct shared* shared_data = (struct shared*) shared_mem;
	
	//Calculate result
	int result = (shared_data->a_b)*(shared_data->c_d)-(shared_data->e_f);
	printf("Result is %d\n", result);
		
	//Parent detaches from shared memory and deletes
	if(shmdt(shared_mem) == -1) exit (EXIT_FAILURE);
	if(shmctl(shmid,IPC_RMID,0) == -1) exit(EXIT_FAILURE);

	return EXIT_SUCCESS;

}


