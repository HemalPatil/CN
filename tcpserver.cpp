#include"header.h"

int main()
{
	int nsfd;
	char buf[1024] = {0};
	gethostname(buf, 1023);
	cout<<"hostname : "<<buf<<endl;
	if((nsfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		cout<<"TCP socket error"<<endl;
		cout<<strerror(errno)<<endl;
		return 1;
	}
	int on = 1;
	if(setsockopt(nsfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
	{
		cout<<"TCP sockopt failed"<<endl;
		cout<<strerror(errno)<<endl;
		return 3;
	}
	sockaddr_in server, client;
	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(4567);
	server.sin_addr.s_addr = INADDR_ANY;
	if(bind(nsfd, (sockaddr*) &server, sizeof(server)) < 0)
	{
		cout<<"TCP bind failed"<<endl;
		cout<<strerror(errno)<<endl;
		return 2;
	}
	listen(nsfd, 5);
	while(true)
	{
		//cout<<"lolz"<<endl;
		sockaddr_in cli;
		socklen_t clil = sizeof(cli);
		int sfd = accept(nsfd, (sockaddr*) &cli, &clil);
		int port = ntohs(cli.sin_port);
		cout<<"connected to port:"<<port<<flush;
		close(sfd);
	}
	close(nsfd);
	return 0;
}
