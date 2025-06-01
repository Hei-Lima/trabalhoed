// Lib that implements all of the UI (User Interface) functions for the main program.

#ifndef _UILIB_H
#define _UILIB_H

// Prints an ANSI escape sequence to clear the screen (like the Unix command clear).
void ui_cls();

// Function to print the main menu.
void ui_print_main_menu();

// Function to print the consulta menu.
void ui_print_consulta();

// Implements the getch func on Linux (adapted from https://gist.github.com/ninovsnino/f910701ea912f03b73a1d0895d213b0e)
char ui_getchar();

// Append a char to a string,
void ui_append_char(char c, char* string, int size, int max_size);

// Print the bottom of the consulta (like the string).
void ui_print_consulta_bottom(char* string);

// Print the top of the consulta.
void ui_print_consulta_top();

// Print the Healthsys logo :)
void ui_print_logo();

// Print the wrong option warning.
void ui_print_option_warning(char choice);

#endif 