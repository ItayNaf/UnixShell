#include "parser.h"

void free_args(char* args[], int len)
{
	for (int i = 0; i < len; i++)
	{
		free(args[i]);
	}
	free(args);
}

void remove_newline_from_input_stream()
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF); // remove \n from input stream
}

void trim_string(char* string)
{
	char* start = string + strspn(string, " \t\n\r"); // Points to the first non-white space character in the string.
	if (string == start)
		return;
	strncpy_s(string, strlen(string), start, strlen(start));
}

int split_string_len(char string[], char split_val)
{
	int count_split_val = 1;
	for (int i = 0; i < strlen(string); i++)
	{
		if (string[i] == split_val)
			count_split_val++;
	}
	return count_split_val;
}

char** split_string(char string[], char split_val, int amount_args)
{

	char** args = (char**)malloc(sizeof(char*) * amount_args);
	if (args == NULL)
		return RET_FAILURE;

	int count_char = 0;
	int string_idx = 0;

	for (int i = 0, j = 0; i < strlen(string) + 1; i++)
	{
		if (string[i] != split_val && string[i] != '\0')
			count_char++;
		else
		{
			args[j] = (char*)malloc(sizeof(char) * count_char + 1);
			if (args[j] == NULL)
				return RET_FAILURE;
			args[j][count_char] = '\0';
			strncpy_s(args[j], count_char + 1, string + string_idx, count_char);
			string_idx += count_char + 1;
			j++;
			count_char = 0;
		}
	}

	return args;
}

int parse_command(char command[])
{
	if (strlen(command) > 0)
	{
		int command_len = strlen(command);
		
		if ((short)command[command_len - 1] == 10)
		{
			command[command_len - 1] = '\0';
		}
		
		// trim all whitespace
		trim_string(command);
		// split string with space
		int len = split_string_len(command, ' ');
		char** args = split_string(command, ' ', len);
		if (args == RET_FAILURE)
		{
			printf("Error happened during spliting of command\n");
			return RET_FAILURE;
		}

		int ret = exec_cmd(args, len);
		free_args(args, len);
		args = NULL;
		if (ret == RET_FAILURE)
		{
			printf("Command not recognized\n");
			return RET_FAILURE;
		}
		return RET_SUCCESS;
	}
	return RET_FAILURE;
}