// Lib that implements all of the database-related functions of the program.
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "db.h"
#include "paciente.h"

// Max number of entries in the print all patients function.
const int PAGE_SIZE = 10;

// Implements the BDPaciente type.
typedef struct bdpaciente
{
    List* lista_pacientes; 
} BDPaciente;

// Initialize a patient and return its pointer.
Paciente* db_create_paciente(BDPaciente* db, int id, char* CPF, char* nome, int idade, char* data_cadastro) {
    Paciente* paciente = pc_create_paciente(id, CPF, nome, idade, data_cadastro);
    ll_insert_node(db->lista_pacientes, paciente);
    return paciente;
}

// Initialize a BDPacient and return its pointer.
BDPaciente* db_create_db() {
    BDPaciente* bdpaciente = malloc(sizeof(BDPaciente));
    bdpaciente->lista_pacientes = ll_create_list();
    return bdpaciente;
}

// Initialize the patient list from a CSVFile in the BDPatient, and populate with data.
void db_create_list_from_csv(char* path, BDPaciente* db) {
    FILE* csv = fopen(path, "r");

    if (csv == NULL) {
        printf("ERROR");
        return;
    }

    char line[200]; 

    while (fgets(line, sizeof(line), csv) != NULL) {
        int id, idade;
        char CPF[16], nome[122], data_cadastro[11];

        if (sscanf(line, "%d,%15[^,],%121[^,],%d,%10s", &id, CPF, nome, &idade, data_cadastro) == 5) {
            Paciente* paciente = pc_create_paciente(id, CPF, nome, idade, data_cadastro);
            ll_insert_node(db->lista_pacientes, paciente);
        } else {
            printf("WARNING: Linha inválida no CSV: %s", line);
        }
    }

    fclose(csv);
}

// Print patient by ID.
void db_print_patient(BDPaciente* db, int id) {
    Paciente* paciente = ll_search_node(db->lista_pacientes, id);
    if (paciente != NULL) {
        pc_print_paciente(paciente);
    } else {
        printf("Paciente com ID %d não encontrado.\n", id);
    }
}

// Print all patients with pagination.
void db_print_all_patients(BDPaciente* db, int page) {
    int entry_quant = ll_get_size(db->lista_pacientes);

    // Check for pagination boundaries.
    page = page < 0 ? 0 : page; 
    int total_pages = (entry_quant + PAGE_SIZE - 1) / PAGE_SIZE; 
    page = page >= total_pages ? total_pages - 1 : page;

    int start = page * PAGE_SIZE;
    int end = start + PAGE_SIZE;

    ll_print_page(db->lista_pacientes, start, end);
    
    printf("Página %d de %d\n", page + 1, total_pages);
}

void db_destroy_db(BDPaciente* db) {
    ll_destroy_list(db->lista_pacientes);
    free(db);
}

void db_search_by_prefix(BDPaciente* db, char* prefix, int filter) {
    ll_print_by_prefix(db->lista_pacientes, prefix, filter);
}

// Remove a patient by ID.
void db_remove_paciente(BDPaciente* db, int id) {
    ll_remove_node(db->lista_pacientes, id);
}

// Update a patient by ID. Returns 1 if updated, 0 if not found.
int db_update_paciente(BDPaciente* db, int id, char* new_cpf, char* new_nome, int new_idade, char* new_data_cadastro) {
    Paciente* paciente = ll_search_node(db->lista_pacientes, id);
    if (!paciente) return 0;
    if (new_cpf) pc_set_cpf(paciente, new_cpf);
    if (new_nome) pc_set_nome(paciente, new_nome);
    if (new_idade >= 0) pc_set_idade(paciente, new_idade);
    if (new_data_cadastro) pc_set_data_cadastro(paciente, new_data_cadastro);
    return 1;
}

// Função auxiliar para salvar um paciente no CSV
static void save_paciente_csv(Paciente* p, void* file_ptr) {
    FILE* csv = (FILE*)file_ptr;
    fprintf(csv, "%d,%s,%s,%d,%s\n", pc_get_id(p), pc_get_cpf(p), pc_get_nome(p), pc_get_idade(p), pc_get_data_cadastro(p));
}

// Save the database to a CSV file.
void db_save_to_csv(BDPaciente* db, char* path) {
    FILE* csv = fopen(path, "w");
    if (!csv) {
        printf("Erro ao salvar CSV!\n");
        return;
    }
    ll_for_each(db->lista_pacientes, save_paciente_csv, csv);
    fclose(csv);
}

// Retorna o próximo ID disponível para paciente
int db_get_next_id(BDPaciente* db) {
    return ll_get_max_id(db->lista_pacientes) + 1;
}

// Busca paciente por ID
Paciente* db_get_paciente_by_id(BDPaciente* db, int id) {
    return ll_search_node(db->lista_pacientes, id);
}