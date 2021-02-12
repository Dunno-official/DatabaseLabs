#include <stdio.h>
#include "supplier.h"
#include "indexer.h"
#include "DBcontroller.h"

#define MASTER_IND "master.ind"
#define MASTER_DATA "master.fl"
#define MASTER_GARBAGE "master_garbage.txt"
#define INDEXER_SIZE sizeof(Indexer)
#define MASTER_SIZE sizeof(Supplier)
#pragma warning(disable : 6387)


void getSupplier()
{
	FILE* indexTable;
	FILE* database;
	Indexer indexer;
	int ID = 0;

	fopen_s(&indexTable , MASTER_IND, "rb");	
	fopen_s(&database , MASTER_DATA, "rb");		

	if (indexTable == NULL || database == NULL)
		return;

	printf_s("Enter ID: ");
	scanf_s("%d", &ID);

	if (checkIndexExistence(indexTable, ID) == 0)
		return;

	fseek(indexTable, (ID - 1) * INDEXER_SIZE, SEEK_SET);	
	fread(&indexer, INDEXER_SIZE, 1, indexTable);			

	if (indexer.exists == 1)
		return;
	
	fseek(database, indexer.address, SEEK_SET);				
	fread(&supplier, sizeof(Supplier), 1, database);		
	fclose(indexTable);										
	fclose(database);

	showSupplier();
}


void updateSupplier()
{

}


void insertSupplier()
{

}


void removeSupplier()
{

}




static void readSupplier()
{
	printf_s("Enter master\'s name: ");
	scanf_s("%s", supplier.name , 16);

	printf_s("Enter master\'s status: ");
	scanf_s("%d", &supplier.status);	
}


static void showSupplier()
{
	printf_s("\n");

	printf("Master\'s name: %s\n", supplier.name);
	printf("Master\'s status: %d\n", supplier.status);

	printf_s("\n");
}