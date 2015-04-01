/*
 This code spawns a shell.
 */


#include <stdlib.h>
#include <stdio.h>

main(){

	char *args[2];

	args[0] = "/bin/bash";
	args[1] = NULL;

	execve(args[0], args, NULL);

	exit(0);
}
