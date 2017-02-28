#include"header.h"

int main()
{
	sockaddr_in server;
	memset(&server, 0, sizeof(server));
	server.sin_port = htons(4567);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	int sfd = socket(AF_INET, SOCK_STREAM, 0);
	int s = connect(sfd, (sockaddr*) &server, sizeof(server));
	cout<<sfd<<' '<<s<<endl;
	close(sfd);
	return 0;
}
