// Test for memory leaks.

#include "db.h"
#include "uilib.h"
#include <stdio.h>

int main() {

    // Create and destroy DB.
    BDPaciente* db = db_create_db();
    db_populate_db_from_csv("pacientes6000.csv", db);
    db_print_all_patients(db, 0);

    db_destroy_db(db);
}