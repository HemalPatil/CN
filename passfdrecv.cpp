#include"header.h"

const string sockpath = "/tmp/myunixsocket";
cmsghdr *cmsg = NULL;

int recvfd(int usfd, int &fd)
{
	msghdr msg;
	iovec iov;
	char buf[10];
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
	msg.msg_control = cmsg;
	msg.msg_controllen = CMSG_LEN(sizeof(fd));
	int status;
	if((status = recvmsg(usfd, &msg, 0)) < 0)
	{
		fd = ~0;
		return status;
	}
	fd = *(int*)CMSG_DATA(cmsg);
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
	sockaddr_un al;
	memset(&al, 0, sizeof(al));
	al.sun_family = AF_UNIX;
	strcpy(al.sun_path, sockpath.c_str());
	connect(usfd, (sockaddr*) &al, sizeof(al));
	int fd;
	for(int i = 0; i < 5; i++)
	{
		int status = recvfd(usfd, fd);
		cout<<"status : "<<status<<endl;
		cout<<fd<<endl;
		write(fd, "recvr\n", strlen("recvr\n"));
		close(fd);
		sleep(1);
	}
	close(usfd);
	return 0;
}
