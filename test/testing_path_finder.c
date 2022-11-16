#include "../shell.h"
#include <unistd.h>
#include <stdio.h>

int main(void)
{
	extern char **environ;
	char *path = NULL;

	path = get_file_path("rpcbind", environ);
	printf("get_file_path got:%s\n", path);
	return (1);
}
