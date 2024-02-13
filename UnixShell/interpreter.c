#include "interpreter.h"

#define CMD_MAX_LEN 99

char* get_path()
{
	char* path;
	if ((path = _getcwd(0, NULL)) == NULL)
		printf("\nError has occured\n");
	else
	{
		return path;
	}
}

void ish_loop(char* username)
{
	char command[CMD_MAX_LEN + 1] = { 0 };
	
	remove_newline_from_input_stream();
	// Start Loop
	do
	{
		printf("%s@my_windows %s $ ", username, get_path());
		fgets(command, CMD_MAX_LEN, stdin);

		// Parse command
		int ret = parse_command(command);

	} while (strcmp(command, "exit") != 0);

}