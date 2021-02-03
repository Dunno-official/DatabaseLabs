#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "supplement.h"
#include "supplier.h"

#pragma warning(disable : 4996)



void clearConsole();



int main()
{
	void (*allCommands[9])() =
	{
		getSupplement , updateSupplement , insertSupplement , removeSupplement , 
		getSupplier   , updateSupplier   , insertSupplier   , removeSupplier   ,
		clearConsole  
	};


	unsigned int command = 8;

	do
	{
		allCommands[command]();

		scanf_s("%d", &command);
		
	} while (command != UINT_MAX);
	

	return 0;
}




void clearConsole()
{
	printf(
		"Choose option:\n"
		"Quit: -1\n"
		"getSupplement: 0\n"
		"updateSupplement: 1\n"
		"insertSupplement\n"
		"removeSupplement\n"
		"5 - Insert Slave\n"
		"6 - Get Slave\n"
		"7 - Update Slave\n"
		"8 - Delete Slave\n"
		"9 - Info\n");
}