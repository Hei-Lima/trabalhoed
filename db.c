// Lib that implements all of the database-related functions of the program.
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "db.h"
#include "paciente.h"

// Max number of entries in the print all patients function.
#define PAGE_SIZE 10

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