#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "db.h"
#include "uilib.h"
#define CSV_PATH "bd_paciente.csv"

void consultar_paciente(BDPaciente* db);

// Função auxiliar para ler uma linha do stdin
static void read_line(char* buffer, int size) {
    if (fgets(buffer, size, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
    }
}

/*
 * Consulta function
 * @param option: 1 = Nome, 2 = CPF
 */
void consulta(BDPaciente* db, int option) {
    char string[122];
    
    printf("Digite o %s para buscar (ou 'sair' para voltar): ", 
           option == 1 ? "nome" : "CPF");
    
    if (fgets(string, sizeof(string), stdin) != NULL) {
        // Remove newline if present
        string[strcspn(string, "\n")] = '\0';
        
        if (strcmp(string, "sair") == 0) {
            return;
        }
        
        ui_cls();
        ui_print_consulta_top();
        db_search_by_prefix(db, string, option);
        
        printf("\nPressione Enter para continuar...");
        getchar();
    }
}

// Function to insert patient.
void inserir_paciente(BDPaciente* db) {
    char cpf[16], nome[122], data[11], idade_str[8], confirm;
    int idade;
    int novo_id = db_get_next_id(db);
    printf("Digite o CPF (XXX.XXX.XXX-XX): ");
    read_line(cpf, sizeof(cpf));
    printf("Digite o nome: ");
    read_line(nome, sizeof(nome));
    printf("Digite a idade: ");
    read_line(idade_str, sizeof(idade_str));
    sscanf(idade_str, "%d", &idade);
    printf("Digite a data de cadastro (AAAA-MM-DD): ");
    read_line(data, sizeof(data));

    // Clear buffer because it was bugging
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    printf("\nConfirma a inserção do registro abaixo? (S/N):\n ");
    printf("%-5s %-15s %-30s %-10s %-15s\n", "ID", "CPF", "Nome", "Idade", "Data Cadastro");
    printf("%-5d %-15s %-30s %-10d %-15s\n\n", novo_id, cpf, nome, idade, data);
    fflush(stdout);
    confirm = getchar(); getchar();
    if (confirm == 'S' || confirm == 's') {
        db_create_paciente(db, novo_id, cpf, nome, idade, data);
        db_save_to_csv(db, CSV_PATH);
        printf("Registro inserido com sucesso!\n");
    } else {
        printf("Operação cancelada.\n");
    }
    printf("Pressione Enter para continuar..."); getchar();
}

// Function to remove a patient.
void remover_paciente(BDPaciente* db) {
    consultar_paciente(db);
    printf("\nDigite o ID do registro a ser removido: ");
    int id; scanf("%d", &id); getchar();
    Paciente* p = db_get_paciente_by_id(db, id);
    if (!p) { printf("ID não encontrado!\n"); printf("Pressione Enter..."); getchar(); return; }
    printf("Tem certeza de que deseja excluir o registro abaixo? (S/N)\n");
    pc_print_paciente(p);
    printf("\n");
    char confirm = getchar(); getchar();
    if (confirm == 'S' || confirm == 's') {
        db_remove_paciente(db, id);
        db_save_to_csv(db, CSV_PATH);
        printf("Registro removido com sucesso!\n");
    } else {
        printf("Operação cancelada.\n");
    }
    printf("Pressione Enter para continuar..."); getchar();
}

// Function to update a patient.
void atualizar_paciente(BDPaciente* db) {
    consultar_paciente(db);
    printf("\nDigite o ID do registro a ser atualizado: ");
    int id; scanf("%d", &id); getchar();
    Paciente* p = db_get_paciente_by_id(db, id);
    if (!p) { printf("ID não encontrado!\n"); printf("Pressione Enter..."); getchar(); return; }
    char cpf[16], nome[122], data[11], idade_str[8], confirm;

    printf("Digite o novo CPF (ou '-' para manter): ");
    read_line(cpf, sizeof(cpf));
    printf("Digite o novo nome (ou '-' para manter): ");
    read_line(nome, sizeof(nome));
    printf("Digite a nova idade (ou '-' para manter): ");
    read_line(idade_str, sizeof(idade_str));
    printf("Digite a nova data de cadastro (ou '-' para manter): ");
    read_line(data, sizeof(data));

    int idade = -1;
    if (strcmp(idade_str, "-") != 0) idade = atoi(idade_str);
    printf("\nConfirma os novos valores para o registro abaixo? (S/N)\n");
    printf("%-5s %-15s %-30s %-10s %-15s\n", "ID", "CPF", "Nome", "Idade", "Data Cadastro");
    printf("%-5d %-15s %-30s %-10d %-15s\n\n", id, 
        strcmp(cpf,"-")==0?pc_get_cpf(p):cpf, 
        strcmp(nome,"-")==0?pc_get_nome(p):nome, 
        strcmp(idade_str,"-")==0?pc_get_idade(p):idade, 
        strcmp(data,"-")==0?pc_get_data_cadastro(p):data);
    int c;
    if (strcmp(data, "-") != 0) {
        // Clear buffer because it was bugging
        while ((c = getchar()) != '\n' && c != EOF);
    }
    confirm = getchar(); getchar();
    if (confirm == 'S' || confirm == 's') {
        db_update_paciente(db, id, strcmp(cpf,"-")==0?NULL:cpf, strcmp(nome,"-")==0?NULL:nome, idade, strcmp(data,"-")==0?NULL:data);
        db_save_to_csv(db, CSV_PATH);
        printf("Registro atualizado com sucesso!\n");
    } else {
        printf("Operação cancelada.\n");
    }
    printf("Pressione Enter para continuar..."); getchar();
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
    int total = db_get_next_id(db) - 1;
    int total_pages = (total + 10 - 1) / PAGE_SIZE;

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
            if (page >= total_pages) page = total_pages - 1;
        }
        else if (choice == '-') {
            page--;
            if (page < 0) page = 0;
        }
    } while (choice != 'Q' && choice != 'q');
}

// Handle Main Menu Choices and return the option.
char handle_main_menu_choices() {
    printf("HEALTHSYS\n");
    printf("1 - Consultar Paciente\n");
    printf("2 - Atualizar Paciente\n");
    printf("3 - Remover Paciente\n");
    printf("4 - Inserir Paciente\n");
    printf("5 - Imprimir Lista de Pacientes\n");
    printf("Q - Sair\n");
    char choice = ui_getchar();
    return choice;
}

// Handle main menu logic.
void handle_main_menu(BDPaciente* db) {
        // Initialize choice to a random char that isn't q. 
        char choice = ' ';

        // While choice != q, continue in the main menu.
        while (choice != 'Q' && choice != 'q') {
            // ui_cls clears the screen.
            ui_cls();
            choice = handle_main_menu_choices();
            ui_cls();
    
            switch (choice) {
            case '1':
                consultar_paciente(db);
                break;
            case '2':
                atualizar_paciente(db);
                break;
            case '3':
                remover_paciente(db);
                break;
            case '4':
                inserir_paciente(db);
                break;
            case '5':    
                print_lista_pacientes(db);
                break;
            case 'q':
            case 'Q':
                break;
            default:
                ui_print_option_warning(choice);
                break;
        }
    }
}

int main() {
    // Initialize DB.
    BDPaciente* db = db_create_db();
    db_create_list_from_csv(CSV_PATH, db);
    
    // Print Healthsys logo.
    ui_print_logo();

    // Handle all main menu logic and choices.
    handle_main_menu(db);

    // Free the DB.
    db_destroy_db(db);

    return 0;
}