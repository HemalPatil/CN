#include"header.h"

int main()
{
	int key = ftok("shm", 'a');
	int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666 | SHM_R | SHM_W);
	if(shmid < 0)
	{
		cout<<"shmget failed"<<endl;
		return 1;
	}
	int* ptr;
	if((ptr = (int*) shmat(shmid, NULL, 0)) <= 0)
	{
		cout<<"shmat failed"<<endl;
		return 2;
	}
	*ptr = 10;
	for(int i = 0; i < 5; i++)
	{
		sleep(1);
		(*ptr)++;
	}
	return 0;
}
