#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "paciente.h"

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

// Initialize a patient and return its pointer.
Paciente* pc_create_paciente(int id, char* CPF, char* nome, int idade, char* data_cadastro) {
    Paciente* paciente = malloc(sizeof(Paciente));
    paciente->id = id;
    paciente->idade = idade;
    strcpy(paciente->CPF, CPF);
    strcpy(paciente->nome, nome);
    strcpy(paciente->data_cadastro, data_cadastro);

    return paciente;
}

// Setters
void pc_set_id(Paciente* paciente, int id) {
    paciente->id = id;
}

void pc_set_cpf(Paciente* paciente, char* CPF) {
    strcpy(paciente->CPF, CPF);
}

void pc_set_nome(Paciente* paciente, char* nome) {
    strcpy(paciente->nome, nome);
}

void pc_set_idade(Paciente* paciente, int idade) {
    paciente->idade = idade;
}

void pc_set_data_cadastro(Paciente* paciente, char* data_cadastro) {
    strcpy(paciente->data_cadastro, data_cadastro);
}

// Getters
int pc_get_id(Paciente* paciente) {
    return paciente->id;
}

char* pc_get_cpf(Paciente* paciente) {
    return paciente->CPF;
}

char* pc_get_nome(Paciente* paciente) {
    return paciente->nome;
}

int pc_get_idade(Paciente* paciente) {
    return paciente->idade;
}

char* pc_get_data_cadastro(Paciente* paciente) {
    return paciente->data_cadastro;
}

void pc_print_paciente(Paciente* paciente) {
    if (paciente == NULL) return;
    printf("%-5d %-15s %-30s %-10d %-15s\n", 
           paciente->id, 
           paciente->CPF, 
           paciente->nome, 
           paciente->idade, 
           paciente->data_cadastro);
}

void pc_destroy_paciente(Paciente* paciente) {
    free(paciente);
}