#pragma pack(1)
#include "updating.h"
#include "filesHandler.h"
#include "reading.h"
#include "structures.h"
#include <stdio.h>

void updateM() {
    Group updGroup = getM();
    if (updGroup.isActive) {
        printf("Enter new name: ");
        fflush(stdin);
        scanf("%s", updGroup.name);

        printf("\n\nUpdated course:\t\n");
        formatGroupOutput(&updGroup);

        updateGroup(&updGroup);
    }
}

void updateS() {
    Student updStudent = getS();
    if (updStudent.isActive) {
        printf("Enter new first name: ");
        fflush(stdin);
        scanf("%s", updStudent.firstName);

        printf("Enter new last name: ");
        fflush(stdin);
        scanf("%s", updStudent.lastName);

        printf("\n\nUpdated professor:\t\n");
        formatStudentOutput(&updStudent);

        updateStudent(&updStudent);
    }
}

void updateGroup(const Group* updGroup) {
    FILE* groupDataFile = NULL;
    openDbFile(&groupDataFile, groupsData);
    unsigned long shopAddress = getAddressByKey(updGroup->id, groupsData);
    fseek(groupDataFile, (long)shopAddress, SEEK_SET);
    fwrite(&*updGroup, sizeof(Group), 1, groupDataFile);
    fclose(groupDataFile);
}

void updateStudent(const Student* updStudent) {
    FILE* studentDataFile = NULL;
    openDbFile(&studentDataFile, studentsData);
    unsigned long studentAddress =
        getAddressByKey(updStudent->id, studentsData);
    fseek(studentDataFile, (long)studentAddress, SEEK_SET);
    fwrite(&*updStudent, sizeof(Student), 1, studentDataFile);
    fclose(studentDataFile);
}

void updateTrashZone(const trashZone* updTrashZone) {
    FILE* trashZoneFile = NULL;
    openDbFile(&trashZoneFile, trashZoneData);
    fwrite(&*updTrashZone, sizeof(trashZone), 1, trashZoneFile);
    fclose(trashZoneFile);
}