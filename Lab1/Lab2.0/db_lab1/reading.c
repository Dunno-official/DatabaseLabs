#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#pragma pack(1)

#include "filesHandler.h"
#include "reading.h"
#include "structures.h"
#include "updating.h"

void getMm() {
    int userKey = getUserKey(groupsData);
    Group foundedGroup = getGroupByKey(userKey);

    if (!foundedGroup.isActive)
    {
        fprintf(stderr, "\nCannot find record in groups.fl!\n");
        return;
    }
    else
    {
        printf("\nFounded group:\t\n");
        formatGroupOutput(&foundedGroup);
    }
}


Group getM() {
    int userKey = getUserKey(groupsData);
    Group foundedGroup = getGroupByKey(userKey);

    if (!foundedGroup.isActive)
    {
        fprintf(stderr, "\nCannot find record in groups.fl!\n");
        return;
    }
    else 
    {
        printf("\nFounded group:\t\n");
        formatGroupOutput(&foundedGroup);
    }
    
    return foundedGroup;
}

Student getS() {
    Student foundedStudent = { .isActive = false };
    Group mGroup;
    mGroup.isActive = false;

    int userKey = getUserKey(groupsData);
    Group foundedGroup = getGroupByKey(userKey);

    if (foundedGroup.isActive)
    {
        mGroup = getM();
    }
    else
    {
        fprintf(stderr, "\nCannot find record in groups.fl!\n");
        return;
    }

   
    if (mGroup.isActive) 
    {
        if (mGroup.studentId == -1)
            fprintf(stderr, "\nGroup on %s doesn't have any student!\n",
                mGroup.name);
        else {
            int userKey = getUserKey(studentsData);
            Student student = getStudentByKey(mGroup.studentId);
            bool isFounded = false;
            while (true)
                if (student.id == userKey && student.isActive) {
                    isFounded = true;
                    break;
                } else if (student.nextGroupmateId == -1)
                    break;
                else
                    student = getStudentByKey(student.nextGroupmateId);
            if (!isFounded)
                fprintf(
                    stderr,
                    "\nGroup on %s doesn't have student with ID number %d!\n",
                    mGroup.name, userKey);
            else {
                printf("\nFounded student:\t\n");
                formatStudentOutput(&student);
                foundedStudent = student;
            }
        }
    }
    return foundedStudent;
}

void getAll() {
    FILE* outputFile = NULL;
    openDbFile(&outputFile, groupsData);

    if (openDbFile == 0)
        return;

    Group outGroup = { .isActive = false };
    while (true)
    {
        fread(&outGroup, sizeof(Group), 1, outputFile);
        if (feof(outputFile))
            break;
        if (outGroup.isActive) {
            printf("\nGroup:\t\t\n");
            formatGroupOutput(&outGroup);
        }
    }
    fclose(outputFile);

    openDbFile(&outputFile, studentsData);
    Student outStudent = { .isActive = false };
    while (true) {
        fread(&outStudent, sizeof(Student), 1, outputFile);
        if (feof(outputFile))
            break;
        if (outStudent.isActive) {
            printf("\nStudent:\t\t\n");
            formatStudentOutput(&outStudent);
        }
    }
    fclose(outputFile);
}

void countAll() {
    printf("\nTotal amount of groups is: %d\t\\\\\n",
        getRecordsNum(groupsData));
    printf("Total amount of students is: %d\t\\\\\n",
        getRecordsNum(studentsData));

    printf("\n");
    Group mGroup = getM();
    printf("Total amount of students in group on %s is: %d\t\\\\\n",
        mGroup.name, getRecordsNum(studentsData));
}

int getStudentsInGroup(const Group* mGroup) {
    int studentsNum = 0;
    FILE* studentsFile;
    openDbFile(&studentsFile, studentsData);
    Student outStudent = { .isActive = false };
    while (true) {
        fread(&outStudent, sizeof(Student), 1, studentsFile);
        if (feof(studentsFile))
            break;
        if (outStudent.isActive && outStudent.groupId == mGroup->id)
            ++studentsNum;
    }
    fclose(studentsFile);
    return studentsNum;
}

void formatGroupOutput(const Group* outGroup) {
    printf("Id: %d\t\t\n"
        "Name: %s\t\n",
        outGroup->id, outGroup->name);
}

void formatStudentOutput(const Student* outStudent) {
    printf("Id: %d\t\t\n"
        "First name: %s\t\n"
        "Last name: %s\t\n"
        "GroupId: %d\t\n\n",
        outStudent->id, outStudent->firstName, outStudent->lastName,
        outStudent->groupId);
}

int getUserKey(dbFiles fileType) {
    int key;
    if (fileType == groupsData || fileType == groupsIndixes)
        printf("Enter key of group: ");
    else
        printf("Enter key of student: ");
    fflush(stdin);
    scanf("%d", &key);
     return key;
}

Group getGroupByKey(int key) {
    Group foundedGroup = { .isActive = false };
    unsigned long offset = getAddressByKey(key, groupsData);
    if (offset != -1) {
        FILE* groupDataFile;
        openDbFile(&groupDataFile, groupsData);
        fseek(groupDataFile, (long)offset, SEEK_SET);
        fread(&foundedGroup, sizeof(Group), 1, groupDataFile);
        fclose(groupDataFile);
    }
    return foundedGroup;
}

Student getStudentByKey(int key) {
    Student foundedStudent = { .isActive = false };
    unsigned long offset = getAddressByKey(key, studentsData);
    if (offset != -1) {
        FILE* studentDataFile;
        openDbFile(&studentDataFile, studentsData);
        fseek(studentDataFile, (long)offset, SEEK_SET);
        fread(&foundedStudent, sizeof(Student), 1, studentDataFile);
        fclose(studentDataFile);
    }
    return foundedStudent;
}

unsigned long getAddressByKey(int key, dbFiles fileType) {
    unsigned long address = -1;
    const int recordsNum = getRecordsNum(fileType);
    if (key - 1 < recordsNum) {
        KeyIndex* indixes = malloc(sizeof(KeyIndex) * recordsNum);
        readIndixes(indixes, recordsNum, fileType);

        for (int i = 0; i < recordsNum; ++i)
            if (indixes[i].key == key - 1)
                address = indixes[i].address;
    }
    return address;
}

void readIndixes(KeyIndex* indixes, int size, dbFiles fileType) {
    FILE* indixesFile = NULL;
    if (fileType == groupsData || fileType == groupsIndixes)
        openDbFile(&indixesFile, groupsIndixes);
    else
        openDbFile(&indixesFile, studentsIndixes);

    fseek(indixesFile, sizeof(int), SEEK_SET);
    fread(indixes, sizeof(KeyIndex), size, indixesFile);
    fclose(indixesFile);
}

int getRecordsNum(dbFiles fileType) {
    FILE* indixesFile = NULL;
    if (fileType == groupsData || fileType == groupsIndixes)
        openDbFile(&indixesFile, groupsIndixes);
    else if (fileType == studentsData || fileType == studentsIndixes)
        openDbFile(&indixesFile, studentsIndixes);

    int num = 0;
    fread(&num, sizeof(int), 1, indixesFile);
    fclose(indixesFile);
    return num;
}

trashZone getTrashZoneData() {
    trashZone trashZone;

    FILE* trashZoneFile = NULL;
    openDbFile(&trashZoneFile, trashZoneData);
    fread(&trashZone, sizeof(trashZone), 1, trashZoneFile);
    fseek(trashZoneFile, 0L, SEEK_END);
    int fileSize = ftell(trashZoneFile);
    if (fileSize == 0) {
        trashZone.groupsAmount = 0;
        trashZone.studentsAmount = 0;
    }
    fclose(trashZoneFile);

    if (trashZone.groupsAmount == 0)
        for (int i = 0; i < MAX_RECORDS_AMOUNT; ++i)
            trashZone.groups[i] = false;
    if (trashZone.studentsAmount == 0)
        for (int j = 0; j < MAX_RECORDS_AMOUNT; ++j)
            trashZone.students[j] = false;

    return trashZone;
}

int getGroupTrashKey() {
    trashZone trashZone = getTrashZoneData();
    if (trashZone.groupsAmount != 0)
        for (int i = 0; i < MAX_RECORDS_AMOUNT; ++i)
            if (trashZone.groups[i]) {
                --trashZone.groupsAmount;
                updateTrashZone(&trashZone);
                return ++i;
            }
    return -1;
}

int getStudentTrashKey() {
    trashZone trashZone = getTrashZoneData();
    if (trashZone.studentsAmount != 0)
        for (int i = 0; i < MAX_RECORDS_AMOUNT; ++i)
            if (trashZone.students[i]) {
                --trashZone.studentsAmount;
                updateTrashZone(&trashZone);
                return ++i;
            }
    return -1;
}