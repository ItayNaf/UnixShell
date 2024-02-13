#include <stdio.h>
#include "interpreter.h"
#include "shell.h"


int main(void)
{

	// Run loop command.
	char username[11] = { 0 };
	printf("username: ");
	scanf_s("%10s", username, 10);
	printf("%s", OPENING);
	ish_loop(username); 

	return RET_SUCCESS;
}
