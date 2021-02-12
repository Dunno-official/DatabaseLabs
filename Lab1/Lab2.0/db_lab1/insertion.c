#include <stdlib.h>
#pragma pack(1)
#include "insertion.h"
#include "Reading.h"
#include "updating.h"

void insertM() {
    int id = -1;
    if (!validateRecordsAmount(groupsIndixes)) {
        id = getGroupTrashKey();
        if (id == -1) {
            fprintf(stderr, "\ngroups.fl cannot store more than %d records!\n",
                MAX_RECORDS_AMOUNT);
            return;
        }
    }
    insertNewGroupRecord(id);
    insertNewGroupIndex();
}

void insertNewGroupRecord(int id) {
    Group newGroup = getNewGroupRecord();
    if (id != -1) {
        newGroup.id = id;
        updateGroup(&newGroup);
    } else {
        FILE* outputFile = NULL;
        openDbFile(&outputFile, groupsData);
        fseek(outputFile, 0L, SEEK_END);
        fwrite(&newGroup, sizeof(Group), 1, outputFile);
        fclose(outputFile);
    }
    printf("\n\nAdded group:\t\t\n");
    formatGroupOutput(&newGroup);
}

Group getNewGroupRecord() {
    Group newGroup = {
        .id = getRecordsNum(groupsData) + 1, .studentId = -1, .isActive = true };
    printf("New group name: ");
    fflush(stdin);
    scanf("%s", newGroup.name);
    return newGroup;
}

void insertNewGroupIndex() {
    FILE* outputFile = NULL;
    KeyIndex newGroupIndex = getNewDataIndex(groupsData);
    int recordNum = newGroupIndex.key + 1;
    openDbFile(&outputFile, groupsIndixes);
    fwrite(&recordNum, sizeof(int), 1, outputFile);
    fseek(outputFile, 0L, SEEK_END);
    fwrite(&newGroupIndex, sizeof(KeyIndex), 1, outputFile);
    fclose(outputFile);
}

void insertS() {
    int id = -1;
    if (!validateRecordsAmount(studentsIndixes)) {
        id = getStudentTrashKey();
        if (id == -1) {
            fprintf(stderr, "students.fl cannot store more than %d records!\n",
                MAX_RECORDS_AMOUNT);
            return;
        }
    }

    int userKey = getUserKey(groupsData);
    Group foundedGroup = getGroupByKey(userKey);

    if (foundedGroup.isActive)
    {
        Group mGroup = getM();
        if (mGroup.isActive) {
            insertNewStudentRecord(&mGroup, id);
            insertNewStudentIndex();
        }
    }
    else
    {
        fprintf(stderr, "\nCannot find record in groups.fl!\n");
    }
}

void insertNewStudentRecord(Group* mGroup, int id) {
    Student newStudent = getNewStudentRecord(mGroup);
    if (id != -1) {
        newStudent.id = id;
        updateStudent(&newStudent);
    } else {
        FILE* outputFile = NULL;
        openDbFile(&outputFile, studentsData);
        fseek(outputFile, 0L, SEEK_END);
        fwrite(&newStudent, sizeof(Student), 1, outputFile);
        fclose(outputFile);
    }
    mGroup->studentId = newStudent.id;
    updateGroup(mGroup);

    printf("\n\nAdded student:\t\n");
    formatStudentOutput(&newStudent);
}

Student getNewStudentRecord(const Group* mGroup) {
    Student newStudent = { .id = getRecordsNum(studentsData) + 1,
                            .prevGroupmateId = -1,
                            .nextGroupmateId = mGroup->studentId,
                            .groupId = mGroup->id,
                            .isActive = true };
    if (mGroup->studentId != -1) {
        Student prevEmployee = getStudentByKey(mGroup->studentId);
        prevEmployee.prevGroupmateId = newStudent.id;
        updateStudent(&prevEmployee);
    }
    printf("Enter credentials of new student:\n"
        "First name: ");
    fflush(stdin);
    scanf("%s", newStudent.firstName);
    printf("Last name: ");
    fflush(stdin);
    scanf("%s", newStudent.lastName);
    return newStudent;
}

void insertNewStudentIndex() {
    FILE* outputFile = NULL;
    KeyIndex newStudentIndex = getNewDataIndex(studentsData);
    int recordNum = newStudentIndex.key + 1;
    openDbFile(&outputFile, studentsIndixes);
    fwrite(&recordNum, sizeof(int), 1, outputFile);
    fseek(outputFile, 0L, SEEK_END);
    fwrite(&newStudentIndex, sizeof(KeyIndex), 1, outputFile);
    fclose(outputFile);
}

bool validateRecordsAmount(dbFiles fileType) {
    if (getRecordsNum(fileType) >= MAX_RECORDS_AMOUNT)
        return false;
    return true;
}

KeyIndex getNewDataIndex(dbFiles fileType) {
    KeyIndex newGroupIndex = { .key = getRecordsNum(fileType) };
    if (fileType == groupsData || fileType == groupsIndixes)
        newGroupIndex.address = getRecordsNum(fileType) * sizeof(Group);
    else
        newGroupIndex.address = getRecordsNum(fileType) * sizeof(Student);
    return newGroupIndex;
}