#include "filesHandler.h"

void openDbFile(FILE** file, dbFiles fileType) {
    char* path = NULL;
    if (fileType == groupsData)
        path = "D:\\Business\\Study\\Univ\\2_course\\2_semester\\Database\\DatabaseLabs\\Lab2.0\\db_lab1\\groups.fl";
    else if (fileType == groupsIndixes)
        path = "D:\\Business\\Study\\Univ\\2_course\\2_semester\\Database\\DatabaseLabs\\Lab2.0\\db_lab1\\groups.ind";
    else if (fileType == studentsData)
        path = "D:\\Business\\Study\\Univ\\2_course\\2_semester\\Database\\DatabaseLabs\\Lab2.0\\db_lab1\\students.fl";
    else if (fileType == studentsIndixes)
        path = "D:\\Business\\Study\\Univ\\2_course\\2_semester\\Database\\DatabaseLabs\\Lab2.0\\db_lab1\\students.ind";
    else
        path = "D:\\Business\\Study\\Univ\\2_course\\2_semester\\Database\\DatabaseLabs\\Lab2.0\\db_lab1\\trashZone.tz";
    *file = fopen(path, "r+b");
}
  