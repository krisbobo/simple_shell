#include <unistd.h>
#include <stdio.h>

int main(void)
{
	extern char **environ;
	int i = 0;
	char *s = *environ;

	while (s)
	{
		printf("%s\n", s);
		s = environ[i++];
	}
	return (1);
}
