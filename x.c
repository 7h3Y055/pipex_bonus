#include <unistd.h>
#include <stdio.h>

void	child();

int main(int argc, char **argv)
{
	int id;
	argv += 1;

	if (*argv)
	{
		id = fork();
		argv += 1;
		child();
	}
}

void	child()
{
	printf("A\n");
}
