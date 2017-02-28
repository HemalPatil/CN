#include"header.h"

int main()
{
	int nsfd;
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
	listen(
	return 0;
}
