#include <stdlib.h>
#pragma pack(1)
#include "dbInsert.h"
#include "dbRead.h"
#include "dbUpdate.h"

void insertM() {
  int id = -1;
  if (!validateRecordsAmount(shopsIndices)) {
    id = getShopTrashKey();
    if (id == -1) {
      fprintf(stderr, "\nShop.fl cannot store more than %d records!\n",
              MAX_RECORDS_AMOUNT);
      return;
    }
  }
  insertNewShopRecord(id);
  insertNewShopIndex();
}

void insertNewShopRecord(int id) {
  shop newShop = getNewShopRecord();
  if (id != -1) {
    newShop.id = id;
    updateShop(&newShop);
  } else {
    FILE *outputFile = NULL;
    openDbFile(&outputFile, shopsData);
    fseek(outputFile, 0L, SEEK_END);
    fwrite(&newShop, sizeof(shop), 1, outputFile);
    fclose(outputFile);
  }
  printf("\n\n/   Added shop:\t\t/\n");
  formatShopOutput(&newShop);
}

shop getNewShopRecord() {
  shop newShop = {
      .id = getRecordsNum(shopsData) + 1, .employeeId = -1, .isActive = true};
  printf("\\\\ New address: ");
  fflush(stdin);
  gets(newShop.address);
  return newShop;
}

void insertNewShopIndex() {
  FILE *outputFile = NULL;
  keyIndex newShopIndex = getNewDataIndex(shopsData);
  int recordNum = newShopIndex.key + 1;
  openDbFile(&outputFile, shopsIndices);
  fwrite(&recordNum, sizeof(int), 1, outputFile);
  fseek(outputFile, 0L, SEEK_END);
  fwrite(&newShopIndex, sizeof(keyIndex), 1, outputFile);
  fclose(outputFile);
}

void insertS() {
  int id = -1;
  if (!validateRecordsAmount(employeesIndices)) {
    id = getEmployeeTrashKey();
    if (id == -1) {
      fprintf(stderr, "\nEmployee.fl cannot store more than %d records!\n",
              MAX_RECORDS_AMOUNT);
      return;
    }
  }
  shop mShop = getM();
  if (mShop.isActive) {
    insertNewEmployeeRecord(&mShop, id);
    insertNewEmployeeIndex();
  }
}

void insertNewEmployeeRecord(shop *mShop, int id) {
  employee newEmployee = getNewEmployeeRecord(mShop);
  if (id != -1) {
    newEmployee.id = id;
    updateEmployee(&newEmployee);
  } else {
    FILE *outputFile = NULL;
    openDbFile(&outputFile, employeesData);
    fseek(outputFile, 0L, SEEK_END);
    fwrite(&newEmployee, sizeof(employee), 1, outputFile);
    fclose(outputFile);
  }
  mShop->employeeId = newEmployee.id;
  updateShop(mShop);

  printf("\n\n/   Added employee:\t/\n");
  formatEmployeeOutput(&newEmployee);
}

employee getNewEmployeeRecord(const shop *mShop) {
  employee newEmployee = {.id = getRecordsNum(employeesData) + 1,
                          .prevColleagueId = -1,
                          .nextColleagueId = mShop->employeeId,
                          .shopId = mShop->id,
                          .isActive = true};
  if (mShop->employeeId != -1) {
    employee prevEmployee = getEmployeeByKey(mShop->employeeId);
    prevEmployee.prevColleagueId = newEmployee.id;
    updateEmployee(&prevEmployee);
  }
  printf("\\\\ Enter credentials of new employee:\n"
         "\\\\ First name: ");
  fflush(stdin);
  gets(newEmployee.firstName);
  printf("\\\\ Last name: ");
  fflush(stdin);
  gets(newEmployee.lastName);
  return newEmployee;
}

void insertNewEmployeeIndex() {
  FILE *outputFile = NULL;
  keyIndex newEmployeeIndex = getNewDataIndex(employeesData);
  int recordNum = newEmployeeIndex.key + 1;
  openDbFile(&outputFile, employeesIndices);
  fwrite(&recordNum, sizeof(int), 1, outputFile);
  fseek(outputFile, 0L, SEEK_END);
  fwrite(&newEmployeeIndex, sizeof(keyIndex), 1, outputFile);
  fclose(outputFile);
}

bool validateRecordsAmount(dbFiles fileType) {
  if (getRecordsNum(fileType) >= MAX_RECORDS_AMOUNT)
    return false;
  return true;
}

keyIndex getNewDataIndex(dbFiles fileType) {
  keyIndex newShopIndex = {.key = getRecordsNum(fileType)};
  if (fileType == shopsData || fileType == shopsIndices)
    newShopIndex.address = getRecordsNum(fileType) * sizeof(shop);
  else
    newShopIndex.address = getRecordsNum(fileType) * sizeof(employee);
  return newShopIndex;
}