#pragma pack(1)
#include <stdbool.h>
#include <stdio.h>
#include <limits.h>
#include "deletion.h"
#include "insertion.h"
#include "reading.h"
#include "updating.h"


void clear();

int main()
{
    unsigned int command = 0;

    void (*allCommands[10])() =
    {
        clear   ,
        insertM , getM ,  updateM , delM ,
        insertS , getS ,  updateS , delS ,
        getAll  ,
    };


    do
    {
        allCommands[command]();
        scanf_s("%d", &command);

    } while (command != UINT_MAX);

    return 0;
}


void clear()
{
    system("cls");
    printf
    ("Quit:    -1\n"
        "Clear:    0\n\n"
        "InsertM:  1\n"
        "GetM:     2\n"
        "UpdateM:  3\n"
        "DelM:     4\n\n"
        "InsertS:  5\n"
        "GetS:     6\n"
        "UpdateS:  7\n"
        "DelS:     8\n"
        "GetAll:   9\n\n"
        "Choose option: ");
}