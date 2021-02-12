#ifndef DB_READING_H
#define DB_READING_H

#include "filesHandler.h"
#include "structures.h"

Group getM();

Student getS();

void getAll();

void countAll();

int getStudentsInGroup(const Group* mGroup);

int getUserKey(dbFiles fileType);

void readIndixes(KeyIndex* indixes, int size, dbFiles fileType);

unsigned long getAddressByKey(int key, dbFiles fileType);

Group getGroupByKey(int key);

Student getStudentByKey(int userKey);

void formatGroupOutput(const Group* outGroup);

void formatStudentOutput(const Student* outStudent);

int getRecordsNum(dbFiles fileType);

trashZone getTrashZoneData();

int getGroupTrashKey();

int getStudentTrashKey();

#endif // DB_READING_H 