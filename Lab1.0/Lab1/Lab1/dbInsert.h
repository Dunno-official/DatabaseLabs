#ifndef DATABASES_DBINSERT_H
#define DATABASES_DBINSERT_H

#include "dbFilesHandler.h"
#include "dbStructures.h"
#include <stdbool.h>

void insertM();

void insertNewShopRecord(int id);

shop getNewShopRecord();

void insertNewShopIndex();

void insertS();

employee getNewEmployeeRecord(const shop *mShop);

void insertNewEmployeeRecord(shop *mShop, int id);

void insertNewEmployeeIndex();

bool validateRecordsAmount(dbFiles fileType);

keyIndex getNewDataIndex(dbFiles fileType);

#endif // DATABASES_DBINSERT_H