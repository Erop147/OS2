#include <stdio.h>
#include <unistd.h>

int main()
{
	while(true)
	{
		int pid = fork();
		if(pid)
		{

		}
		else
		{
			int e=setpgid(pid, 40000);
			if(e==-1)
			{
				fprintf(stderr, "err set pgid\n");
				continue;
			}

			e=getpgid(pid);

			if(e==-1)
			{
				fprintf(stderr, "err get pgid\n");
				continue;
			}

			if(printf("%d\n", e)<1)
			{
				fprintf(stderr, "err print\n");
				continue;
			}
		}
	}

	return 0;
}
