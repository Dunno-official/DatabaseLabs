#ifndef DB_FILESHANDLER_H
#define DB_FILESHANDLER_H

#include <stdio.h>

typedef enum dbFiles {
	groupsData,
	groupsIndixes,
	studentsData,
	studentsIndixes,
	trashZoneData
} dbFiles;

void openDbFile(FILE** file, dbFiles fileType);

#endif // DB_FILESHANDLER_H