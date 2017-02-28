#include<iostream>
#include<string>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/un.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<errno.h>
#include<fcntl.h>

using namespace std;

const string sockpath = "/tmp/myunixsocket";
const string lolz = "/tmp/lolz";
cmsghdr *cmsg = NULL;

int sendfd(int usfd, int fd)
{
	msghdr msg;
	iovec iov;
	char buf[10] = "msgbuffer";
	iov.iov_base = buf;
	iov.iov_len = 10;
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;
	msg.msg_name = NULL;
	msg.msg_namelen = 0;
	if(cmsg == NULL)
	{
		cmsg = (cmsghdr*) malloc(CMSG_LEN(sizeof(fd)));
	}
	cmsg->cmsg_type = SCM_RIGHTS;
	cmsg->cmsg_len = CMSG_LEN(sizeof(int));
	cmsg->cmsg_level = SOL_SOCKET;
	msg.msg_control = cmsg;
	msg.msg_controllen = cmsg->cmsg_len;
	*(int*)CMSG_DATA(cmsg) = fd;
	int status = sendmsg(usfd, &msg, 0);
	if(status < 0)
	{
		cout<<strerror(errno)<<endl;
	}
	return status;
}

int main()
{
	int usfd;
	if((usfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
	{
		cout<<"Unix socket error"<<endl;
	}
	int on = 1;
	setsockopt(usfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
	sockaddr_un al, cl;
	socklen_t cli = sizeof(cl);
	memset(&al, 0, sizeof(al));
	al.sun_family = AF_UNIX;
	strcpy(al.sun_path, sockpath.c_str());
	unlink(sockpath.c_str());
	unlink(lolz.c_str());
	int ffd = open(lolz.c_str(), O_CREAT | O_RDWR, 0666);
	cout<<"ffd : "<<ffd<<endl;
	if(bind(usfd, (sockaddr*) &al, sizeof(al)) < 0)
	{
		cout<<"Unix socket bind failed"<<endl;
	}
	listen(usfd, 5);
	int nsfd = accept(usfd, (sockaddr*) &cl, &cli);
	cout<<"usfd : "<<usfd<<" nsfd : "<<nsfd<<endl;
	for(int i = 0; i < 5; i++)
	{
		int status = sendfd(nsfd, ffd);
		cout<<"send status : "<<status<<endl;
		write(ffd, "sender\n", strlen("sender\n"));
		sleep(2);
	}
	return 0;
}
