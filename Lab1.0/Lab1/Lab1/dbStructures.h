#ifndef DATABASES_DBSTRUCTURES_H
#define DATABASES_DBSTRUCTURES_H

#define MAX_RECORDS_AMOUNT 20
#include <stdbool.h>

#pragma pack(1)
typedef struct shop {
  int id;
  char address[70];
  int employeeId;
  bool isActive;
} shop;

#pragma pack(1)
typedef struct employee {
  int id;
  char firstName[30];
  char lastName[30];
  int prevColleagueId;
  int nextColleagueId;
  int shopId;
  bool isActive;
} employee;

#pragma pack(1)
typedef struct keyIndex {
  int key;
  unsigned long address;
} keyIndex;

#pragma pack(1)
typedef struct trashKeys {
  int shopsAmount;
  int employeesAmount;
  bool shops[MAX_RECORDS_AMOUNT];
  bool employees[MAX_RECORDS_AMOUNT];
} trashZone;

#endif // DATABASES_DBSTRUCTURES_H