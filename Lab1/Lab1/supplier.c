#include <stdio.h>
#include "supplier.h"

#define MASTER_IND "master.ind"
#define MASTER_DATA "master.fl"
#define MASTER_GARBAGE "master_garbage.txt"
#define INDEXER_SIZE sizeof(struct Indexer)
#define MASTER_SIZE sizeof(struct Supplier)


void getSupplier()
{
	FILE* indexTable = fopen(MASTER_IND, "rb");				// "rb": відкрити бінарний файл
	FILE* database = fopen(MASTER_DATA, "rb");				// тільки для читання

	if (!checkFileExistence(indexTable, database, error))
	{
		return 0;
	}

	struct Indexer indexer;

	if (!checkIndexExistence(indexTable, error, id))
	{
		return 0;
	}

	fseek(indexTable, (id - 1) * INDEXER_SIZE, SEEK_SET);	// Отримуємо індексатор шуканого запису
	fread(&indexer, INDEXER_SIZE, 1, indexTable);			// за вказаним номером

	if (!checkRecordExistence(indexer, error))
	{
		return 0;
	}

	fseek(database, indexer.address, SEEK_SET);				// Отримуємо шуканий запис з БД-таблички
	fread(master, sizeof(struct Master), 1, database);		// за знайденою адресою
	fclose(indexTable);										// Закриваємо файли
	fclose(database);

	return 1;
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