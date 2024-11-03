#ifndef UTILS_H
#define UTILS_H

char *read_input();
int color_print(const char *format, ...);
void display_welcome_message(void);
const char *find_changelog(const char *version);

extern int NO_COLOR;


#endif
