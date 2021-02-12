#ifndef DATABASES_FILESHANDLER_H
#define DATABASES_FILESHANDLER_H

#include <stdio.h>

typedef enum dbFiles {
  shopsData,
  shopsIndices,
  employeesData,
  employeesIndices,
  trashZoneData
} dbFiles;

void openDbFile(FILE **file, dbFiles fileType);

#endif // DATABASES_FILESHANDLER_H