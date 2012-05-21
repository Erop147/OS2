#include <stdio.h>
#include <unistd.h>
#include <poll.h>
#include <fcntl.h>

int main(int argc, char** argv)
{
	struct pollfd fds[256];
	int i, n=0;

	for(i=1; i<argc; ++i)
	{

		if(sscanf(argv[i], "%d", &fds[n++].fd) == 0)
		{
			n--;
		}
		else
		{
			int flags=fcntl(fds[n-1].fd, F_GETFL, 0);
			if(fcntl(fds[n-1].fd, F_SETFL, flags|O_NONBLOCK)==-1)
			{
				perror("non-block");
				n--;
			}
			fds[n-1].events=POLLIN;
		}
	}

	int res;

	while((res=poll(fds, n, 1000)) > 0)
	{
		char buff[10];
		int flag=0;

		for(i=0; i<n; ++i)
		{
			int r=read(fds[i].fd, buff, 10);
			if(r>0)
			{
				write(1, buff, r);
				flag=1;
			}
		}

		if(flag!=1)
		{
			break;
		}
	}

	if(res==0)
	{
		return 0;
	}
	else
	{
		perror("Poll");	
		return 1;
	}
}
