#include <stddef.h>
#include <string.h>

#include "meta_data.h"


const char product_name[12] = "shell";
const char *version = "1.5";
const char *author = "foxypiratecove37350";

const char *welcome_messages[] = {
	"\033[94m┌─────────────────────────────────────────────────────────┐\033[0m\n"
	"\033[94m│\033[0m Welcome in \033[38;2;255;255;0m%-12s\033[0m                                 \033[94m│\033[0m\n"
    "\033[94m│\033[0m You can type 'help' to see the available commands.      \033[94m│\033[0m\n"
    "\033[94m└─────────────────────────────────────────────────────────┘\033[0m\n",

    "\033[94m\"\033[0m\033[0m\033[38;2;255;255;0m%s\033[0m ain't \033[0m\033[38;2;255;255;0m%sing\033[0m!\033[94m\"\033[0m "
	"\033[91m(don't worry, that's just a welcome message :)\033[0m\n",

    "You don't like \033[38;2;255;0;0;1mc\033[0m\033[38;2;208;222;33;1mo\033[0m\033[38;2;63;218;216;1ml\033[0m"
	"\033[38;2;28;127;238;1mo\033[0m\033[38;2;186;12;248;1mr\033[0m\033[38;2;255;0;0;1ms\033[0m :( ? "
	"Try starting \033[38;2;255;255;0m%s\033[0m with the '--no-color' flag!\n",

	"You want to see something \033[95mmagic\033[0m? Try the \033[92mescape codes\033[0m!\n"
	"echo \"'\\\\', '\\a', '\\b', '\\f', '\\n', '\\r', '\\t', '\\v', '\\e', '\\?'\"\n",

    "\033[38;2;255;255;0m%s\033[0m is good... enough!\n",

    "You prefer \033[94mC++\033[0m? Try \033[38;2;255;255;0m%s++\033[0m! Same as \033[38;2;255;255;0m%s\033[0m, "
	"but in \033[94mC++\033[0m.\n",

	"You want \033[94mWindows\033[0m on \033[32mLinux\033[0m? As simple as \033[38;2;255;255;0m%s\033[0m is, just "
	"install \033[32mL\033[0mS\033[94mW\033[0m!\n",

	"\033[38;2;255;255;0m%s\033[0m... is... BACK!\n",

	"Don't like \033[94mGNU Binutils\033[0m and find them too heavy and bloated for \033[32mLinux\033[0m? "
	"Try \033[38;2;255;255;0mBinutils++\033[0m!\n"
};
const int welcome_messages_num = sizeof(welcome_messages) / sizeof(char *);


const char *changelogs[] = {
	"v1.5:\n\n"
	"Added:\n"
	"- The `changelog` command\n"
	"- Handling of external executables\n"
	"- The \"shell... is... BACK!\" welcome message\n"
	"- The \"Don't like GNU Binutils and find them too heavy and bloated for Linux? "
	"Try Binutils++!\" welcome message\n\n"
	"Removed:\n"
	"- Windows support (too heavy codebase)\n\n"
	"Changed:\n"
	"- Welcome messages now mention \"welcome messages\" instead of \"splash texts\"\n"
	"- Welcome messages now uses \":(\" instead of \":-(\" (reference to Windows 10's BSoD)\n\n",

	"v1.0:\n\n"
	"Added:\n"
	"- The core commands (`help`, `info`, `pwd`, `welcome`, `echo`, `uname`, `clear`, `exit`)\n"
	"- The welcome messages\n"
	"- The argument parsing\n"
	"- The core components\n\n",

	NULL
};
