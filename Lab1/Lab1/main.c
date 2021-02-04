#include <stdio.h>
#include <limits.h>
#include "supplement.h"
#include "supplier.h"

#pragma warning(disable : 4013)

void clearConsole();


int main()
{
	void (*allCommands[9])() =
	{
		clearConsole  ,
		getSupplement , updateSupplement , insertSupplement , removeSupplement , 
		getSupplier   , updateSupplier   , insertSupplier   , removeSupplier   ,  
	};

	unsigned int command = 0;


	do
	{
		allCommands[command]();

		printf_s("Choose option: ");
		scanf_s("%d", &command);
		
	} while (command != UINT_MAX);
	

	return 0;
}



void clearConsole()
{
	system("cls");

	printf_s(
		"Quit = -1\n"
		"Clear Console = 0\n\n"
		"Get Supplement     =  1\n"
		"Update Supplement  =  2\n"
		"Insert Supplement  =  3\n"
		"Remove Supplement  =  4\n\n"
		"Get Supplier       =  5\n"
		"Update Supplier    =  6\n"
		"Insert Supplier    =  7\n"
		"Remove Supplier    =  8\n\n");
}