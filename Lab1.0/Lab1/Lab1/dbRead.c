#include <stdbool.h>
#include <stdlib.h>

#pragma pack(1)

#include "dbFilesHandler.h"
#include "dbRead.h"
#include "dbStructures.h"
#include "dbUpdate.h"

#pragma warning( disable : 6011 )
#pragma warning( disable : 6385 )
#pragma warning( disable : 6387 )


shop getM() 
{
  int userKey = getUserKey(shopsData);
  shop foundedShop = getShopByKey(userKey);

  if (!foundedShop.isActive)
    fprintf(stderr, "\n*** Cannot find record in Shop.fl! ***\n");

  else 
  {
    printf("\n/   Founded shop:\t/\n");
    formatShopOutput(&foundedShop);
  }

  return foundedShop;
}

employee getS() 
{
  shop mShop = getM();
  employee foundedEmployee = {.isActive = false};

  if (mShop.isActive)
  {
        if (mShop.employeeId == -1)
          fprintf(stderr, "\n*** Shop on %s doesn't have any employee! ***\n",
                  mShop.address);
        else
        {
              int userKey = getUserKey(employeesData);
              employee employee = getEmployeeByKey(mShop.employeeId);
              bool isFounded = false;
              while (true)
                if (employee.id == userKey && employee.isActive) {
                  isFounded = true;
                  break;
                } else if (employee.nextColleagueId == -1)
                  break;
                else
                  employee = getEmployeeByKey(employee.nextColleagueId);
              if (!isFounded)
                fprintf(
                    stderr,
                    "\n*** Shop on %s doesn't have employee with ID number %d! ***\n",
                    mShop.address, userKey);
              else 
              {
                printf("\n/   Founded employee:\t/\n");
                formatEmployeeOutput(&employee);
                foundedEmployee = employee;
              }
        }
  }

  return foundedEmployee;
}

void getAll()
{
  FILE *outputFile = NULL;
  openDbFile(&outputFile, shopsData);
  shop outShop = {.isActive = false};

  while (true) 
  {
    fread(&outShop, sizeof(shop), 1, outputFile);

    if (feof(outputFile))
      break;

    if (outShop.isActive) 
    {
      printf("\n/   Shop:\t\t/\n");
      formatShopOutput(&outShop);
    }
  }

  fclose(outputFile);

  openDbFile(&outputFile, employeesData);
  employee outEmployee = {.isActive = false};
  while (true) 
  {
    fread(&outEmployee, sizeof(employee), 1, outputFile);
    if (feof(outputFile))
      break;

    if (outEmployee.isActive) 
    {
      printf("\n/   Employee:\t\t/\n");
      formatEmployeeOutput(&outEmployee);
    }

  }
  fclose(outputFile);
}

void countAll() {
  printf("\n\\\\   Total amount of shops is: %d\t\\\\\n",
         getRecordsNum(shopsData));
  printf("\\\\   Total amount of shops is: %d\t\\\\\n",
         getRecordsNum(employeesData));

  printf("\n");
  shop mShop = getM();
  printf("\\\\   Total amount of employees in shop on %s is: %d\t\\\\\n",
         mShop.address, getRecordsNum(employeesData));
}

int getEmployeesInShop(const shop *mShop) {
  int employeesNum = 0;
  FILE *employeesFile;
  openDbFile(&employeesFile, employeesData);
  employee outEmployee = {.isActive = false};
  while (true) {
    fread(&outEmployee, sizeof(employee), 1, employeesFile);
    if (feof(employeesFile))
      break;
    if (outEmployee.isActive && outEmployee.shopId == mShop->id)
      ++employeesNum;
  }
  fclose(employeesFile);
  return employeesNum;
}

void formatShopOutput(const shop *outShop) {
  printf("/   Id: %d\t\t/\n"
         "/   Address: %s\t/\n"
         "/   EmployeeId: %d\t/\n\n",
         outShop->id, outShop->address, outShop->employeeId);
}

void formatEmployeeOutput(const employee *outEmployee) {
  printf("/   Id: %d\t\t/\n"
         "/   First name: %s\t/\n"
         "/   Last name: %s\t/\n"
         "/   PrevColleagueId: %d\t/\n"
         "/   NextColleagueId: %d\t/\n"
         "/   ShopId: %d\t/\n\n",
         outEmployee->id, outEmployee->firstName, outEmployee->lastName,
         outEmployee->prevColleagueId, outEmployee->nextColleagueId,
         outEmployee->shopId);
}

int getUserKey(dbFiles fileType) {
  int key;
  if (fileType == shopsData || fileType == shopsIndices)
    printf("*\tEnter key of shop: ");
  else
    printf("*\tEnter key of employee: ");
  fflush(stdin);
  scanf_s("%d", &key); // NOLINT(cert-err34-c)
  return key;
}

shop getShopByKey(int key) {
  shop foundedShop = {.isActive = false};
  unsigned long offset = getAddressByKey(key, shopsData);
  if (offset != -1) {
    FILE *shopDataFile;
    openDbFile(&shopDataFile, shopsData);
    fseek(shopDataFile, (long)offset, SEEK_SET);
    fread(&foundedShop, sizeof(shop), 1, shopDataFile);
    fclose(shopDataFile);
  }
  return foundedShop;
}

employee getEmployeeByKey(int key) {
  employee foundedEmployee = {.isActive = false};
  unsigned long offset = getAddressByKey(key, employeesData);
  if (offset != -1) {
    FILE *employeeDataFile;
    openDbFile(&employeeDataFile, employeesData);
    fseek(employeeDataFile, (long)offset, SEEK_SET);
    fread(&foundedEmployee, sizeof(employee), 1, employeeDataFile);
    fclose(employeeDataFile);
  }
  return foundedEmployee;
}

unsigned long getAddressByKey(int key, dbFiles fileType) {
  unsigned long address = -1;
  int recordsNum = getRecordsNum(fileType);
  
  if (key - 1 < recordsNum) 
  {
    keyIndex* indices = (keyIndex*)malloc(recordsNum);
    readIndices(indices, recordsNum, fileType);

    for (int i = 0; i < recordsNum; ++i)
      if (indices[i].key == key - 1)
        address = indices[i].address;
  }

  
  return address;
}

void readIndices(keyIndex *indices, int size, dbFiles fileType) {
  FILE *indicesFile = NULL;
  if (fileType == shopsData || fileType == shopsIndices)
    openDbFile(&indicesFile, shopsIndices);
  else
    openDbFile(&indicesFile, employeesIndices);

  fseek(indicesFile, sizeof(int), SEEK_SET);
  fread(indices, sizeof(keyIndex), size, indicesFile);
  fclose(indicesFile);
}

int getRecordsNum(dbFiles fileType) {
  FILE *indicesFile = NULL;
  if (fileType == shopsData || fileType == shopsIndices)
    openDbFile(&indicesFile, shopsIndices);
  else if (fileType == employeesData || fileType == employeesIndices)
    openDbFile(&indicesFile, employeesIndices);

  int num = 0;
  fread(&num, sizeof(int), 1, indicesFile);
  fclose(indicesFile);
  return num;
}

trashZone getTrashZoneData() {
  trashZone trashZone;

  FILE *trashZoneFile = NULL;
  openDbFile(&trashZoneFile, trashZoneData);
  fread(&trashZone, sizeof(trashZone), 1, trashZoneFile);
  fseek(trashZoneFile, 0L, SEEK_END);
  int fileSize = ftell(trashZoneFile);
  if (fileSize == 0) {
    trashZone.shopsAmount = 0;
    trashZone.employeesAmount = 0;
  }
  fclose(trashZoneFile);

  if (trashZone.shopsAmount == 0)
    for (int i = 0; i < MAX_RECORDS_AMOUNT; ++i)
      trashZone.shops[i] = false;
  if (trashZone.employeesAmount == 0)
    for (int j = 0; j < MAX_RECORDS_AMOUNT; ++j)
      trashZone.employees[j] = false;

  return trashZone;
}

int getShopTrashKey() {
  trashZone trashZone = getTrashZoneData();
  if (trashZone.shopsAmount != 0)
    for (int i = 0; i < MAX_RECORDS_AMOUNT; ++i)
      if (trashZone.shops[i]) {
        --trashZone.shopsAmount;
        updateTrashZone(&trashZone);
        return ++i;
      }
  return -1;
}

int getEmployeeTrashKey() {
  trashZone trashZone = getTrashZoneData();
  if (trashZone.employeesAmount != 0)
    for (int i = 0; i < MAX_RECORDS_AMOUNT; ++i)
      if (trashZone.employees[i]) {
        --trashZone.employeesAmount;
        updateTrashZone(&trashZone);
        return ++i;
      }
  return -1;
}