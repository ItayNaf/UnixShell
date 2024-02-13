#include "shell.h"
#include "interpreter.h"

void help_menu()
{
	printf("This is a Unix-Based terminal that will convert all Unix-Based commands to Windows\n");
	printf("help - help menu\n");
	printf("pwd - print working directory\n");
	printf("cd - change working directory\n");
	printf("mkdir - create a new directory\n");
	printf("rm - remove, for help type: rm --help\n");
	printf("ls - list working directory, for help type: ls --help\n");
	printf("cp - copy a file, for help: cp --help\n");
	printf("mv - move files and renames files and directories\n");
	printf("cat - view contents of a file\n");
	printf("ifconfig - display ip information\n");
	printf("uname - display system information\n");
	printf("clear - clear the screen\n");
	printf("exit - exit shell\n");
}
void rm_help_menu()
{
	printf("rm - removes file\n");
	printf("-r - removes recursivly(rmdir), don't forget! to remove a directory it needs be empty of files\n");
	printf("--help - for rm help menu\n");
}
void ls_help_menu()
{
	printf("ls - list working directory\n");
	printf("-a - displays the names of all files, including hidden and system files\n");
	printf("--help - for ls help menu\n");
}
void cp_help_menu()
{
	printf("cp - copy file from source to destination\n");
	printf("cp <src> <dst> - copy file\n");
	printf("cp -r <src> <dst> - copy recursivly(copy directories)\n");
	printf("cp --help - for cp help menu\n");
}

int exec_cmd(char** args, int len)
{
	if (strcmp(args[0], "help") == 0)
	{
		if (len > 1)
		{
			printf("help has no arguments\n");
		}else
			help_menu();
		return RET_SUCCESS;
	}
	else if (strcmp(args[0], "exit") == 0)
	{
		if (len != 1)
			printf("exit has no arguments\n");
		return RET_SUCCESS;
	}
	else if (strcmp(args[0], "pwd") == 0)
	{
		if (len != 1)
		{
			printf("pwd has no arguments\n");
		}
		else
		{
			printf("%s\n", get_path());
		}
		return RET_SUCCESS;
		
	}
	else if(strcmp(args[0], "cd") == 0)
	{
		if (len == 2)
		{
			char* path = args[1];
			int ret = _chdir(path);
			if (ret != 0)
				printf("Unknown path: %s\n", path);
		}
		else
		{
			printf("cd has only one argument: cd <path>\n");
		}
		return RET_SUCCESS;
	}
	else if (strcmp(args[0], "mkdir") == 0)
	{
		if (len == 2)
		{
			char* path = args[1];
			int ret = _mkdir(path);
			if (ret != 0)
				printf("Unable to create dir in path: %s\n", path);
		}
		else
		{
			printf("mkdir has only one argument: mkdir <path>\n");
		}
		return RET_SUCCESS;
	}
	else if (strcmp(args[0], "rm") == 0)
	{
		if (len == 2)
		{
			if (strcmp(args[1], "--help") == 0)
				rm_help_menu();
			else
			{
				int ret = remove(args[1]);
				if (ret != 0)
					printf("Unable to remove file: %s\n", args[1]);
			}
		}
		else if (len == 3)
		{
			if (strcmp(args[1], "-r") == 0)
			{
				int ret = _rmdir(args[2]);
				if (ret != 0)
					printf("Unable to remove path: %s\n", args[2]);
			}
		}
		else
			printf("Read the help menu for help: rm --help\n");
		return RET_SUCCESS;
	}
	else if (strcmp(args[0], "ls") == 0)
	{
		if (len == 1)
		{
			system("dir");
		}
		else if (len == 2)
		{
			if (strcmp(args[1], "--help") == 0)
				ls_help_menu();
			else if (strcmp(args[1], "-a") == 0)
			{
				system("dir /a");
			}
			else
			{
				int len_command = 3 + strlen(args[1]) + 1; // including space and "dir" 
				char* command = (char*)malloc(sizeof(char) * len_command + 1); // including null terminater
				snprintf(command, len_command + 1, "dir %s", args[1]);
				system(command);
			}
		}
		else if (len == 3)
		{
			if (strcmp(args[1], "-a") == 0)
			{
				int len_command = 5 + strlen(args[2]) + 2; // including 2 spaces, "dir" and "/a"
				char* command = (char*)malloc(sizeof(char) * len_command + 1); // including null terminater
				snprintf(command, len_command + 1, "dir /a %s", args[2]);
				system(command);
				free(command);
			}
			else
			{
				printf("Unkown path or argument: %s, %s. for help: ls --help", args[1], args[2]);
			}
		}
		return RET_SUCCESS;
	}
	else if (strcmp(args[0], "cp") == 0)
	{
		if (len == 3)
		{
			int len_command = 4 + strlen(args[1]) + strlen(args[2]) + 2; // including 2 spaces, "copy"
			char* command = (char*)malloc(sizeof(char) * len_command + 1); // including null terminater
			snprintf(command, len_command + 1, "copy %s %s", args[1], args[2]);
			system(command);
			free(command);
		}
		else if (len == 2)
		{
			if (strcmp(args[0], "--help") == 0)
				cp_help_menu();
			else
				printf("Uknown arguemt or path: %s, for help: cp --help\n", args[1]);
		}
		else if (len == 4)
		{
			if (strcmp(args[1], "-r") == 0)
			{
				int len_command = 5 + 2 + 2 + strlen(args[2]) + strlen(args[3]) + 4; // including 4 spaces, "xcopy", "/E" and "/I"
				char* command = (char*)malloc(sizeof(char) * len_command + 1); // including null terminater
				snprintf(command, len_command + 1, "xcopy /E /I %s %s", args[2], args[3]);
				system(command);
				free(command);
			}
			else
				printf("Uknown arguemt or path, for help: cp --help\n");
		}
		else
			printf("cp has no less the 2 arguments and no more than 3 arguments, for help: cp --help\n");
		return RET_SUCCESS;
	}
	else if (strcmp(args[0], "mv") == 0)
	{
		if (len != 3)
		{
			printf("mv only accepts two arguments\n");
		}
		else
		{
			int ret = rename(args[1], args[2]);
			if (ret != 0)
				printf("mv did not succeed\n");
			printf("file: %s moved to %s\n", args[1], args[2]);
		}
		return RET_SUCCESS;	
	}
	else if (strcmp(args[0], "cat") == 0)
	{
		if (len != 2)
		{
			printf("cat accepts only one argument\n");
		}
		else
		{
			int len_command = 4 + strlen(args[1]) + 1; // including 1 space, "type"
			char* command = (char*)malloc(sizeof(char) * len_command + 1); // including null terminater
			snprintf(command, len_command + 1, "type %s", args[1]);
			system(command);
			free(command);
		}
		return RET_SUCCESS;
	}
	else if (strcmp(args[0], "ifconfig") == 0)
	{
		if (len == 1)
			system("ipconfig");
		else
			printf("ifconfig doesn't take arguments\n");
		return RET_SUCCESS;
	}
	else if (strcmp(args[0], "uname") == 0)
	{
		if (len == 1)
			system("systeminfo");
		else
			printf("uname doesn't take arguments\n");
		return RET_SUCCESS;
	}
	else if (strcmp(args[0], "clear") == 0)
	{
		if (len == 1)
			system("cls");
		else
			printf("cls doesn't take arguments\n");
		return RET_SUCCESS;
	}
	else if (args[0][0] == '\0')
		return RET_SUCCESS;
	return RET_FAILURE;
}