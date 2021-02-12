#ifndef DB_DELETION_H
#define DB_DELETION_H

#pragma pack(1)
#include "filesHandler.h"
#include "structures.h"

void delM();

void delS();

void writeGroupStudentsInactive(trashZone* trashZone, const Group* delGroup);

#endif // DB_DELETION_H