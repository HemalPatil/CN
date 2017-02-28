#include"header.h"

int c = 7;

void sighandler(int signum)
{
	cout<<"signal caught"<<endl;
	c--;
	if(c == 0)
	{
		signal(SIGINT, NULL);
	}
}

int main()
{
	signal(SIGINT, sighandler);
	while(true)
	{
		cout<<"Still sleeping"<<endl;
		sleep(1);
	}
	return 0;
}
