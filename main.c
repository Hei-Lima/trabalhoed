#include "db.h"
#include "uilib.h"
#include <stdio.h>

/*
 * Consulta function
 * @param option: 1 = Nome, 2 = CPF
 */
void consulta(BDPaciente* db, int option) {
    int current_size = 0;
    int max_size = 121;
    
    char string[max_size + 1];
    char lastchar;
    string[0] = '\0';

    do {
        // UI
        ui_print_consulta_top();
        db_search_by_prefix(db, string, option);
        ui_print_consulta_bottom(string);

        // Input
        lastchar = ui_getchar();
        if (lastchar == '_') {
            current_size = 0;
            string[0] = '\0';
        } else {
            ui_append_char(lastchar, string, current_size, max_size);
            current_size++;
        }
        ui_cls();
    } while (lastchar != '-');
}

// Handle the consulta option.
void consultar_paciente(BDPaciente* db) {
    ui_print_consulta();
    
    char choice = ui_getchar();

    // Get option numerical value.
    int option = choice - '0';

    ui_cls();

    if (option == 3) {
        return;
    }

    consulta(db, option);
}

// Handle the print all patients pagination. 
void print_lista_pacientes(BDPaciente* db) {
    int page = 0;

    // Any char that is not q;
    char choice = ' ';

    do {
        ui_cls();
        // UI
        ui_print_consulta_top();
        db_print_all_patients(db, page);
        printf("Pressione '+' para avançar e '-' para retroceder. Para sair pressione 'Q'.");

        // Input
        choice = ui_getchar();
        if (choice == '+') {
            page++;
        }
        else if (choice == '-') {
            page--;
        }
    } while (choice != 'Q');
}

// Handle Main Menu Choices and return the option.
char handle_main_menu() {

    printf("HEALTHSYS\n");
    printf("1 - Consultar Paciente\n");
    // printf("2 - Atualizar Paciente\n");
    // printf("3 - Remover Paciente\n");
    // printf("4 - Inserir Paciente\n");
    printf("5 - Imprimir Lista de Pacientes\n");
    printf("Q - Sair\n");

    char choice = ui_getchar();

    return choice;
}

int main() {
    BDPaciente* db = db_create_db();
    db_populate_db_from_csv("pacientes6000.csv", db);
    
    ui_print_logo();

    // Initialize choice to a random char that isn't q. 
    char choice = ' ';

    // While choice != q, continue in the main menu.
    while (choice != 'Q') {
        // ui_cls clears the screen.
        ui_cls();
        choice = handle_main_menu();
        ui_cls();

        switch (choice) {
        case '1':
            consultar_paciente(db);
            break;
        case '5':    
            print_lista_pacientes(db);
            break;
        case 'q':
            break;
        case 'Q':
            break;
        default:
            ui_print_option_warning(choice);
            break;
        }
    }

    db_destroy_db(db);

    return 0;
}