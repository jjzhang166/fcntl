#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int set_non_block(int fd)
{
	int old_fl=fcntl(fd,F_GETFL);
	if(old_fl<0)
	{
		perror("fcntl");
		return -1;
	}

	if(fcntl(fd,F_SETFL,old_fl|O_NONBLOCK)<0)
	{
		perror("fcntl");
		return -1;
	}
	return 0;
}

int main()
{
	set_non_block(0);
	char buf[1024];
	while(1)
	{
		memset(buf,'\0',sizeof(buf));
		ssize_t _s=read(0,buf,sizeof(buf)-1);
		if(_s>0)
		{
			buf[_s-1]='\0';
			printf("%s\n",buf);
		}
		else
		{
			if(errno==EAGAIN)
			{
				printf("######## :%d\n",errno);
			}
		}
		sleep(1);
	}
	return 0;
}
