#pragma pack(1)
#include "deletion.h"
#include "reading.h"
#include "updating.h"

void delM() {
    Group delGroup = getM();
    if (delGroup.isActive) {
        trashZone trashZone = getTrashZoneData();
        if (delGroup.studentId != -1)
            writeGroupStudentsInactive(&trashZone, &delGroup);
        delGroup.isActive = false;
        updateGroup(&delGroup);
        ++trashZone.groupsAmount;
        trashZone.groups[delGroup.id - 1] = true;
        updateTrashZone(&trashZone);

        mDeleted++;
        printf("\nDeletion was successful\n");
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

void delS() {
    Student delStudent = getS();
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

    sDeleted++;
    printf("\nDeletion was successful\n");
}