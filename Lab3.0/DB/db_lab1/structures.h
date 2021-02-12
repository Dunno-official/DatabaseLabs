#ifndef DB_STRUCTURES_H
#define DB_STRUCTURES_H

#define MAX_RECORDS_AMOUNT 20
#include <stdbool.h>

#pragma pack(1)
typedef struct Group {
	int id;
	char name[70];
	int studentId;
	bool isActive;
} Group;

#pragma pack(1)
typedef struct Student {
	int id;
	char firstName[30];
	char lastName[30];
	int prevGroupmateId;
	int nextGroupmateId;
	int groupId;
	bool isActive;
} Student;

#pragma pack(1)
typedef struct KeyIndex {
	int key;
	unsigned long address;
} KeyIndex;

#pragma pack(1)
typedef struct trashKeys {
	int groupsAmount;
	int studentsAmount;
	bool groups[MAX_RECORDS_AMOUNT];
	bool students[MAX_RECORDS_AMOUNT];
} trashZone;

#endif // DB_STRUCTURES_H