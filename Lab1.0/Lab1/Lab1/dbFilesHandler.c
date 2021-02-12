#include "dbFilesHandler.h"

void openDbFile(FILE **file, dbFiles fileType) {
  char *path = NULL;
  if (fileType == shopsData)
    path = "D:\\Business\\Study\\Univ\\2_course\\2_semester\\Database\\DatabaseLabs\\Lab1.0\\Lab1\\Lab1\\Shops.fl";
  else if (fileType == shopsIndices)
    path = "D:\\Business\\Study\\Univ\\2_course\\2_semester\\Database\\DatabaseLabs\\Lab1.0\\Lab1\\Lab1\\Shops.ind";
  else if (fileType == employeesData)
    path = "D:\\Business\\Study\\Univ\\2_course\\2_semester\\Database\\DatabaseLabs\\Lab1.0\\Lab1\\Lab1\\Employees.fl";
  else if (fileType == employeesIndices)
    path = "D:\\Business\\Study\\Univ\\2_course\\2_semester\\Database\\DatabaseLabs\\Lab1.0\\Lab1\\Lab1\\Employees.ind";
  else
      path = "D:\\Business\\Study\\Univ\\2_course\\2_semester\\Database\\DatabaseLabs\\Lab1.0\\Lab1\\Lab1\\trashZone.tr";
  fopen_s(file , path, "r+b");
}