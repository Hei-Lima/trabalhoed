// Lib that implements all of the database-related functions of the program.

#ifndef _DB_H
#define _DB_H


// This struct implements the Paciente type.
typedef struct paciente Paciente;

// This struct implements the BDPaciente type.
typedef struct bdpaciente BDPaciente;

#include "trie.h"

// Initialize a patient and return its pointer.
Paciente* db_create_paciente(int id, char* CPF, char* nome, int idade, char* data_cadastro);

// Initialize a BDPaciente and return its pointer.
BDPaciente* db_create_db();

// Populate the database from a CSV file.
void db_populate_db_from_csv(char* path, BDPaciente* db);

// Print a patient by ID.
void db_print_patient(BDPaciente* db, int id);

/* 
    * Search and print all entries matching the prefix.
    * @params: int filter - 1 for Nome, 2 for CPF  
*/
void db_search_by_prefix(BDPaciente* db, char* prefix, int filter);

// Print all patients with pagination.
void db_print_all_patients(BDPaciente* db, int page);

// Destroy the database and dealocate everything.
void db_destroy_db(BDPaciente* db);

#endif