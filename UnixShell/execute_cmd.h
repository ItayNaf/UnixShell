typedef struct _Command {
	char* command;
	int(*function)(char** args, int len);
} Command;


int exec_cmd(char** args, int len);
void help_menu();
void rm_help_menu();
void ls_help_menu();
void cp_help_menu();

int help_command(char** args, int len);
int exit_command(char** args, int len);
int pwd_command(char** args, int len);
int cd_command(char** args, int len);
int mkdir_command(char** args, int len);
int rm_command(char** args, int len);
int ls_command(char** args, int len);
int cp_command(char** args, int len);
int mv_command(char** args, int len);
int cat_command(char** args, int len);
int ifconfig_command(char** args, int len);
int uname_command(char** args, int len);
int clear_command(char** args, int len);
