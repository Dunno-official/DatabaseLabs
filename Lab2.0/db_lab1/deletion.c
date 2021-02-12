#pragma pack(1)
#include "deletion.h"
#include "reading.h"
#include "updating.h"

void delM()
{
    int userKey = getUserKey(groupsData);
    Group foundedGroup = getGroupByKey(userKey);
    Group delGroup;

    if (foundedGroup.isActive)
    {
        delGroup = getM();

        if (delGroup.isActive)
        {
            trashZone trashZone = getTrashZoneData();
            if (delGroup.studentId != -1)
                writeGroupStudentsInactive(&trashZone, &delGroup);
            delGroup.isActive = false;
            updateGroup(&delGroup);
            ++trashZone.groupsAmount;
            trashZone.groups[delGroup.id - 1] = true;
            updateTrashZone(&trashZone);
            printf("\n\\   Deletion successful\t\\\n");
        }
    }
    else
    {
        fprintf(stderr, "\nCannot find record in groups.fl!\n");
    }
}

void writeGroupStudentsInactive(trashZone* trashZone, const Group* delGroup) {
    Student delStudent = getStudentByKey(delGroup->studentId);
    while (true) {
        ++trashZone->studentsAmount; /////// / // / // 
        trashZone->students[delStudent.id - 1] = true;
        delStudent.isActive = false;
        updateStudent(&delStudent);
        if (delStudent.nextGroupmateId == -1)
            break;
        delStudent = getStudentByKey(delStudent.nextGroupmateId);
    }
}

void delS() 
{
    Student delStudent;

    int userKey = getUserKey(groupsData);
    Group foundedGroup = getGroupByKey(userKey);

    if (foundedGroup.isActive)
    {
        delStudent = getS();
    }
    else
    {
        fprintf(stderr, "\nCannot find record in groups.fl!\n");
        return;
    }

    delStudent.isActive = false;
    updateStudent(&delStudent);

    trashZone trashZone = getTrashZoneData();
    ++trashZone.studentsAmount;
    trashZone.students[delStudent.id - 1] = true;
    updateTrashZone(&trashZone);

    if (delStudent.prevGroupmateId == -1 && delStudent.nextGroupmateId != -1) {
        Group mGroup = getGroupByKey(delStudent.groupId);
        mGroup.studentId = delStudent.nextGroupmateId;
        updateGroup(&mGroup);
        Student nextStudent = getStudentByKey(delStudent.nextGroupmateId);
        nextStudent.prevGroupmateId = -1;
        updateStudent(&nextStudent);
    } else if (delStudent.prevGroupmateId != -1 &&
        delStudent.nextGroupmateId != -1) {
        Student prevGroupmate = getStudentByKey(delStudent.prevGroupmateId);
        prevGroupmate.nextGroupmateId = delStudent.nextGroupmateId;
        updateStudent(&prevGroupmate);
    } else {
        Student prevGroupmate = getStudentByKey(delStudent.prevGroupmateId);
        prevGroupmate.nextGroupmateId = -1;
        updateStudent(&prevGroupmate);
    }
    printf("\n\\   Deletion successful\t\\\n");
}