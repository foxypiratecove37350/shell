#ifndef COMMANDS_H
#define COMMANDS_H


typedef struct Command {
	char *name;
	char *usage;
	char *description;
	int (*execute)(const struct Command *cmd, int argc, char **argv);
} Command;

Command *getCommand(Command (*cmd_list)[], const char *name);

int help(const Command *cmd, int argc, char **argv);
int info(const Command *cmd, int argc, char **argv);
int pwd(const Command *cmd, int argc, char **argv);
int welcome(const Command *cmd, int argc, char **argv);
int changelog(const Command *cmd, int argc, char **argv);
int echo(const Command *cmd, int argc, char **argv);
int clear(const Command *cmd, int argc, char **argv);
int exit_cmd(const Command *cmd, int argc, char **argv);
int uname_cmd(const Command *cmd, int argc, char **argv);

extern Command command_list[];

int exec_extern_executable(const char *name, int argc, char **argv);


#endif
