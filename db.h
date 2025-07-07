// Lib that implements all of the database-related functions of the program.

#ifndef _DB_H
#define _DB_H

// Externing PAGE_SIZE to be used in the pagination functions.
extern const int PAGE_SIZE;

// This struct implements the Paciente type.
typedef struct paciente Paciente;

// This struct implements the BDPaciente type.
typedef struct bdpaciente BDPaciente;

#include "list.h"

// Initialize a patient and return its pointer.
Paciente* db_create_paciente(BDPaciente* db, int id, char* CPF, char* nome, int idade, char* data_cadastro);

// Initialize a BDPaciente and return its pointer.
BDPaciente* db_create_db();

// Populate the database from a CSV file.
void db_create_list_from_csv(char* path, BDPaciente* db);

// Print a patient by ID.
void db_print_patient(BDPaciente* db, int id);

/* 
    * Search and print all entries matching the prefix.
    * @params: int filter - 1 for Nome, 2 for CPF  
*/
void db_search_by_prefix(BDPaciente* db, char* prefix, int filter);

// Print all patients with pagination.
void db_print_all_patients(BDPaciente* db, int page);

// Remove a patient by ID.
void db_remove_paciente(BDPaciente* db, int id);
// Update a patient by ID. Returns 1 if updated, 0 if not found.
int db_update_paciente(BDPaciente* db, int id, char* new_cpf, char* new_nome, int new_idade, char* new_data_cadastro);
// Save the database to a CSV file.
void db_save_to_csv(BDPaciente* db, char* path);

// Destroy the database and dealocate everything.
void db_destroy_db(BDPaciente* db);

// Retorna o próximo ID disponível para paciente
int db_get_next_id(BDPaciente* db);
// Busca paciente por ID
Paciente* db_get_paciente_by_id(BDPaciente* db, int id);

#endif