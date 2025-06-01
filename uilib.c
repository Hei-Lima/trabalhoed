// Lib that implements all of the UI (User Interface) functions for the main program.

#include "uilib.h"
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

// Clears the screen (on Unix and POSIX compliant terminals). 
void ui_cls() {
    printf("\e[1;1H\e[2J");
}

// Function to print the main menu.
void ui_print_main_menu() {
    printf("HEALTHSYS\n");
    printf("1 - Consultar Paciente\n");
    // printf("2 - Atualizar Paciente\n");
    // printf("3 - Remover Paciente\n");
    // printf("4 - Inserir Paciente\n");
    printf("5 - Imprimir Lista de Pacientes\n");
    printf("Q - Sair\n");
}

// Function to print the consulta menu.
void ui_print_consulta() {
    printf("Escolha o modo de consulta: \n");
    printf("1 - Por nome\n");
    printf("2 - Por CPF\n");
    printf("3 - Retornar ao menu principal\n");
}

void ui_paginate_pacients() {
    
}

// Implements the getch func on Linux (adapted from https://gist.github.com/ninovsnino/f910701ea912f03b73a1d0895d213b0e)
char ui_getchar() {
    struct termios oldt, newt;
    char ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch;
}

// Append a char to a string,
void ui_append_char(char c, char* string, int size, int max_size) {
    if (size >= max_size) {
        printf("MAXIMO DE CARACTERES EXCEDIDO.\n");
        return;
    }
    
    string[size] = c;
    string[size + 1] = '\0';
}

// Print the bottom of the consulta (like the string).
void ui_print_consulta_bottom(char* string) {
    printf("\n%-30s \t%s", "Pressione '-' para sair da busca ou '_' para limpar campo", string);
}

// Print the top of the consulta.
void ui_print_consulta_top() {
    printf("%-5s %-15s %-30s %-10s %-15s\n", "ID", "CPF", "Nome", "Idade", "Data Cadastro");
}

// Print the Healthsys logo :)
void ui_print_logo() {
    ui_cls();
    printf("  _    _            _ _   _      _____           \n");
    usleep(100000);
    printf(" | |  | |          | | | | |    / ____|          \n");
    usleep(100000);
    printf(" | |__| | ___  __ _| | |_| |__ | (___  _   _ ___ \n");
    usleep(100000);
    printf(" |  __  |/ _ \\/ _` | | __| '_ \\ \\___ \\| | | / __|\n");
    usleep(100000);
    printf(" | |  | |  __/ (_| | | |_| | | |____) | |_| \\__ \\\n");
    usleep(100000);
    printf(" |_|  |_|\\___\\__,_|_|\\__|_| |_|_____/ \\__, |___/\n");
    usleep(100000);
    printf("                                        __/ |    \n");
    usleep(100000);
    printf("                                       |___/     \n");
    sleep(1);
}

// Print the wrong option warning.
void ui_print_option_warning(char choice) {
    ui_cls();
    printf("A opção %c não existe ou não foi implementada.\nPressione qualquer tecla para voltar.", choice);
    ui_getchar();
}