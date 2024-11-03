#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/utsname.h>
#include <sys/wait.h>

#include "commands.h"
#include "meta_data.h"
#include "utils.h"


Command* getCommand(Command (*cmd_list)[], const char *name) {
	if (strcmp(name, "") == 0) {
		return ((void*)-1);
	}

	for (int i = 0; (*cmd_list)[i].name != NULL; i++) {
		if (strcmp((*cmd_list)[i].name, name) == 0) {
			return &(*cmd_list)[i];
		}
	}

	return NULL;
}

Command command_list[] = {
	{"help", "[command]", "Display this help message", help},
	{"info", "[-d]", "Display info about the shell", info},
	{"pwd", "", "Print the current working directory", pwd},
	{"welcome", "", "Print all the welcome messages", welcome},
	{"changelog", "[version | *]", "Print the changes since the last release", changelog},
	{"echo", "[TEXT | \"TEXT\"]", "Print text to the screen", echo},
	{"uname", "[-a | -s | -n | -r | -v | -m | -p | -i | -o]", "Display current machine information", uname_cmd},
	{"clear", "", "Clear the terminal.", clear},
	{"exit", "[code]", "Exit the terminal.", exit_cmd},
	{NULL, NULL, NULL, NULL} // Sentinel
};

int help(const Command *cmd, const int argc, char **argv) {
	if (argc == 1) {
		color_print("Available commands:\n");

		for (int i = 0; command_list[i].name != NULL; i++) {
			color_print("- %s: %s\n\t%s\n\n", command_list[i].name, command_list[i].usage, command_list[i].description);
		}
	} else if (argc == 2) {
		const Command *_cmd = getCommand(&command_list, argv[1]);
		if (_cmd == NULL) {
			fprintf(stderr, "Command not found\n");
			return 1;
		}

		color_print("%s: %s\n    %s\n", _cmd->name, _cmd->usage, _cmd->description);
	} else {
        fprintf(stderr, "Usage: %s %s\n", cmd->name, cmd->usage);
		return 2;
	}

	return 0;
}

int info(const Command *cmd, const int argc, char **argv) {
	if (argc == 2 && strcmp(argv[1], "-d") == 0) {
		char c_standard[4];
		c_standard[3] = '\0';
		#ifdef __STDC_VERSION__
			c_standard[0] = 'C';
			c_standard[1] = (__STDC_VERSION__ / 10) % 10 + '0';
			c_standard[2] = (__STDC_VERSION__ / 100) % 10 + '0';
		#else
			c_standard[0] = 'U';
			c_standard[1] = 'n';
			c_standard[2] = 'k'; 
		#endif

        color_print("\033[38;2;255;255;0m%s\033[0m \033[32mv%s\033[0m\n"
					"by \033[91m%s\033[0m\n"
					"Compiled using the \033[94m%s\033[0m standard\n", product_name, version, author, c_standard);
	} else if (argc == 1) {
        color_print("\033[38;2;255;255;0m%s\033[0m \033[32mv%s\033[0m\nby \033[91m%s\033[0m\n",
        	product_name, version, author);
	} else {
        fprintf(stderr, "Usage: %s %s\n", cmd->name, cmd->usage);
		return 1;
	}

	return 0;
}

int pwd(const Command *cmd, const int argc, char **argv) {
    if (argc > 1) {
        fprintf(stderr, "Usage: %s %s\n", cmd->name, cmd->usage);
        return 2;
    }

	color_print("%s\n", getcwd(NULL, 0));

	return 0;
}

int welcome(const Command *cmd, const int argc, char **argv) {
	if (argc > 1) {
		fprintf(stderr, "Usage: %s %s\n", cmd->name, cmd->usage);
		return 2;
	}

	color_print("Welcomes messages:\n");

	for (int i = 0; i < welcome_messages_num; i++) {
		color_print(welcome_messages[i], product_name);
		color_print("\n");
	}

	return 0;
}

int changelog(const Command *cmd, const int argc, char **argv) {
	if (argc > 2) {
		fprintf(stderr, "Usage: %s %s\n", cmd->name, cmd->usage);
		return 2;
	}

	if (argc == 1) {
		color_print("%s", changelogs[0]);
		return 0;
	}

	if (strcmp(argv[1], "*") == 0) {
		for (size_t i = 0; changelogs[i] != NULL; i++) {
			color_print("%s", changelogs[i]);
		}

		return 0;
	}

	const char *_changelog = find_changelog(argv[1]);

	if (_changelog == NULL) {
		fprintf(stderr, "Error: Couldn't retrieve the changelog for the version \"%s\"\n", argv[1]);
		return 1;
	}

	color_print("%s", _changelog);

	return 0;
}

int uname_cmd(const Command *cmd, const int argc, char **argv) {
    struct utsname buffer;
    if (uname(&buffer) != 0) {
		fprintf(stderr, "Error: Error while retrieving system information\n");
        return 1;
    }

    int printAll = 0, printKernelName = 0, printNodeName = 0, printKernelRelease = 0, printKernelVersion = 0,
		printMachine = 0, printProcessor = 0, printHardwarePlatform = 0, printOperatingSystem = 0;

    if (argc == 1) {
        printKernelName = 1;
    } else {
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "--all") == 0) {
                printAll = 1;
            } else if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--kernel-name") == 0) {
                printKernelName = 1;
            } else if (strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "--nodename") == 0) {
                printNodeName = 1;
            } else if (strcmp(argv[i], "-r") == 0 || strcmp(argv[i], "--kernel-release") == 0) {
                printKernelRelease = 1;
            } else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--kernel-version") == 0) {
                printKernelVersion = 1;
            } else if (strcmp(argv[i], "-m") == 0 || strcmp(argv[i], "--machine") == 0) {
                printMachine = 1;
            } else if (strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--processor") == 0) {
                printProcessor = 1;
            } else if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--hardware-platform") == 0) {
                printHardwarePlatform = 1;
            } else if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--operating-system") == 0) {
                printOperatingSystem = 1;
            } else {
                fprintf(stderr, "Usage: %s %s\n", cmd->name, cmd->usage);
                return 1;
            }
        }
    }

    if (printAll || printKernelName) {
        color_print("%s ", buffer.sysname);
    }
    if (printAll || printNodeName) {
        color_print("%s ", buffer.nodename);
    }
    if (printAll || printKernelRelease) {
        color_print("%s ", buffer.release);
    }
    if (printAll || printKernelVersion) {
        color_print("%s ", buffer.version);
    }
    if (printAll || printMachine) {
        color_print("%s ", buffer.machine);
    }
    if (printAll || printProcessor) {
        color_print("%s ", buffer.machine); // (non-portable)
    }
    if (printAll || printHardwarePlatform) {
        color_print("%s ", buffer.machine); // (non-portable)
    }
    if (printAll || printOperatingSystem) {
        color_print("%s ", buffer.sysname);
    }

    color_print("\n");

    return 0;
}

int echo(const Command *cmd, const int argc, char **argv) {
	int i = 1;

	if (argc > 2) {
		for (i = 1; i < argc - 1; i++) {
			color_print("%s ", argv[i]);
		}

		color_print("%s", argv[i]);
	} else if (argc == 2) {
		color_print("%s", argv[i]);
	}

    printf("\n");

	return 0;
}

int clear(const Command *cmd, const int argc, char **argv) {
    if (argc > 1) {
        fprintf(stderr, "Usage: %s %s\n", cmd->name, cmd->usage);
        return 2;
    }

	color_print("\033c\033[2J\033[1;1H");

	return 0;
}

int exit_cmd(const Command *cmd, const int argc, char **argv) {
    if (argc > 2) {
        fprintf(stderr, "Usage: %s %s\n", cmd->name, cmd->usage);
        return 2;
    }

	if (argc == 1) {
		exit(0);
	}

    char *endptr;
    const int exit_code = strtol(argv[1], &endptr, 10);

    if (*endptr != '\0') {
        fprintf(stderr, "Error: Non-integer exit code\n");
        return 2;
    }

    exit(exit_code);
}

int exec_extern_executable(const char *name, const int argc, char **argv) {
	char *error_label = malloc(sizeof("Error: ") + sizeof(name));
	char **new_argv = realloc(argv,sizeof(char *) * (argc + 1));

	if (error_label == NULL || new_argv == NULL) {
		fprintf(stderr, "Error: Unable to allocate memory\n");
		free(new_argv);
		return 1;
	}

	sprintf(error_label, "Error: %s", name);

	new_argv[argc] = NULL;
	const pid_t pid = fork();

	if (pid == 0) {
		execv(name, (char * const *)new_argv);
		perror(error_label);
		free(error_label);
		free(new_argv);
		exit(1);
	}

	if (pid < 1) {
		fprintf(stderr, "Error: Unable to create subprocess\n");
		free(error_label);
		return 1;
	}

	wait(NULL);

	free(error_label);
	return 0;
}
