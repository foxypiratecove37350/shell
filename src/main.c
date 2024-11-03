#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "args_parsing.h"
#include "commands.h"
#include "utils.h"


int main(const int argc, char **argv) {
	if (argc > 1 && strcmp(argv[1], "--no-color") == 0) {
		NO_COLOR = 1;
	}

	display_welcome_message();

	while (1) {
		char shell_status_str[] = "$";
		
		color_print("\033[94m%s\033[0m\033[38;2;255;255;0m%s\033[0m ", getcwd(NULL, 0), shell_status_str);

		const char *input = read_input();

		char **parsed_input = NULL;
		const int cmd_argc = parse_args(input, &parsed_input);
		
		if (parsed_input == NULL) {
			fprintf(stderr, "Error: Error while argument parsing\n");
			continue;
		}

		if (parsed_input == (void*) -1) {
			continue;
		}

		const Command *cmd = getCommand(&command_list, parsed_input[0]);

		if (cmd == NULL) {
			exec_extern_executable(parsed_input[0], cmd_argc, parsed_input);
		} else if (cmd == (void*) -1) {
			continue;
		} else {
			cmd->execute(cmd, cmd_argc, parsed_input);
		}

		for (int i = 0; i <= cmd_argc; i++) {
        	free(parsed_input[i]);
		}

		free(parsed_input);
	}
}
