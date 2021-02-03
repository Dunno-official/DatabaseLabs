#include <stdio.h>
#include <stdlib.h>
#include "supplement.h"
#include "supplier.h"

#pragma warning(disable : 4996)


void clearConsole();



int main()
{
	void (*commands[10])(void) =
	{
		getSupplement , updateSupplement , insertSupplement , removeSupplement , 
		getSupplier  , updateSupplier  , insertSupplier  , removeSupplier  ,

		clearConsole  
	};


	return 0;
}




void clearConsole()
{

}