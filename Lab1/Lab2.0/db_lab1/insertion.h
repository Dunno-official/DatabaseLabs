#ifndef DB_INSERTION_H
#define DB_INSERTION_H

#include "filesHandler.h"
#include "structures.h"
#include <stdbool.h>

void insertM();

void insertNewGroupRecord(int id);

Group getNewGroupRecord();

void insertNewGroupIndex();

void insertS();

Student getNewStudentRecord(const Group* mGroup);

void insertNewStudentRecord(Group* mGroup, int id);

void insertNewStudentIndex();

bool validateRecordsAmount(dbFiles fileType);

KeyIndex getNewDataIndex(dbFiles fileType);

#endif // DB_INSERTION_H