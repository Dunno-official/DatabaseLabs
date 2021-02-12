#pragma pack(1)
#include <stdbool.h>
#include <stdio.h>
#include "deletion.h"
#include "insertion.h"
#include "reading.h"
#include "updating.h"

unsigned int getOption();
void DoCommand(unsigned int command);
void clear();

int main()
{
    clear();

    while (true) 
    {
        unsigned int command = getOption();
        DoCommand(command);
    }
}




unsigned int getOption()
{
    unsigned int opt;
    do 
    {        
        fflush(stdin);
        printf("\nChoose option : ");
        scanf("%d", &opt);

    } while (!(opt >= 0 && opt <= 11));

    return opt;
}


void DoCommand(unsigned int command)
{
    switch (command)
    {
    case 0:
        clear();
        break;
    case 1:
        getAll();
        break;
    case 2:
        countAll();
        break;
    case 3:
        insertM();
        break;
    case 4:
        getM();
        break;
    case 5:
        updateM();
        break;
    case 6:
        delM();
        break;
    case 7:
        insertS();
        break;
    case 8:
        getS();
        break;
    case 9:
        updateS();
        break;
    case 10:
        delS();
        break;    
    }
}



void clear()
{
    system("cls");
    printf
        (
        "Clear:    0\n"
        "GetAll:   1\n"
        "CountAll: 2\n\n"
        "InsertM:  3\n"
        "GetM:     4\n"
        "UpdateM:  5\n"
        "DelM:     6\n\n"
        "InsertS:  7\n"
        "GetS:     8\n"
        "UpdateS:  9\n"
        "DelS:     10\n\n");
}