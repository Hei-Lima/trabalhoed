// Lib that implements all of the patient management functions.

#ifndef _PACIENTE_H
#define _PACIENTE_H

typedef struct paciente Paciente;

// Create a patient and return its pointer.
Paciente* pc_create_paciente(int id, char* CPF, char* nome, int idade, char* data_cadastro);

// Setters
// Set the patient id.
void pc_set_id(Paciente* paciente, int id);

// Set the patient CPF.
void pc_set_cpf(Paciente* paciente, char* CPF);

// Set the patient name.
void pc_set_nome(Paciente* paciente, char* nome);

// Set the patient age.
void pc_set_idade(Paciente* paciente, int idade);

// Set the patient registration date.
void pc_set_data_cadastro(Paciente* paciente, char* data_cadastro);

// Getters
// Get the patient id.
int pc_get_id(Paciente* paciente);

// Get the patient name.
char* pc_get_nome(Paciente* paciente);

// Get the patient CPF.
char* pc_get_cpf(Paciente* paciente);

// Get the patient age.
int pc_get_idade(Paciente* paciente);

// Get the patient registration date.
char* pc_get_data_cadastro(Paciente* paciente);

// Print patient information.
void pc_print_paciente(Paciente* paciente);

// Free memory allocated for a patient.
void pc_destroy_paciente(Paciente* paciente);

#endif