// Lib that implements all of the database-related functions of the program.

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "trie.h"
#include "db.h"

// Max number of entries in the print all patients function.
#define PAGE_SIZE 10

// Implements the Paciente type.
typedef struct paciente
{
    int id;
    char CPF[16];
    // Space for 121 characters, which is the number of characters in the full name of Pedro II.
    char nome[122];
    int idade;
    // AAAA-MM-DD format.
    char data_cadastro[11];
} Paciente;

// Implements the BDPaciente type.
typedef struct bdpaciente
{
    int entry_quant;
    Paciente* array_paciente;
    Trie* cpf_trie;
    Trie* nome_trie; 
} BDPaciente;

// Initialize a patient and return its pointer.
Paciente* db_create_paciente(int id, char* CPF, char* nome, int idade, char* data_cadastro) {
    Paciente* paciente = malloc(sizeof(Paciente));
    paciente->id = id;
    paciente->idade = idade;
    strcpy(paciente->CPF, CPF);
    strcpy(paciente->nome, nome);
    strcpy(paciente->data_cadastro, data_cadastro);

    return paciente;
}

// Initialize a BDPacient and return its pointer.
BDPaciente* db_create_db() {
    BDPaciente* bdpaciente = malloc(sizeof(BDPaciente));
    return bdpaciente;
}


// Initialize the patient array from a CSVFile in the BDPatient, unpopulated.
void create_patient_array_from_csv(char* path, BDPaciente* db) {
    FILE* csv = fopen(path, "r");

    if (csv == NULL) {
        printf("ERROR");
        return;
    }

    // Find the number of patients.
    // Você postou esse código no github e eu estou usando... haha
    int line_count = 0;
    char line[200]; // sequence of non-blank characters

    while (fgets(line, 200, csv) != NULL) // returns line or NULL (if reach the end of file)
    {
        line_count++;
    }

    db->entry_quant = line_count;
    db->array_paciente = malloc(sizeof(Paciente) * line_count);

    fclose(csv);
}

// This cretes the CPF and Name tries in the BDPaciente.
void create_patient_tries(BDPaciente* db) {
    db->cpf_trie = trie_create();
    db->nome_trie = trie_create();
}

// Insert all patients on the tries and on the array.
void insert_patients_from_csv(char* path, BDPaciente* db) {
    FILE* csv = fopen(path, "r");

    if (csv == NULL) {
        printf("ERROR");
        return;
    }

    char line[200]; 
    int index = 0;

    while (fgets(line, sizeof(line), csv) != NULL) {
        int id, idade;
        char CPF[16], nome[122], data_cadastro[11];

        if (sscanf(line, "%d,%15[^,],%121[^,],%d,%10s", &id, CPF, nome, &idade, data_cadastro) == 5) {
            Paciente paciente = {id, "", "", idade, ""};
            strncpy(paciente.CPF, CPF, sizeof(paciente.CPF) - 1);
            strncpy(paciente.nome, nome, sizeof(paciente.nome) - 1);
            strncpy(paciente.data_cadastro, data_cadastro, sizeof(paciente.data_cadastro) - 1);

            db->array_paciente[index++] = paciente;

            trie_insert(db->cpf_trie, CPF, id);
            trie_insert(db->nome_trie, nome, id);
        } else {
            printf("WARNING: Linha inválida no CSV: %s", line);
        }
    }

    fclose(csv);
}

// Supondo que o array seja um array de inteiros e você saiba o tamanho dele.
void print_array(int* array, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n"); // Para adicionar uma nova linha após imprimir o array.
}

// Populate the DB with a CSV file.
void db_populate_db_from_csv(char* path, BDPaciente* db) {
    create_patient_array_from_csv(path, db);
    create_patient_tries(db);
    insert_patients_from_csv(path, db);
}

// Print patient by ID.
void db_print_patient(BDPaciente* db, int id) {
    Paciente* paciente = &db->array_paciente[id];
    printf("%-5d %-15s %-30s %-10d %-15s\n", 
           id + 1, 
           paciente->CPF, 
           paciente->nome, 
           paciente->idade, 
           paciente->data_cadastro);
}

/* 
    * Search and print all entries matching the prefix.
    * @params: int filter - 1 for Nome, 2 for CPF  
*/
void db_search_by_prefix(BDPaciente* db, char* prefix, int filter) {
    // Caso Nome
    if (filter == 1) {
        trie_search(db->nome_trie, prefix, db);
    }
    // Caso CPF
    if (filter == 2) {
        trie_search(db->cpf_trie, prefix, db);
    } 
}

// Print all patients with pagination.
void db_print_all_patients(BDPaciente* db, int page) {
    int entry_quant = db->entry_quant;

    // Check for pagination boundaries.
    page = page < 0 ? 0 : page; 
    int total_pages = (entry_quant + PAGE_SIZE - 1) / PAGE_SIZE; 
    page = page >= total_pages ? total_pages - 1 : page;

    int start = page * PAGE_SIZE;
    int end = start + PAGE_SIZE;

    for (int i = start; i < entry_quant && i < end; i++) {
        db_print_patient(db, i);
    }

    printf("Página %d de %d\n", page + 1, total_pages);
}

void db_destroy_db(BDPaciente* db) {
    trie_destroy(db->cpf_trie);
    trie_destroy(db->nome_trie);
    free(db->array_paciente);
    free(db);
}