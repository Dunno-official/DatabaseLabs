#ifndef DATABASES_DBREAD_H
#define DATABASES_DBREAD_H

#include "dbFilesHandler.h"
#include "dbStructures.h"

shop getM();

employee getS();

void getAll();

void countAll();

int getEmployeesInShop(const shop *mShop);

int getUserKey(dbFiles fileType);

void readIndices(keyIndex *indices, int size, dbFiles fileType);

unsigned long getAddressByKey(int key, dbFiles fileType);

shop getShopByKey(int key);

employee getEmployeeByKey(int userKey);

void formatShopOutput(const shop *outShop);

void formatEmployeeOutput(const employee *outEmployee);

int getRecordsNum(dbFiles fileType);

trashZone getTrashZoneData();

int getShopTrashKey();

int getEmployeeTrashKey();

#endif // DATABASES_DBREAD_H