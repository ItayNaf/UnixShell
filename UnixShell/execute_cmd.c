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

int help_command(char** args, int len)
{
	if (len > 1)
	{
		printf("help has no arguments\n");
	}
	else
		help_menu();
	return RET_SUCCESS;
}
int exit_command(char** args, int len)
{
	if (len != 1)
	{
		printf("exit has no arguments\n");
	}
	return RET_SUCCESS;
}
int pwd_command(char** args, int len)
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
int cd_command(char** args, int len)
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
int mkdir_command(char** args, int len)
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
int rm_command(char** args, int len)
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
int ls_command(char** args, int len)
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
int cp_command(char** args, int len)
{
	if (len == 2)
	{
		if (strcmp(args[0], "--help") == 0)
			cp_help_menu();
		else
			printf("Uknown arguemt or path: %s, for help: cp --help\n", args[1]);
	}
	else if (len == 3)
	{
		int len_command = 4 + strlen(args[1]) + strlen(args[2]) + 2; // including 2 spaces, "copy"
		char* command = (char*)malloc(sizeof(char) * len_command + 1); // including null terminater
		snprintf(command, len_command + 1, "copy %s %s", args[1], args[2]);
		system(command);
		free(command);
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
			printf("Uknown arguemt or path: [%s], for help: cp --help\n", args[1]);
	}
	else
		printf("cp has no less than 2 arguments and no more than 3 arguments, for help: cp --help\n");
	return RET_SUCCESS;
}
int mv_command(char** args, int len)
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
int cat_command(char** args, int len)
{
	if (len != 2)
	{
		printf("cat accepts only one argument\n");
	}
	else
	{
		FILE* file = NULL;
		fopen_s(&file, args[1], "r");
		if (file == NULL)
		{
			printf("file cannot opened\n");
			return -1;
		}
		
		char c = fgetc(file);
		while (c != EOF)
		{
			printf("%c", c);
			c = fgetc(file);
		}
		fclose(file);
		printf("\n");
	}
	return RET_SUCCESS;
}
int ifconfig_command(char** args, int len)
{
	if (len == 1)
		system("ipconfig");
	else
		printf("ifconfig doesn't take arguments\n");
	return RET_SUCCESS;
}
int uname_command(char** args, int len)
{
	if (len == 1)
		system("systeminfo");
	else
		printf("uname doesn't take arguments\n");
	return RET_SUCCESS;
}
int clear_command(char** args, int len)
{
	if (len == 1)
		system("cls");
	else
		printf("cls doesn't take arguments\n");
	return RET_SUCCESS;
}

Command commands[] = {
	{"help", help_command},
	{"exit", exit_command},
	{"pwd", pwd_command},
	{"cd", cd_command},
	{"mkdir", mkdir_command},
	{"rm", rm_command},
	{"ls", ls_command},
	{"cp", cp_command},
	{"mv", mv_command},
	{"cat", cat_command},
	{"ifconfig", ifconfig_command},
	{"uname", uname_command},
	{"clear", clear_command}

};

int exec_cmd(char** args, int len)
{
	if (args[0][0] == '\0')
		return RET_SUCCESS;
	for (int i = 0; i < sizeof(commands) / sizeof(commands[i]); i++)
	{
		if (strcmp(args[0], commands[i].command) == 0)
		{
			int ret = commands[i].function(args, len);
			if (ret == RET_FAILURE)
			{
				printf("Error: command %s faild\n", commands[i].command);
				return RET_FAILURE;
			}
			return RET_SUCCESS;
		}
	}
	return RET_FAILURE;

}